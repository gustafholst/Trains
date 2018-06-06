/*
* TrainMap.h
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Declares the TrainMap class.
*
*/

#ifndef TRAINMAP_H
#define TRAINMAP_H

#include <string>
#include <map>

class TrainMap
{
public:
	TrainMap() = default;

	//overloaded call operator returns the distance betweeen two stations
	int operator() (const std::string &a, const std::string &b);

	void readFromFile();

	void printAll();   //for debug purpose only
private:
	std::map<std::string, std::map<std::string, int>> m_distances;
};

#endif // !TRAINMAP_H


