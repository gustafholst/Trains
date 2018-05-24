
#include <iostream>
#include "RailwayCompany.h"
#include "TrainMap.h"
#include "UserInterface.h"


int main()
{
	RailwayCompany company;
	try
	{
		company.loadStations();
		company.loadTimetable();
		company.loadMap();
	}
	catch (std::ios_base::failure &e)
	{
		std::cerr << e.what() << std::endl << "Exiting..." << std::endl;
		return 1;
	}
	
	Simulation simulation;

	UserInterface ui(&company, &simulation);
	ui.run();
}