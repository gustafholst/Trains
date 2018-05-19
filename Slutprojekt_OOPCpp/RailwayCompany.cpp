
#include <iostream>
#include <fstream>
#include "RailwayCompany.h"


RailwayCompany::RailwayCompany()
{
}


RailwayCompany::~RailwayCompany()
{
}

void RailwayCompany::loadStations()
{
	std::ifstream inFile("TrainStations.txt");
	if (inFile.is_open())
	{
		TrainStation tmpStation;
		while (inFile >> tmpStation) {
			m_stations.push_back(tmpStation);
			if (inFile.eof())
				break;
		}		
	}
	else
		std::cout << "TrainStations.txt could not be opened" << std::endl;  //throw exception instead
}

void RailwayCompany::loadTimetable()
{
	std::ifstream inFile("Trains.txt");

	if (inFile.is_open())
	{
		Route tmpRoute;
		while (inFile >> tmpRoute) {
			m_timetable.push_back(tmpRoute);
			if (inFile.eof())
				break;

			tmpRoute = Route();  //reinitialize in order to clear vehicle vector
		}
	}
	else
		std::cout << "Trains.txt could not be opened" << std::endl;  //throw exception
}
