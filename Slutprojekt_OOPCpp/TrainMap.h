

#ifndef TRAINMAP_H
#define TRAINMAP_H

#include <string>
#include <map>

class TrainMap
{
public:
	TrainMap();
	~TrainMap();

	int operator() (const std::string &a, const std::string &b);

	void readFromFile();

	void printAll();
private:
	std::map<std::string, std::map<std::string, int>> m_distances;

	int findDistance(const std::string &a, const std::string &b);
};



#endif // !TRAINMAP_H


