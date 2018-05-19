
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

using namespace std;

int main()
{
	cout << "#######################################################################################" << endl;

	TrainMap distance;
	distance.readFromFile();
	distance.printAll();

	cout << "#######################################################################################" << endl;

	RailwayCompany company;
	company.loadStations();
	company.printAllStationNames();

	cout << "#######################################################################################" << endl;

	company.loadTimetable();
	company.printTimetable();

	cout << "#######################################################################################" << endl;

	//vector<unique_ptr<Vehicle>> vehicles;
	//
	//ifstream inFile("TrainStations.txt");
	//if (inFile.is_open())
	//{
	//	string stationName;
	//	while (getline(inFile, stationName, ' ')) //get the station name
	//	{
	//		cout << stationName << endl;

	//		string row;
	//		getline(inFile, row);  //get rest of row

	//		size_t pos = row.find('(', 0);
	//		cout << pos << endl;
	//		while (pos != string::npos) {
	//			//cout << row.substr(pos+1, row.size()) << endl;
	//			istringstream stream(row.substr(pos+1, 20));  // 20 = 4*4 + 4 (max size of 4 4digit parameters within brackets (xxxx xxxx xxxx xxxx))
	//			int param[4];  // array for parameters read from file [0]->id [1]->vehicle type [2]->typedependent [3]->typedependent
	//			int count = 0;
	//			while (stream >> param[count++]);  //read parameters (3 or 4)

	//			VehicleType type = static_cast<VehicleType>(param[1]);   //param[1] contains vehicle type

	//			if (type == VehicleType::SeatedCoach)
	//			{
	//				vehicles.push_back(unique_ptr<Vehicle>(new SeatedCoach(param[0], param[2], param[3])));  // id, numSeats, internet
	//			}
	//			else if (type == VehicleType::SleeperCoach)
	//			{
	//				vehicles.push_back(unique_ptr<Vehicle>(new SleeperCoach(param[0], param[2])));  // id, numBeds
	//			}
	//			else if (type == VehicleType::OpenGoods)
	//			{
	//				vehicles.push_back(unique_ptr<Vehicle>(new OpenGoods(param[0], param[2], param[3])));  // id, capacity, area
	//			}
	//			else if (type == VehicleType::CoveredGoods)
	//			{
	//				vehicles.push_back(unique_ptr<Vehicle>(new CoveredGoods(param[0], param[2])));  // id, volume
	//			}
	//			else if (type == VehicleType::ElectricLoc)
	//			{
	//				vehicles.push_back(unique_ptr<Vehicle>(new ElectricLoc(param[0], param[2], param[3])));  // id, maxSpeed, effect
	//			}
	//			else if (type == VehicleType::DieselLoc)
	//			{
	//				vehicles.push_back(unique_ptr<Vehicle>(new DieselLoc(param[0], param[2], param[3])));  // id, maxSpeed, fuelConsumption
	//			}

	//			pos = row.find('(', pos+1);
	//		}
	//	}
	//}

	//cout << "Number of vehicles: " << vehicles.size() << endl;

	//cout << vehicles[740]->getFuelConsumption() << endl;

	//stable_sort(vehicles.begin(), vehicles.end(), [](auto &v1, auto &v2) {
	//	return v1->getType() < v2->getType();
	//});

	//for (auto &v : vehicles)
	//{
	//std::cout << "==========================================\n";
	//std::cout << "Vehicle id: " << v->getId() << "\nVehicle type: " << static_cast<int>(v->getType()) << std::endl;
	//std::cout << "==========================================\n";
	//}

	//int a = 2;
	//cout << typeid(a).name() << endl;

	//cout << typeid(*vehicles[0]).name() << endl;
	//cout << typeid(*vehicles[300]).name() << endl;
	//cout << typeid(*vehicles[740]).name() << endl;
}