

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

	// ------ GETTERS ------
	std::string getName() const { return m_name; }
	const std::vector<std::shared_ptr<Vehicle>> getAllVehicles() const;
	const std::vector<std::pair<VehicleType, int>> getVehicleCounts() const;  //nr vehicles by type
	const int getNumVehicles() const { return m_vehicles.size(); }   //get only available vehicles (of all types)
	const std::vector <std::shared_ptr<Train>> getTrains() const { return m_trains; }

	// ------ SETTER ------
	void setName(const std::string &p_name) { m_name = p_name; }

	// ------ LOGIC ------

	/*
	Searches the station for a vehicle of the specified type. The vehicle with the lowest id will be chosen.

	@param type the type to search for
	@return shared pointer to the chosen vehicle
	*/
	std::shared_ptr<Vehicle> findVehicle(VehicleType type);

	/*
	Places a vehicle in the pool of available vehicles at this station.

	@param vehicle the vehicle to park
	*/
	void parkVehicle(std::shared_ptr<Vehicle> vehicle);

	/*
	Searches the station for a specific instance of Vehicle.

	@param id the id of the searched vehicle
	@return shared pointer to the found vehicle if found, null pointer otherwise
	*/
	std::shared_ptr<Vehicle> locateVehicle(const int id) const;  

	/*
	Searches the station for a train.

	@param id the id of the searched train
	@return shared pointer to the found train if found, null pointer otherwise
	*/
	std::shared_ptr<Train> locateTrain(const int id) const;

	/*
	Adds a train to the station based on a Route object.

	@param route the route to create a train for
	*/
	void addTrain(Route &route) { m_trains.push_back(std::shared_ptr<Train>(new Train(route))); }

	/*
	Attempts to assemble a train with the vehicles available at this station.

	@param train the train to assemble
	@return true if all vehicle types were found, false otherwise
	*/	
	bool assembleTrain(std::shared_ptr<Train> train);
	
	/*
	Places a train in the train data structure.

	@param train the arriving train
	*/
	void arrive(std::shared_ptr<Train> train);

	/*
	Removes a train from the train data structure at this station.
	*/
	void depart(std::shared_ptr<Train> train);

private:
	std::string m_name;
	std::list <std::shared_ptr<Vehicle>> m_vehicles;
	std::vector <std::shared_ptr<Train>> m_trains;
};

std::istream &operator >> (std::istream &instream, TrainStation &ts);

#endif // TRAINSTATION_H
