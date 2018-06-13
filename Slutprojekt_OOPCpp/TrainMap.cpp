/*
* TrainMap.cpp
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Defines the TrainMap class.
*
*/

#include <fstream>
#include <iostream>
#include "TrainMap.h"
#include "constants.h"

std::string TRAIN_MAP_FILE = "TrainMap.txt";

int TrainMap::operator()(const std::string & a, const std::string & b)
{
	if (m_distances[a][b] == 0)        // if dep - arr is undefined
		return m_distances[b][a];	   //return arr - dep

	return m_distances[a][b];
}

void TrainMap::readFromFile()
{
	std::ifstream inFile(TRAIN_MAP_FILE);
	if (inFile.is_open())
	{
		std::string tmpDep, tmpArr;
		int tmpDist;
		while (std::getline(inFile, tmpDep, ' '))
		{
			std::getline(inFile, tmpArr, ' ');
			inFile >> tmpDist;
			inFile.ignore(2, '\n');   //adjusted for Linux

			m_distances[tmpDep][tmpArr] = tmpDist;
		}
	}
	else {
		throw std::runtime_error("File " + TRAIN_MAP_FILE + " could not be opened");
	}
}

void TrainMap::printAll()
{
	for (auto &x : m_distances)
	{
		for (auto &y : x.second)
			std::cout << x.first << " - " << y.first << " " << y.second << std::endl;
	}
}