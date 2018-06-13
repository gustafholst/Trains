/*
* RailwayCompany.h
* Gustaf Holst, guho1700
* 2018-05-27
* v1.0
*
* Declares the RailwayCompany class.
*
*/

#ifndef RAILWAYCOMPANY_H
#define RAILWAYCOMPANY_H

#include <memory>
#include "TrainMap.h"
#include "TrainStation.h"
#include "Train.h"
#include "Route.h"
#include "auxilliary.h"
#include "Simulation.h"


class RailwayCompany
{
public:
	RailwayCompany() = default;

	// load files (throws runtime exceptions)
	void loadStations();
	void loadTimetable();
	void loadMap();

	// ------ GETTERS ------
	std::vector<std::shared_ptr<Vehicle>> getAllVehicles() const;
	TrainStation* getStation(const std::string &sName);
	std::vector<const TrainStation*> getAllStations() const;
	std::vector<std::string> getAllStationNames() const;
	std::vector<std::shared_ptr<Train>> getAllTrains() const;
	std::vector<const Route*> getTimetable();
	const std::map<std::string, int> getInitialVehicleCount() const { return m_vehicleCount; }
	int getDistance(const std::string &depStation, const std::string &arrStation) { return distance(depStation, arrStation); }

	// ------ LOGIC ------
	/*
	Searches all stations and running trains for the vehicle with the specified id. Returns a tuple with pointers to the vehicle and train
	/trainstation where the vehice was found. Pointers not applicable will be null pointers.

	@param id the id the of the searched vehicle
	@return pointer to the vehicle if found together with pointer to station or train, nullptr otherwise
	*/
	std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> locateVehicle(const int id);

	/*
	Searches all stations for the train with the specified id.

	@param id id of the train to search for
	@return shared pointer to the train if found, nullptr otherwise
	*/
	std::shared_ptr<Train> locateTrain(const int id);

	/*
	Searches the specified trainstation for a vehicle of the specified type. The vehicle with the lowest id will be chosen if
	several are available.

	@param station the station to search
	@param type the type of vehcile to search for
	@return shared pointer to the found vehicle, or nullptr if no vehicle was found
	*/
	std::shared_ptr<Vehicle> findVehicleType(TrainStation *station, VehicleType type) { return station->findVehicle(type); }

	/*
	Puts a pointer to the specified train in the vector with trains currently running (i.e are not currently associated
	with any station).

	@param train  pointer to the train to place in in-transit data structure
	*/
	void placeInTransit(std::shared_ptr<Train> train);

	/*
	Removes pointer to the specified train from the in-transit data structure.

	@param train pointer to the train to take out of transit
	*/
	void removeFromTransit(std::shared_ptr<Train> train);

	/*
	Instantiates Train objects that corresponds to all the Route objects in the timetable.
	*/
	void createTrains();

	/*
	Counts and stores a record of number of vehicles at every station at the start of the simulation.
	*/
	void makeInitialVehicleInventory();
	
private:
	std::vector<TrainStation> m_stations;
	std::vector<Route> m_timetable;
	std::list<std::shared_ptr<Train>> m_runningTrains;
	TrainMap distance;   //functor
	std::map<std::string, int> m_vehicleCount;   //keep track of how many vehicles are att the station at beginning of simulation
};


#endif // RAILWAYCOMPANY_H