
#include <fstream>
#include <iostream>
#include "TrainMap.h"

TrainMap::TrainMap()
{
}


TrainMap::~TrainMap()
{
}

int TrainMap::operator()(const std::string & a, const std::string & b)
{
	return findDistance(a,b);
}

void TrainMap::readFromFile()
{
	std::ifstream inFile("TrainMap.txt");
	if (inFile.is_open())
	{
		std::string tmpDep, tmpArr;
		int tmpDist;
		while (std::getline(inFile, tmpDep, ' '))
		{
			std::getline(inFile, tmpArr, ' ');
			inFile >> tmpDist;
			inFile.get();

			m_distances[tmpDep][tmpArr] = tmpDist;
		}
	}
	else {
		throw std::ios_base::failure("File 'TrainMap.txt' could not be opened");
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

int TrainMap::findDistance(const std::string & a, const std::string & b)
{
	if (m_distances[a][b] == 0)        // if dep - arr is undefined
		return m_distances[b][a];	   //return arr -dep
	
	return m_distances[a][b];
}
