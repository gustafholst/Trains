

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "menu.h"
#include "RailwayCompany.h"
#include "Simulation.h"

class UserInterface
{
public:
	UserInterface(RailwayCompany *p_railway, Simulation * p_simulation)
		:m_railway(p_railway), m_simulation(p_simulation)
	{
		setupMenus();
		seedSimulation();
	};

	void run();

private:
	RailwayCompany * m_railway;
	Simulation * m_simulation;
	Menu startMenu;
    Menu simMenu;
	Menu logLevelMenu;
	Menu trainMenu;
	Menu stationMenu;
	Menu vehicleMenu;
	std::vector<std::shared_ptr<Train>> m_allTrains;   //for statistics when simulation is finished

	void seedSimulation();  //creates trains from the timetable and puts inital events in the event queue
	void runSimulation();

	void setupMenus();
	void setupStartMenu();
	void setupSimulationMenu();
	void setupLogLevelMenu();
	void setupTrainMenu();
	void setupStationMenu();
	void setupVehicleMenu();
	
	void nextEvent();
	void nextInterval();

	void changeInterval();
	void changeStartTime();
	void changeEndTime();
	void locateVehicle();

	void displayStation();
	void displayVehiclesAtStation();
	void displayAllStationNames();
	void displayAllVehicles();
	void displayTrain();
	void displayTrainHistory();
	void displayStatistics();
	void displayEventsHistory();
};

void printVehicle(std::ostream &os, std::shared_ptr<const Vehicle> v, LogLevel p_logLevel);
void printStation(std::ostream &os, const TrainStation *station, LogLevel p_logLevel);
void printTrain(std::ostream &os, std::shared_ptr<const Train> t, LogLevel p_logLevel);
void printEvent(std::ostream &os, std::shared_ptr<const Event> e);

#endif //!USERINTERFACE_H