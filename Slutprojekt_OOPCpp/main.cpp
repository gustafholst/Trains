
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


	/*Time t1(582);
	Time t2(701);
	Time t3(120);
	Time t4 = t1 - t2;

	std::cout << formatTime(t1) << std::endl;
	std::cout << formatTime(t2) << std::endl;
	std::cout << formatTime(t3) << std::endl;
	std::cout << formatTime(t4) << std::endl;*/
}