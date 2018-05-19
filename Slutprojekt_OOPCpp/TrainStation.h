

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

	std::shared_ptr<Vehicle> findVehicle(VehicleType type) const;
	void parkVehicle(std::shared_ptr<Vehicle> vehicle);

private:
	std::string m_name;
	std::list <std::shared_ptr<Vehicle>> m_vehicles;
};

std::istream &operator >> (std::istream &instream, TrainStation &ts);

#endif // TRAINSTATION_H
