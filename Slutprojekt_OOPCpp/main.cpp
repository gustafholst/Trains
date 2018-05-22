
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <sstream>
#include <typeinfo>
#include "Vehicle.h"
#include "Time.h"
#include "RailwayCompany.h"
#include "Route.h"
#include "TrainMap.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	/*cout << "#######################################################################################" << endl;

	TrainMap distance;
	distance.readFromFile();
	distance.printAll();

	cout << "#######################################################################################" << endl;*/

	RailwayCompany company;
	company.loadStations();
	company.loadTimetable();
	company.loadMap();

	UserInterface ui(&company);
	ui.run();



	//company.printAllStationNames();

	/*cout << "#######################################################################################" << endl;

	
	company.printTimetable();

	cout << "#######################################################################################" << endl;*/

	
		

	//cout << typeid(*vehicles[0]).name() << endl;
	//cout << typeid(*vehicles[300]).name() << endl;
	//cout << typeid(*vehicles[740]).name() << endl;
}