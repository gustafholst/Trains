
#include <algorithm>
#include "Train.h"



//Train::Train()
//{
//}


Train::~Train()
{
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
	/*auto it = std::find_if(m_vehicles.cbegin(), m_vehicles.cend(), [p_vehicle](const std::shared_ptr<Vehicle> vptr) {
		return vptr == p_vehicle;
	});
	if (it != m_vehicles.cend())
	{
		std::shared_ptr<Vehicle> decoupled = *it;
		m_vehicles.erase(it);

		return decoupled;
	}*/

	if (m_vehicles.empty())
		return nullptr;

	//decouple last vehicle
	std::shared_ptr<Vehicle> decoupled = m_vehicles.back();
	m_vehicles.pop_back();
	return decoupled;
}

std::shared_ptr<Vehicle> Train::locateVehicle(const int id) const
{
	auto it = std::find_if(m_vehicles.cbegin(), m_vehicles.cend(), [id](const std::shared_ptr<Vehicle> &vptr) {
		return vptr->getId() == id;
	});

	if (it != m_vehicles.cend())
		return *it;

	return nullptr;
}
