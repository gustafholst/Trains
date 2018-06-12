
#include <algorithm>
#include <sstream>
#include <cassert>
#include "TrainStation.h"

bool vehicleCompare(const std::shared_ptr<Vehicle> a, const std::shared_ptr<Vehicle> b)
{
	return a->getId() < b->getId();
}

std::shared_ptr<Vehicle> TrainStation::findVehicle(VehicleType type)
{
	m_vehicles.sort([](const std::shared_ptr<Vehicle> &a, const std::shared_ptr<Vehicle> &b) {
		return a->getId() < b->getId();
	});
	
	auto it = std::find_if(m_vehicles.cbegin(), m_vehicles.cend(), [type](const std::shared_ptr<Vehicle> &vptr) {
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

std::shared_ptr<Train> TrainStation::locateTrain(const int id) const
{
	auto found = std::find_if(m_trains.cbegin(), m_trains.cend(), [id](const std::shared_ptr<Train> t) {
		return t->getId() == id;
	});

	if (found != m_trains.cend())
		return *found;

	return nullptr;
}

bool TrainStation::assembleTrain(std::shared_ptr<Train> train)
{
	std::vector<VehicleType> neededVehicles = train->getVehicleTypes();
	
	bool complete = true;

	if (train->getState() == TrainState::INCOMPLETE)  //previous attempts have been made
	{
		std::vector<std::shared_ptr<Vehicle>> vehicles = train->getVehicles();
		for (size_t i = 0; i < neededVehicles.size(); ++i)
		{
			if (vehicles[i] == nullptr) { //if vehicle at that spot (index) is missing
				std::shared_ptr<Vehicle> v = findVehicle(neededVehicles[i]);
				if (v == nullptr)
					complete = false;
				else
					train->addVehicle(v, i);   //add vehicle at spot i in the train
			}
		}
		return complete;
	}
	//otherwise (first attempt to assemble train)
	for (VehicleType type : neededVehicles)
	{
		std::shared_ptr<Vehicle> v = findVehicle(type);
		if (v == nullptr)
			complete = false;
		train->addVehicle(v);
	}

	return complete;
}

void TrainStation::arrive(std::shared_ptr<Train> train)
{
	m_trains.push_back(train);
}

void TrainStation::depart(std::shared_ptr<Train> train)
{
	auto found = std::find_if(m_trains.begin(), m_trains.end(), [train](std::shared_ptr<Train> t) {
		return train == t;
	});

	assert(found != m_trains.end());    //if train is not found, something is seriously wrong

	if (found != m_trains.end())
		m_trains.erase(found);
}

const std::vector<std::shared_ptr<Vehicle>> TrainStation::getAllVehicles() const
{
	std::vector < std::shared_ptr<Vehicle> >vehicles;
	// copy all pointer into a vector (instead of list)
	copy(m_vehicles.cbegin(), m_vehicles.cend(), std::back_inserter(vehicles));

	return vehicles;
}

const std::vector<std::pair<VehicleType, int>> TrainStation::getVehicleCounts() const
{
	std::vector<std::pair<VehicleType, int>> counts;
	for (size_t i = 0; i < vehicleTypeStrings.size(); ++i)
	{
		VehicleType type = static_cast<VehicleType>(i);
		int count = std::count_if(m_vehicles.cbegin(), m_vehicles.cend(), [type](std::shared_ptr<Vehicle> v) {
			return v->getType() == type;
		});
		counts.push_back(std::make_pair(type, count));
	}
	
	return counts;
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

		switch (type)
		{
		case VehicleType::SeatedCoach:
			ts.parkVehicle(shared_ptr<Vehicle>(new SeatedCoach(param[0], param[2], param[3])));  // id, numSeats, internet
			break;
		case VehicleType::SleeperCoach:
			ts.parkVehicle(std::make_shared<SleeperCoach>(param[0], param[2]));  // id, numBeds
			break;
		case VehicleType::OpenGoods:
			ts.parkVehicle(std::make_shared<OpenGoods>(param[0], param[2], param[3]));  // id, capacity, area
			break;
		case VehicleType::CoveredGoods:
			ts.parkVehicle(std::make_shared<CoveredGoods>(param[0], param[2]));  // id, volume
			break;
		case VehicleType::ElectricEngine:
			ts.parkVehicle(std::make_shared<ElectricEngine>(param[0], param[2], param[3]));  // id, maxSpeed, effect
			break;
		case VehicleType::DieselEngine:
			ts.parkVehicle(std::make_shared<DieselEngine>(param[0], param[2], param[3]));  // id, maxSpeed, fuelConsumption
			break;
		default:
			break;
		}

		pos = row.find('(', pos + 1);  // find next bracket
	}

	return instream;
}
