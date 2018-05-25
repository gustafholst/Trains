

#ifndef TRAINSTATION_H
#define TRAINSTATION_H

#include <string>
#include <list>
#include <memory>
#include "Vehicle.h"
#include "constants.h"
#include "Route.h"
#include "Train.h"

#include <iostream>

class TrainStation
{
public:
	TrainStation() = default; // const std::string &p_name) : m_name(p_name) {}
	~TrainStation() {};

	std::string getName() const { return m_name; }
	void setName(const std::string &p_name) { m_name = p_name; }

	std::shared_ptr<Vehicle> findVehicle(VehicleType type);  //search for vehicle of type x         const!!!!!!!!
	void parkVehicle(std::shared_ptr<Vehicle> vehicle);

	std::shared_ptr<Vehicle> locateVehicle(const int id) const;  // search for vehicle with id x

	void addTrain(Route &route) { m_trains.push_back(std::shared_ptr<Train>(new Train(route))); }

	const std::vector <std::shared_ptr<Train>> getTrains() const { return m_trains; }
	bool assembleTrain(std::shared_ptr<Train> train);
	
	void arrive(std::shared_ptr<Train> train);
	void depart(std::shared_ptr<Train> train);

	const std::vector<std::shared_ptr<Vehicle>> getAllVehicles() const;
	const std::vector<std::pair<VehicleType, int>> getVehicleCounts() const;

private:
	std::string m_name;
	std::list <std::shared_ptr<Vehicle>> m_vehicles;
	std::vector <std::shared_ptr<Train>> m_trains;
};

std::istream &operator >> (std::istream &instream, TrainStation &ts);

#endif // TRAINSTATION_H
