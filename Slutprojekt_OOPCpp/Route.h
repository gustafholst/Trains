


#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>
#include "Time.h"
#include "constants.h"

class Route
{
public:
	Route() = default;
	Route(const Route &route) = default;
	Route(const int p_id, const std::string &p_depStation, const std::string &p_arrStation, const Time &p_depTime, const Time &p_arrTime)
		:m_id(p_id), m_depStation(p_depStation), m_arrStation(p_arrStation), m_depTime(p_depTime), m_arrTime(p_arrTime) {}
	virtual ~Route() {}

	int getId() const { return m_id; }
	std::string getDepStation() const { return m_depStation; }
	std::string getArrStation() const { return m_arrStation; }
	Time getDepTime() const { return m_depTime; }
	Time getArrTime() const { return m_arrTime; }
	int getMaxSpeed() const { return m_maxSpeed; }
	std::vector<std::string> getVehicleTypeNames() const;
	std::vector<VehicleType> getVehicleTypes() const { return m_vehicleTypes; }

	void setId(const int p_id) { m_id = p_id; }
	void setDepStation(const std::string &p_dep) { m_depStation = p_dep; }
	void setArrStation(const std::string &p_arr) { m_arrStation = p_arr; }
	void setDepTime(const Time &p_dep) { m_depTime = p_dep; }
	void setArrTime(const Time &p_arr) { m_arrTime = p_arr; }
	void setMaxSpeed(const int p_speed) { m_maxSpeed = p_speed; }
	void addVehicleType(const VehicleType type) { m_vehicleTypes.push_back(type); }

protected:
	int m_id;
	std::string m_depStation;
	std::string m_arrStation;
	Time m_depTime;
	Time m_arrTime;
	int m_maxSpeed;
	std::vector<VehicleType> m_vehicleTypes;
};

std::istream &operator >> (std::istream &instream, Route &route);
std::ostream &operator << (std::ostream &outstream, const Route &route);

#endif // !CONNECTION_H