
#include <sstream>
#include "Route.h"



Route::~Route()
{
}

std::vector<std::string> Route::getVehicleTypes() const
{
	std::vector<std::string> types;
	for (VehicleType t : m_vehicleTypes)
		types.push_back(vehicleTypeStrings[static_cast<size_t>(t)]);

	return types;
}

std::istream & operator>>(std::istream & instream, Route & route)
{
	int id, maxSpeed;
	std::string depStr, arrStr;
	Time depTime, arrTime;

	instream >> id;
	instream.get();  // read whitespace;
	std::getline(instream, depStr, ' ');
	std::getline(instream, arrStr, ' ');
	instream >> depTime >> arrTime >> maxSpeed;

	route.setId(id);
	route.setDepStation(depStr);
	route.setArrStation(arrStr);
	route.setDepTime(depTime);
	route.setArrTime(arrTime);
	route.setMaxSpeed(maxSpeed);
	
	instream.get();   //remove newline character
	std::string vehicles;
	getline(instream, vehicles);
	std::istringstream vehicleStream(vehicles);
	int vehicle;
	while (vehicleStream >> vehicle)
		route.addVehicleType(static_cast<VehicleType>(vehicle));

	return instream;
}

std::ostream & operator<<(std::ostream & outstream, const Route & route)
{
	std::vector<std::string> vehicles = route.getVehicleTypes();
	outstream << route.getId() << ' '
		<< route.getDepStation() << ' '
		<< route.getArrStation() << ' '
		<< formatTime(route.getDepTime()) << ' '
		<< formatTime(route.getArrTime()) << ' '
		<< route.getMaxSpeed() << ' ';

	for (auto &v : vehicles)
		outstream << '[' << v << ']' << ' ';

	return outstream;
}
