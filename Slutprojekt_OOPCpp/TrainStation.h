

#ifndef TRAINSTATION_H
#define TRAINSTATION_H

#include <string>
#include <list>
#include <memory>
#include "Vehicle.h"
#include "constants.h"

#include <iostream>

class TrainStation
{
public:
	TrainStation() = default; // const std::string &p_name) : m_name(p_name) {}
	~TrainStation() {};

	std::string getName() const { return m_name; }
	void setName(const std::string &p_name) { m_name = p_name; }

	std::shared_ptr<Vehicle> findVehicle(VehicleType type);  //search for vehicle of type x
	void parkVehicle(std::shared_ptr<Vehicle> vehicle);

	std::shared_ptr<Vehicle> locateVehicle(const int id) const;  // search for vehicle with id x

	const std::vector<std::shared_ptr<Vehicle>> getAllVehicles() const { 
		std::vector < std::shared_ptr<Vehicle> >vehicles;
		for (auto &shared : m_vehicles)
			vehicles.push_back(std::shared_ptr<Vehicle>(shared));

		return vehicles; 
	}
private:
	std::string m_name;
	std::list <std::shared_ptr<Vehicle>> m_vehicles;
};

std::istream &operator >> (std::istream &instream, TrainStation &ts);

#endif // TRAINSTATION_H
