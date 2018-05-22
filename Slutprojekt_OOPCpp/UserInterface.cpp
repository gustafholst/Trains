
#include <functional>
#include <algorithm>
#include "UserInterface.h"
#include "auxilliary.h"

UserInterface::~UserInterface()
{
}

void UserInterface::run()
{
	while (simMenu.display()) {
		goOn("Press enter...");
	}
}

void UserInterface::setupMenus()
{
	setupVehicleMenu();
	setupStationMenu();
	setupSimulationMenu();
}

void UserInterface::setupSimulationMenu()
{
	simMenu.setHead("Simulation menu");
	simMenu.addItem("Station menu...", [this]() {
		stationMenu.display();
	});
	simMenu.addItem("Vehicle menu...", [this]() {
		vehicleMenu.display();
	});
}

void UserInterface::setupVehicleMenu()
{
	vehicleMenu.setHead("Vehicle menu");
	vehicleMenu.addItem("Show vehicle by id", [this]() {
		locateVehicle();
	});
	vehicleMenu.addItem("Find vehicle type seatec coach in station 4", [this]() {
		printVehicle(std::cout, m_railway->findVehicleType());
	});
	
}

void UserInterface::setupStationMenu()
{
	stationMenu.setHead("Station menu");
	stationMenu.addItem("Show station names", [this]() {
		auto names = m_railway->getAllStationNames();
		for (auto &str : names)
			std::cout << str << std::endl;
	});
	stationMenu.addItem("Show station by name", [this]() {
		printStation();
	});
}

void UserInterface::locateVehicle()
{
	using namespace std;

	int searched = getIntInput("Input id number of vehicle: ", 0);

	auto v = m_railway->locateVehicle(searched);
	auto vehicle = get<0>(v);
	auto train = get<1>(v);
	auto station = get<2>(v);
	if (vehicle != nullptr)
	{
		printVehicle(cout, vehicle);
		cout << "Vehicle currently at station: " << station->getName() << endl;
	}
}

void UserInterface::printStation()
{
	std::string sName = getStringInput("Station name: ");
	const TrainStation *station = m_railway->getStation(sName);
	if (station != nullptr)
	{
		std::vector < std::shared_ptr<Vehicle>> vehicles = station->getAllVehicles();
		std::for_each(vehicles.cbegin(), vehicles.cend(), [](const std::shared_ptr<Vehicle> &v) {
		printVehicle(std::cout, v);
		});
	}
	else
	{
		std::cout << "No station found" << std::endl;
	}
}

void printVehicle(std::ostream & os, std::shared_ptr<const Vehicle> v)
{
	using namespace std;
	os << "[" << vehicleTypeStrings[static_cast<int>(v->getType())] << "] " <<
		"id: " << v->getId() << ", " <<
		(v->getNumSeats() != -1 ? "Seats: " + std::to_string(v->getNumSeats()) + ", " : "");

	if (v->getType() == VehicleType::SeatedCoach)
		os << (v->hasInternet() ? "internet onboard " : "no internet onboard ");

		os << (v->getNumBeds() != -1 ? "Beds: " + std::to_string(v->getNumBeds()) + " " : "") <<
		(v->getCapacity() != -1 ? "Capacity: " + std::to_string(v->getCapacity()) + ", " : "") <<
		(v->getArea() != -1 ? "Area: " + std::to_string(v->getArea()) + " m^2 " : "") <<
		(v->getVolume() != -1 ? "Volume: " + std::to_string(v->getVolume()) + " m^3 " : "") <<
		(v->getMaxSpeed() != -1 ? "Max speed: " + std::to_string(v->getMaxSpeed()) + " km/h, " : "") <<
		(v->getEffect() != -1 ? "Effect: " + std::to_string(v->getEffect()) + " kW " : "") <<
		(v->getFuelConsumption() != -1 ? "Fuel consumption: " + std::to_string(v->getFuelConsumption()) + " l/h " : "") << endl;
}
