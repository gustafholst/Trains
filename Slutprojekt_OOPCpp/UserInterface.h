

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
	~UserInterface();

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

	void seedSimulation();

	void setupMenus();
	void setupSimulationMenu();
	void setupVehicleMenu();
	void setupStationMenu();

	void locateVehicle();

	void printStation();
	void displayAllStationNames();
};

void printVehicle(std::ostream &os, std::shared_ptr<const Vehicle> v);

#endif //!USERINTERFACE_H