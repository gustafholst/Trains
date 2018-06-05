
#include <functional>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>
#include "UserInterface.h"
#include "auxilliary.h"


bool UserInterface::run()
{
	while (startMenu.display(m_simulation) && !resetSim);  //display until exit option or reset option is chosen
	return resetSim;  //if true, new instances of Simulation and TrainCompany will be instantiated.
}

void UserInterface::seedSimulation()
{
	m_railway->createTrains();    //create train objects for every route
}

void UserInterface::prepareSimulation()
{
	m_simulation->setupSimulation(m_railway);  //place assembly events for all trains in the event queue
	m_railway->makeInitialVehicleInventory();  //count vehicles at every station (for comparison afterwards)
	m_simulation->startSimulation();           //process all events up until start time (if any)
}

void UserInterface::runSimulation()
{
	while (simMenu.display(m_simulation) && !m_simulation->isFinished());  //keep displaying sim menu until user choses return option (for start menu)
																		   //or simulation is finished
	if (m_simulation->isFinished())
	{
		//### simulation is finished ###
		m_simulation->writeToFile();    //print log file with all the events
		m_allTrains = m_railway->getAllTrains();  //get pointers to all trains

												  //disable menu items only applicable during simulation
		for (size_t item = 0; item < 4; ++item)
			simMenu.disableItem(item);

		simMenu.enableItem(5);     //enable print statistics option
		simMenu.enableItem(6);     //enable view all events option
		trainMenu.enableItem(3);   //enable view delayed trains option
		trainMenu.enableItem(4);   //trains that never left station
		vehicleMenu.enableItem(2);  //enable vehicle history option

		while (simMenu.display(m_simulation));   //keep displaying menu until user is done
	}
}

void UserInterface::setupMenus()
{
	setupStartMenu();
	setupVehicleMenu();
	setupStationMenu();
	setupTrainMenu();
	setupSimulationMenu();
	setupLogLevelMenu();
}

void UserInterface::setupStartMenu()
{
	startMenu.setHead("Start menu");
	startMenu.addItem("Change start time", true, [this]() {
		changeStartTime();
	});
	startMenu.addItem("Change end time", true, [this]() {
		changeEndTime();
	});
	startMenu.addItem("Start simulation", true, [this]() {
		//disable menu items only applicable during simulation (they have already been displayed and are not needed anymore)
		for (size_t item = 0; item < 3; ++item)
			startMenu.disableItem(item);  //change start/end time, start simulation

		startMenu.enableItem(3);   //enable back to simulation option
		startMenu.enableItem(4);   //enable restart simulation

		prepareSimulation();
		runSimulation();
	});
	startMenu.addItem("Back to simulation", false, [this]() {
		if (m_simulation->isFinished())
			while (simMenu.display(m_simulation));   //keep displaying menu until user is done
		else
			runSimulation();
	});
	startMenu.addItem("Restart simulation", false, [this]() {
		resetSim = true;
	});
	
}

void UserInterface::setupSimulationMenu()
{
	simMenu.setHead("Simulation menu");
	simMenu.addItem("Change interval", true, [this]() {
		changeInterval();
	});
	simMenu.addItem("Next event", true, [this]() {
		nextEvent();
	});
	simMenu.addItem("Run next interval", true, [this]() {
		nextInterval();
	});
	simMenu.addItem("Finish (Complete simulation)", true, [this]() {
		m_simulation->finishSimulation();
	});
	simMenu.addItem("Change log level", true, [this]() {
		logLevelMenu.display(m_simulation);
	});
	simMenu.addItem("Print statistics", false, [this]() {     //only display when simulation is finished
		displayStatistics();
	});
	simMenu.addItem("View all events", false, [this]() {     //only display when simulation is finished
		displayEventsHistory();
	});
	simMenu.addItem("Train menu...", true, [this]() {
		while (trainMenu.display(m_simulation));    //keep displaying until return option is chosen
	});
	simMenu.addItem("Station menu...", true, [this]() {
		while (stationMenu.display(m_simulation));    //keep displaying until return option is chosen
	});
	simMenu.addItem("Vehicle menu...", true, [this]() {
		while (vehicleMenu.display(m_simulation));	 //keep displaying until return option is chosen
	});
}

