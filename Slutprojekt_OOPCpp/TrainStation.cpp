
#include <algorithm>
#include <sstream>
#include "TrainStation.h"



std::shared_ptr<Vehicle> TrainStation::findVehicle(VehicleType type)
{
	m_vehicles.sort([](const std::shared_ptr<Vehicle> &a, const std::shared_ptr<Vehicle> &b) {
		return a->getId() < b->getId();
	});
	
	auto it = find_if(m_vehicles.cbegin(), m_vehicles.cend(), [type](const std::shared_ptr<Vehicle> &vptr) {
		return vptr->getType() == type;
	});

	if (it != m_vehicles.cend())
	{
		std::shared_ptr<Vehicle> foundVehicle = *it;
		m_vehicles.erase(it);   //remove the vehicle from this staion
		return foundVehicle;
	}
		
	return nullptr;
}

void TrainStation::parkVehicle(std::shared_ptr<Vehicle> vehicle)
{
	m_vehicles.push_back(vehicle);
}

std::shared_ptr<Vehicle> TrainStation::locateVehicle(const int id) const
{
	auto it = std::find_if(m_vehicles.cbegin(), m_vehicles.cend(), [id](const std::shared_ptr<Vehicle> &vptr) {
		return vptr->getId() == id;
	});

	if (it != m_vehicles.cend())
		return *it;

	return nullptr;
}

bool TrainStation::assembleTrain(std::shared_ptr<Train> train)
{
	std::vector<VehicleType> neededVehicles = train->getVehicleTypes();
	
	bool complete = true;

	if (train->getState() == TrainState::INCOMPLETE)
	{
		std::vector<std::shared_ptr<Vehicle>> vehicles = train->getVehicles();
		for (size_t i = 0; i < neededVehicles.size(); ++i)
		{
			if (vehicles[i] == nullptr) { //if that vehicle is missing
				std::shared_ptr<Vehicle> v = findVehicle(neededVehicles[i]);
				if (v == nullptr)
					complete = false;
				else
					train->addVehicle(v, i);   //add vehicle at spot i in the train
			}
		}
		return complete;
	}
	//otherwise (first try to assemble train)
	for (VehicleType type : neededVehicles)
	{
		std::shared_ptr<Vehicle> v = findVehicle(type);
		if (v == nullptr)
			complete = false;
		train->addVehicle(v);
	}

	return complete;
}

std::istream & operator>>(std::istream & instream, TrainStation & ts)
{
	using namespace std;
	string stationName;
	getline(instream, stationName, ' '); //read the station name
	ts.setName(stationName);             

	string row;
	getline(instream, row);  //get rest of row (until newline)

	size_t pos = row.find('(', 0);	//find first left bracket
	while (pos != string::npos) {
		//cout << row.substr(pos+1, row.size()) << endl;
		istringstream stream(row.substr(pos + 1, 20));  // 20 = 4*4 + 4 (max size of 4 4digit parameters within brackets (xxxx xxxx xxxx xxxx))
		int param[4];  // array for parameters read from file [0]->id [1]->vehicle type [2]->typedependent [3]->typedependent
		int count = 0;
		while (stream >> param[count++]);  //read parameters (3 or 4)

		VehicleType type = static_cast<VehicleType>(param[1]);   //param[1] contains vehicle type

		if (type == VehicleType::SeatedCoach)
		{
			ts.parkVehicle(shared_ptr<Vehicle>(new SeatedCoach(param[0], param[2], param[3])));  // id, numSeats, internet
		}
		else if (type == VehicleType::SleeperCoach)
		{
			ts.parkVehicle(shared_ptr<Vehicle>(new SleeperCoach(param[0], param[2])));  // id, numBeds
		}
		else if (type == VehicleType::OpenGoods)
		{
			ts.parkVehicle(shared_ptr<Vehicle>(new OpenGoods(param[0], param[2], param[3])));  // id, capacity, area
		}
		else if (type == VehicleType::CoveredGoods)
		{
			ts.parkVehicle(shared_ptr<Vehicle>(new CoveredGoods(param[0], param[2])));  // id, volume
		}
		else if (type == VehicleType::ElectricEngine)
		{
			ts.parkVehicle(shared_ptr<Vehicle>(new ElectricEngine(param[0], param[2], param[3])));  // id, maxSpeed, effect
		}
		else if (type == VehicleType::DieselEngine)
		{
			ts.parkVehicle(shared_ptr<Vehicle>(new DieselEngine(param[0], param[2], param[3])));  // id, maxSpeed, fuelConsumption
		}

		pos = row.find('(', pos + 1);  // find next bracket
	}

	return instream;
}
