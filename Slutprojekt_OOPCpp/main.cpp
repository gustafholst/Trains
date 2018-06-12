/*
* main.cpp
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Entry point for train simulation application.
*
*/

#include <iostream>
#include "RailwayCompany.h"
#include "TrainMap.h"
#include "UserInterface.h"

int main()
{
	bool reset = false;
	do
	{
		RailwayCompany company;
		try
		{
			company.loadStations();
			company.loadTimetable();
			company.loadMap();
		}
		catch (std::runtime_error &e)
		{
			std::cerr << e.what() << std::endl << "Exiting..." << std::endl;
			return 1;
		}

		Simulation simulation;
		UserInterface ui(&company, &simulation);
		reset = ui.run();
	} while (reset);
}