void UserInterface::setupVehicleMenu()
{
	vehicleMenu.setHead("Vehicle menu");
	vehicleMenu.addItem("Show vehicle by id", true, [this]() {
		locateVehicle();
	});
	vehicleMenu.addItem("Show all vehicles", true, [this]() {
		displayAllVehicles();
	});
	vehicleMenu.addItem("View vehicle history", false, [this]() {
		int searched = getIntInput("Input id number of vehicle: ", 0);
		const std::vector<std::shared_ptr<Event>> events = m_simulation->getVehicleEvents(searched);
		if (!events.empty())
		{
			for (auto &e : events)
			{
				printEvent(std::cout, e);
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << "-- The vehicle has not been used during simulation --" << std::endl;
		}
		
		goOn("Press <ENTER> to for menu...");
	});
	vehicleMenu.addItem("Change log level", true, [this]() {
		logLevelMenu.display(m_simulation);
	});
}

void UserInterface::setupStationMenu()
{
	stationMenu.setHead("Station menu");
	stationMenu.addItem("Show station names", true, [this]() {
		displayAllStationNames();
	});
	stationMenu.addItem("Show station by name", true, [this]() {
		displayStation();
	});
	stationMenu.addItem("Display vehicles at station", true, [this]() {
		displayVehiclesAtStation();
	});
	stationMenu.addItem("Change log level", true, [this]() {
		logLevelMenu.display(m_simulation);
	});
}

void UserInterface::setupLogLevelMenu()
{
	logLevelMenu.setHead("Log level menu");
	logLevelMenu.addItem("Low", true, [this]() {
		m_simulation->setLogLevel(LogLevel::LOW);
		std::cout << "-- Log level is set to low --" << std::endl;
		goOn("Press <ENTER> to go back...");
	});
	logLevelMenu.addItem("Normal", true, [this]() {
		m_simulation->setLogLevel(LogLevel::NORMAL);
		std::cout << "-- Log level is set to normal --" << std::endl;
		goOn("Press <ENTER> to go back...");
	});
	logLevelMenu.addItem("High", true, [this]() {
		m_simulation->setLogLevel(LogLevel::HIGH);
		std::cout << "-- Log level is set to high --" << std::endl;
		goOn("Press <ENTER> to go back...");
	});
}

void UserInterface::setupTrainMenu()
{
	trainMenu.setHead("Train menu");
	trainMenu.addItem("Search train by id", true, [this]() {
		displayTrain();
	});
	trainMenu.addItem("View train history", true, [this]() {
		displayTrainHistory();
	});
	trainMenu.addItem("Change log level", true, [this]() {
		logLevelMenu.display(m_simulation);
	});
	trainMenu.addItem("View delayed trains", false, [this]() {
		for (auto &t : m_allTrains)
		{
			if (t->getDelay() > 0 && t->getState() == TrainState::FINISHED)
			{
				printTrain(std::cout, t, m_simulation->getLogLevel());
				std::cout << std::endl;
			}
		}

		goOn("Press <ENTER> for menu...");
	});
	trainMenu.addItem("View trains that never left the station", false, [this]() {
		for (auto &t : m_allTrains)
		{
			if (t->getState() != TrainState::FINISHED)
			{
				printTrain(std::cout, t, m_simulation->getLogLevel());
				std::cout << std::endl;
				sepLine(std::cout, 80, '-');
			}
		}

		goOn("Press <ENTER> for menu...");
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
	Time from = m_simulation->getCurrentTime();
	std::vector<std::shared_ptr<Event>> latestEvents = m_simulation->getNextInterval();
	Time to = m_simulation->getCurrentTime();
	sepLine(std::cout, 30, '=');
	std::cout << "Events between " << formatTime(from) << " and " << formatTime(to) << std::endl;
	sepLine(std::cout, 30, '=');
	for (auto e : latestEvents)
	{
		printEvent(std::cout, e);
		std::cout << std::endl;
	}
		
	goOn("Press <ENTER> for menu...");
}

void UserInterface::changeInterval()
{
	Time newInterval = getTimeInput("New interval: ");
	m_simulation->changeInterval(newInterval);
	//std::cout << "-- interval is changed --" << std::endl;
}

void UserInterface::changeStartTime()
{
	while (true)
	{
		Time newStartTime = getTimeInput("New start time: ");
		
		if (m_simulation->changeStartTime(newStartTime))
			break;
		else 
		{
			std::cout << "-- Start time cannot be before end time --" << std::endl;
			goOn("Press <ENTER> for menu...");
		}	
	}
}

void UserInterface::changeEndTime()
{
	while (true)
	{
		Time newEndTime = getTimeInput("New end time: ");

		if (m_simulation->changeEndTime(newEndTime))
			break;
		else
		{
			std::cout << "-- End time cannot be before start time --" << std::endl;
			goOn("Press <ENTER> for menu...");
		}
	}
}

void UserInterface::locateVehicle()
{
	using namespace std;

	int searched = getIntInput("Input id number of vehicle: ", 0);

	auto v = m_railway->locateVehicle(searched);    //returns a tuple (vehicle, train, station)
	auto vehicle = get<0>(v);
	auto train = get<1>(v);
	auto station = get<2>(v);
	if (vehicle)
	{
		if (station)
		{
			printVehicle(cout, vehicle, m_simulation->getLogLevel());
			cout << endl << "Vehicle currently at station: " << station->getName() << endl;
		}
		else if (train)
		{
			printVehicle(cout, vehicle, m_simulation->getLogLevel());
			cout << endl << "Vehicle currently part of train: " << endl;
			printTrain(std::cout, train, m_simulation->getLogLevel());
			cout << endl;
		}
	}

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayStation()
{
	std::string sName = getStringInput("Station name: ");
	const TrainStation *station = m_railway->getStation(sName);
	if (station != nullptr)
	{
		printStation(std::cout, station, m_simulation->getLogLevel());   //print station info according to current log level
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
		std::cout << std::endl << "Vehicles currently at station " << sName << std::endl;
		sepLine(std::cout, sName.size() + 32, '=');
		std::vector < std::shared_ptr<Vehicle>> vehicles = station->getAllVehicles();
		std::for_each(vehicles.cbegin(), vehicles.cend(), [this](const std::shared_ptr<Vehicle> &v) {
			printVehicle(std::cout, v, m_simulation->getLogLevel());
			std::cout << std::endl;
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

void UserInterface::displayAllVehicles()
{
	std::vector<std::shared_ptr<Vehicle>> allVehicles = m_railway->getAllVehicles();
	for (auto &v : allVehicles)
	{
		printVehicle(std::cout, v, m_simulation->getLogLevel());   //print vehicle info according to current log level
		std::cout << std::endl;
	}

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayTrain()
{
	int trainId = getIntInput("Train id: ");
	std::shared_ptr<Train> train = m_railway->locateTrain(trainId);

	if (train)
	{
		printTrain(std::cout, train, m_simulation->getLogLevel());   //print train info according to current log level
		std::cout << std::endl;
	}
	else
	{
		std::cout << "No train found" << std::endl;
	}

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayTrainHistory()
{
	int trainId = getIntInput("Train id: ");

	std::vector<std::shared_ptr<Event>> events = m_simulation->getTrainEvents(trainId);

	if (!events.empty())
	{
		for (auto e : events)
		{
			printEvent(std::cout, e);
			std::cout << std::endl;
		}	
	}	
	else
		std::cout << "No events found" << std::endl;

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayStatistics()
{
	int numDelayed = 0, numNoDeparture = 0;
	Time totalDelay(0);
	Time totalDepDelay(0);

	for (auto train : m_allTrains)
	{
		if (train->getState() == TrainState::FINISHED)
		{
			Time delay = train->getDelay();
			if (delay > 0)  
			{
				totalDelay += delay;   //accumulate total delay (arrival delay)
				++numDelayed;     //count number of delayed trains (arrival delay)
			}

			totalDepDelay += train->getDepartureDelay();  //accumulate total departure delay
		}
		else  //if trains state is not finished -> it got stuck in assembled or ready state
		{
			++numNoDeparture;
		}
	}

	sepLine(std::cout, 55, '=');
	std::cout << "Simulation statistics" << std::endl;
	sepLine(std::cout, 21, '-');
	std::cout << std::left << std::setw(50) << "Simulation end time:" << std::right << std::setw(5) << (m_simulation->getCurrentTime()) << std::endl;
	std::cout << std::left << std::setw(50) << "Number of delayed trains:" << std::right << std::setw(5) << numDelayed << std::endl;
	std::cout << std::left << std::setw(50) << "Number of trains that never left the station:" << std::right << std::setw(5) << numNoDeparture << std::endl;
	std::cout << std::left << std::setw(50) << "Total delay time:" << std::right << std::setw(5) << formatTime(totalDelay) << std::endl;
	std::cout << std::left << std::setw(50) << "Total delay time at departure:" << std::right << std::setw(5) << formatTime(totalDepDelay) << std::endl;

	//print table displaying vehicle count at every station
	std::cout << std::endl << "Number of vehicles before and after simulation" << std::endl;
	std::cout << std::left << std::setw(20) << "Station" << std::right << std::setw(12) << "Before" << std::setw(12) << "After" << std::endl;
	std::cout << std::left << std::setw(20) << "-------" << std::right << std::setw(12) << "------" << std::setw(12) << "-----" << std::endl;
	const std::map<std::string, int> initialVehicleCount = m_railway->getInitialVehicleCount();
	std::for_each(initialVehicleCount.cbegin(), initialVehicleCount.cend(), [this](const std::pair<std::string, int> &station) {
		TrainStation* s = m_railway->getStation(station.first);
		int finalCount = s->getNumVehicles();
		std::cout << std::left << std::setw(20) << station.first << std::right << std::setw(12) << station.second << std::setw(12) << finalCount << std::endl;
	});

	sepLine(std::cout, 55, '=');
	std::cout << "see submenus (station/train/vehicle) for more details" << std::endl;

	goOn("Press <ENTER> for menu...");
}

void UserInterface::displayEventsHistory()
{
	std::vector<std::shared_ptr<Event>> events = m_simulation->getAllEvents();
	for (auto e : events)
	{
		printEvent(std::cout, e);
		std::cout << '\n';
	}

	goOn("Press <ENTER> for menu...");
}

void printVehicle(std::ostream & os, std::shared_ptr<const Vehicle> v, LogLevel p_logLevel)
{
	using namespace std;
	os << "[" << vehicleTypeStrings[static_cast<int>(v->getType())] << "] " <<
		"id: " << v->getId();
	
	if (p_logLevel == LogLevel::NORMAL || p_logLevel == LogLevel::HIGH)
	{
		os << ", " <<
			(v->getNumSeats() != -1 ? "Seats: " + std::to_string(v->getNumSeats()) + ", " : "");

		if (v->getType() == VehicleType::SeatedCoach)
			os << (v->hasInternet() ? "internet onboard " : "no internet onboard ");

		os << (v->getNumBeds() != -1 ? "Beds: " + std::to_string(v->getNumBeds()) + " " : "") <<
			(v->getCapacity() != -1 ? "Capacity: " + std::to_string(v->getCapacity()) + ", " : "") <<
			(v->getArea() != -1 ? "Area: " + std::to_string(v->getArea()) + " m^2 " : "") <<
			(v->getVolume() != -1 ? "Volume: " + std::to_string(v->getVolume()) + " m^3 " : "") <<
			(v->getMaxSpeed() != -1 ? "Max speed: " + std::to_string(v->getMaxSpeed()) + " km/h, " : "") <<
			(v->getEffect() != -1 ? "Effect: " + std::to_string(v->getEffect()) + " kW " : "") <<
			(v->getFuelConsumption() != -1 ? "Fuel consumption: " + std::to_string(v->getFuelConsumption()) + " l/h " : "");
	}
}

void printStation(std::ostream & os, const TrainStation * station, LogLevel p_logLevel)
{
	std::string name = station->getName();
	os << "Vehicle count at station " << name << std::endl;
	sepLine(os, name.size() + 27, '=');

	
	std::vector<std::pair<VehicleType, int>> vehicleCounts = station->getVehicleCounts();
	for (std::pair<VehicleType, int> count : vehicleCounts)
	{ 
		os << vehicleTypeStrings[static_cast<int>(count.first)] << ": " << count.second << std::endl;
	}
	
	os << std::endl << "Trains currently at station " << name << std::endl;
	sepLine(os, name.size() + 30, '=');
	const std::vector<std::shared_ptr<Train>> trains = station->getTrains();
	for (std::shared_ptr<Train> train : trains)
	{
		printTrain(std::cout, train, p_logLevel);
		std::cout << std::endl;
	}
}

void printTrain(std::ostream & os, std::shared_ptr<const Train> t, LogLevel p_logLevel)
{
	os << "Train [" << t->getId() << "] (" << trainStateStrings[static_cast<int>(t->getState())] << ") ";
	if (p_logLevel > LogLevel::LOW)
	{
		os << "from " << t->getDepStation() << ' ' << t->getDepTime() << " (" << t->getActualDepTime()
			<< ") to " << t->getArrStation() << ' ' << t->getArrTime() << " (" << t->getActualArrTime() << ')'
			<< " delay (" << formatTime(t->getDelay()) << ") speed = " << t->getAvgSpeed() << " km/h";
	}	
	//if log level high, also print info about all vehicles in the train
	if (p_logLevel == LogLevel::HIGH)
	{
		TrainState s = t->getState();
		if (s != TrainState::NOT_ASSEMBLED || s != TrainState::FINISHED)
		{
			std::vector<std::shared_ptr<Vehicle>> vehicles = t->getVehicles();
			if (!vehicles.empty())
				os << std::endl;   //only add newline if therea re vehicles to display
			for (auto v : vehicles)
			{
				if (v)
				{
					printVehicle(os, v, p_logLevel);
					os << std::endl;
				}
			}
		}
		if (s == TrainState::INCOMPLETE)    //print missing vehicle types
		{
			os << "Missing vehicles:" << std::endl;
			std::vector<VehicleType> missing = t->getMissingVehicles();
			for (VehicleType type : missing)
			{
				os << vehicleTypeStrings[static_cast<size_t>(type)];
				os << std::endl;
			}
		}
	}
}

void printEvent(std::ostream & os, std::shared_ptr<const Event> e)
{
	os << *e;
}
