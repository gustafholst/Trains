
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
		:Route(route), m_state(TrainState::NOT_ASSEMBLED), m_delay(0), m_avgSpeed(0) {}
	Train(const int p_id, const std::string &p_depStation, const std::string &p_arrStation, const Time &p_depTime, const Time &p_arrTime)
		:Route(p_id, p_depStation, p_arrStation, p_depTime, p_arrTime) {}
	~Train();

	std::vector<std::shared_ptr<Vehicle>> getVehicles() const { return m_vehicles; }
	TrainState getState() const { return m_state; }

	Time getDelay() const { return m_delay; }
	Time getActualDepTime() const { return m_depTime + m_delay; }
	Time getActualArrTime() const { return m_arrTime + m_delay; }   //calculate arrival time based on speed!!
	int getAvgSpeed() const { return m_avgSpeed; }

	void setState(const TrainState p_newState) { m_state = p_newState; }
	void increaseDelay(const Time &p_delay) { m_delay += p_delay; }
	int setAvgSpeed(const int p_avgSpeed);    //returns speed that was actually set (depending on engines max speed and routes max speed)
	void setDelay(const Time p_delay) { m_delay = p_delay; }
	void addVehicle(const std::shared_ptr<Vehicle> &p_vehicle, int index = -1);

	//void decoupleVehicle

	std::shared_ptr<Vehicle> locateVehicle(const int id) const;

private:
	TrainState m_state;
	Time m_delay;
	std::vector<std::shared_ptr<Vehicle>> m_vehicles;
	int m_avgSpeed;
};

#endif // TRAIN_H