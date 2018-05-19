

#ifndef VEHICLE_H
#define VEHICLE_H

#include "constants.h"

class Vehicle {
public:
	Vehicle(const int p_id) : m_id(p_id) {}
	virtual ~Vehicle() = default;

	virtual VehicleType getType() const = 0;
	int getId() const { return m_id; }

	virtual int getFuelConsumption() const { return -1; }
protected:
	const int m_id;
};

class SeatedCoach : public Vehicle {
public:
	SeatedCoach(const int p_id, const int p_numSeats, const bool p_internet)
		:Vehicle(p_id), m_numSeats(p_numSeats), m_internet(p_internet) {}

	VehicleType getType() const { return VehicleType::SeatedCoach; }
	int getNumSeats() const { return m_numSeats; }

private:
	const int m_numSeats;
	const bool m_internet;
};

class SleeperCoach : public Vehicle {
public:
	SleeperCoach(const int p_id, const int p_numBeds)
		:Vehicle(p_id), m_numBeds(p_numBeds) {}

	VehicleType getType() const { return VehicleType::SleeperCoach; }
	int getNumBeds() const { return m_numBeds; }

private:
	const int m_numBeds;
};

class OpenGoods : public Vehicle {
public:
	OpenGoods(const int p_id, const int p_capacity, const int p_area)
		:Vehicle(p_id), m_capacity(p_capacity), m_area(p_area) {}

	VehicleType getType() const { return VehicleType::OpenGoods; }
	int getCapacity() const { return m_capacity; }
	int getArea() const { return m_area; }
private:
	const int m_capacity;
	const int m_area;
};

class CoveredGoods : public Vehicle {
public:
	CoveredGoods(const int p_id, const int p_volume)
		:Vehicle(p_id), m_volume(p_volume) {}

	VehicleType getType() const { return VehicleType::CoveredGoods; }
	int getVolume() const { return m_volume; }

private:
	const int m_volume;
};

class Locomotive : public Vehicle {
public:
	Locomotive(const int p_id, const int p_maxSpeed)
		: Vehicle(p_id), m_maxSpeed(p_maxSpeed) {}
	virtual ~Locomotive() = default;

	int getMaxSpeed() { return m_maxSpeed; }

protected:
	const int m_maxSpeed;
};

class ElectricLoc : public Locomotive {
public:
	ElectricLoc(const int p_id, const int p_maxSpeed, const int p_effect)
		:Locomotive(p_id, p_maxSpeed), m_effect(p_effect) {}

	VehicleType getType() const override { return VehicleType::ElectricEngine; }
	int getEffect() const { return m_effect; }

private:
	const int m_effect;
};

class DieselLoc : public Locomotive {
public:
	DieselLoc(const int p_id, const int p_maxSpeed, const int p_fuelConsumption)
		:Locomotive(p_id, p_maxSpeed), m_fuelConsumption(p_fuelConsumption) {}

	VehicleType getType() const override { return VehicleType::DieselEngine; }  
	int getFuelConsumption() const override { return m_fuelConsumption; }
	
private:
	const int m_fuelConsumption;
};
#endif // VEHICLE_H



