
#include <functional>
#include <algorithm>
#include <sstream>
#include "UserInterface.h"
#include "auxilliary.h"

UserInterface::~UserInterface()
{
}

void UserInterface::run()
{
	while (simMenu.display(m_simulation));
}

void UserInterface::seedSimulation()
{
	m_railway->createTrains();
	m_railway->scheduleTrains(m_simulation);
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
	simMenu.addItem("Change interval", [this]() {
		changeInterval();
	});
	simMenu.addItem("Next event", [this]() {
		nextEvent();
	});
	simMenu.addItem("Run next interval", [this]() {
		nextInterval();
	});
	simMenu.addItem("Station menu...", [this]() {
		while (stationMenu.display());    //keep displaying until return option is chosen
	});
	simMenu.addItem("Vehicle menu...", [this]() {
		while (vehicleMenu.display());	 //keep displaying until return option is chosen
	});
}

void UserInterface::setupVehicleMenu()
{
	vehicleMenu.setHead("Vehicle menu");
	vehicleMenu.addItem("Show vehicle by id", [this]() {
		locateVehicle();
	});
	/*vehicleMenu.addItem("Find vehicle type seatec coach in station 4", [this]() {
		printVehicle(std::cout, m_railway->findVehicleType());
	});*/
	
}

void UserInterface::setupStationMenu()
{
	stationMenu.setHead("Station menu");
	stationMenu.addItem("Show station names", [this]() {
		displayAllStationNames();
	});
	stationMenu.addItem("Show station by name", [this]() {
		displayStation();
	});
}

void UserInterface::nextEvent()
{
	std::shared_ptr<Event> next = m_simulation->getNextEvent();
	if (next != nullptr)
	{
		printEvent(std::cout, next);
		std::cout << std::endl;
	}

	goOn("Press <ENTER> for menu..."); 
}

void UserInterface::nextInterval()
{
	std::vector<std::shared_ptr<Event>> latestEvents = m_simulation->getNextInterval();
	for (auto e : latestEvents)
	{
		printEvent(std::cout, e);
		std::cout << std::endl;
	}
		

	goOn("Press <ENTER> for menu...");
}

void UserInterface::changeInterval()
{
	Time newInterval;

	while (true)
	{
		std::stringstream stream;
		std::string input = getStringInput("New interval: ");
		try
		{
			stream << input << ' ';
			stream >> newInterval;
			break;
		}
		catch (std::ios_base::failure &)
		{
			std::cout << "Not a valid time" << std::endl;
		}
	}
	
	m_simulation->changeInterval(newInterval);
	std::cout << "-- interval is changed --" << std::endl;
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

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayStation()
{
	std::string sName = getStringInput("Station name: ");
	const TrainStation *station = m_railway->getStation(sName);
	if (station != nullptr)
	{
		printStation(std::cout, station);
	}
	else
	{
		std::cout << "No station found" << std::endl;
	}

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayVehiclesAtStation()
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

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayAllStationNames()
{
	auto names = m_railway->getAllStationNames();
	for (auto &str : names)
		std::cout << str << std::endl;

	goOn("Press <ENTER> for menu...");
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

void printStation(std::ostream & os, const TrainStation * station)
{
	std::vector<std::pair<VehicleType, int>> vehicleCounts = station->getVehicleCounts();
	for (std::pair<VehicleType, int> count : vehicleCounts)
	{ 
		os << vehicleTypeStrings[static_cast<int>(count.first)] << ": " << count.second << std::endl;
	}

	const std::vector<std::shared_ptr<Train>> trains = station->getTrains();
	for (std::shared_ptr<Train> train : trains)
	{
		printTrain(std::cout, train);
		std::cout << std::endl;
	}

}

void printTrain(std::ostream & os, std::shared_ptr<const Train> t)
{
	os << "Train [" << t->getId() << "] (" << trainStateStrings[static_cast<int>(t->getState())] << ") "
		<< "from " << t->getDepStation() << ' ' << t->getDepTime() << " (" << t->getActualDepTime()
		<< ") to " << t->getArrStation() << ' ' << t->getArrTime() << " (" << t->getActualArrTime() << ')'
		<< " delay (" << formatTime(t->getDelay()) << ") speed = " << t->getAvgSpeed() << " km/h";
}

void printEvent(std::ostream & os, std::shared_ptr<const Event> e)
{
	os << *e;
}
