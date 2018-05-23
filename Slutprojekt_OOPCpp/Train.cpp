
#include <algorithm>
#include "Train.h"



//Train::Train()
//{
//}


Train::~Train()
{
}

void Train::addVehicle(const std::shared_ptr<Vehicle>& p_vehicle, int index)
{
	if (index == -1)
		m_vehicles.push_back(p_vehicle);  //when train not assembled
	else
		m_vehicles[index] = p_vehicle;    //when train is incomplete
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
