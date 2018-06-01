

#ifndef TRAINMAP_H
#define TRAINMAP_H

#include <string>
#include <map>

class TrainMap
{
public:
	TrainMap() = default;

	int operator() (const std::string &a, const std::string &b);

	void readFromFile();

	void printAll();   //for debug purpose only
private:
	std::map<std::string, std::map<std::string, int>> m_distances;
};

#endif // !TRAINMAP_H


