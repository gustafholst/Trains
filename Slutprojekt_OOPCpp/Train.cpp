
#include <algorithm>
#include "Train.h"



//Train::Train()
//{
//}


Train::~Train()
{
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
