/*
* Train.h
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Defines the Train class.
*
*/

#include <algorithm>
#include "Train.h"

std::vector<VehicleType> Train::getMissingVehicles() const
{
	std::vector<VehicleType> missingTypes;
	for (size_t i = 0; i < m_vehicles.size(); ++i)
	{
		if (m_vehicles[i] == nullptr)
			missingTypes.push_back(m_vehicleTypes[i]);
	}

	return missingTypes;
}

int Train::setAvgSpeed(const int p_avgSpeed)
{
	int speed = p_avgSpeed;

	//check max speed for all vehicles (if any has lower max speed than p_avgSpeed: use the lower value)
	for (auto v : m_vehicles)   
	{
		int max = v->getMaxSpeed();
		if (max > 0 && max < speed)   //max > 0 -> vehicle has max speed (is engine)
		{
			speed = max;    
		}
	}

	//finally check against maxSpeed of the route (which is generally lower than that of the engines)
	if (m_maxSpeed < speed)  
		speed = m_maxSpeed;

	m_avgSpeed = speed;

	return m_avgSpeed;  //return the speed that was set
}

void Train::addVehicle(const std::shared_ptr<Vehicle> p_vehicle, int index)
{
	if (index == -1)
		m_vehicles.push_back(p_vehicle);  //when train not assembled
	else
		m_vehicles[index] = p_vehicle;    //when train is incomplete
}

std::shared_ptr<Vehicle> Train::decoupleVehicle()
{
	if (m_vehicles.empty())
		return nullptr;

	//decouple last vehicle
	std::shared_ptr<Vehicle> decoupled = m_vehicles.back();
	m_vehicleIds.push_back(decoupled->getId());
	m_vehicles.pop_back();                   
	return decoupled;
}

std::shared_ptr<Vehicle> Train::locateVehicle(const int id) const
{
	auto it = std::find_if(m_vehicles.cbegin(), m_vehicles.cend(), [id](const std::shared_ptr<Vehicle> vptr) {
		if (vptr)     //incomplete trains contains null pointers so make sure only to call getId on existing vehicles
			return vptr->getId() == id;
		else
			return false;
	});

	if (it != m_vehicles.cend())
		return *it;
	
	return nullptr;
}

bool Train::containedVehicle(const int id) const
{
	return std::find(m_vehicleIds.cbegin(), m_vehicleIds.cend(), id) != m_vehicleIds.cend();
}
