/*
* Train.h
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Declares the Train class.
*
*/

#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <memory>
#include "Vehicle.h"
#include "Route.h"
#include "constants.h"

class Train : public Route
{
public:
	Train(const Route &route)
		:Route(route), m_state(TrainState::NOT_ASSEMBLED), m_delay(0), m_actualDepTime(m_depTime), m_avgSpeed(0) {}
	Train(const int p_id, const std::string &p_depStation, const std::string &p_arrStation, const Time &p_depTime, const Time &p_arrTime)
		:Route(p_id, p_depStation, p_arrStation, p_depTime, p_arrTime) {}

	// ---- GETTERS ----
	std::vector<std::shared_ptr<Vehicle>> getVehicles() const { return m_vehicles; }
	std::vector<VehicleType> getMissingVehicles() const;
	TrainState getState() const { return m_state; }
	int getId() const { return m_id; }
	Time getDelay() const { return m_delay; }
	Time getDepartureDelay() const { return m_actualDepTime - m_depTime; }
	Time getActualDepTime() const { return m_actualDepTime; }
	Time getActualArrTime() const { return m_arrTime + m_delay; }   
	int getAvgSpeed() const { return m_avgSpeed; }

	// ---- SETTERS ----
	void setState(const TrainState p_newState) { m_state = p_newState; }
	void setDelay(const Time p_delay) { m_delay = p_delay; }   //used then train leaves station to set the final delay
	void increaseDelay(const Time &p_delay) { m_delay += p_delay; m_actualDepTime += p_delay; }  //used while train is incomplete 
	/*
	Sets the average speed. Returns speed that was actually set, depending on engines max speed and routes max speed.

	@param p_avgSpeed the speed that caller wants to set
	@return the actual speed set
	*/
	int setAvgSpeed(const int p_avgSpeed);    
	
	// ----- LOGIC -------

	/*
	Adds a vehicle to the train. If no index is passed vehicle will be placed at the back of the train.

	@param p_vehicle the vehicle to be added
	@param index the position in the train where to insert the vehicle
	*/
	void addVehicle(const std::shared_ptr<Vehicle> p_vehicle, int index = -1);

	/*
	Decouples the last vehicle of the train and stores its id in a vector in order to be able to track it later.

	@return shared pointer to the decoupled vehicle or null pointer if no more vehicles
	*/
	std::shared_ptr<Vehicle> decoupleVehicle();

	/*
	Searches the train for a vehicle with the specified id.

	@param id id of the vehicle to search for
	@return shared pointer to the vehicle if found, nullptr otherwise
	*/
	std::shared_ptr<Vehicle> locateVehicle(const int id) const;

	/*
	Searches the vector of vehicles that have been coupled to this train.

	@param id id of the vehicle to search for
	@return true if vehicle has been coupled to this train, false otherwise
	*/
	bool containedVehicle(const int id) const;

private:
	TrainState m_state;
	std::vector<std::shared_ptr<Vehicle>> m_vehicles;
	std::vector<int> m_vehicleIds;    //store ids of vehicles for tracking vehicle movement 
	Time m_delay;
	Time m_actualDepTime;
	int m_avgSpeed;
};

#endif // TRAIN_H