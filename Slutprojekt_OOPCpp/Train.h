
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include "Route.h"

class Train : public Route
{
public:
	Train(const int p_id, const std::string &p_depStation, const std::string &p_arrStation, const Time &p_depTime, const Time &p_arrTime)
		:Route(p_id, p_depStation, p_arrStation, p_depTime, p_arrTime) {}
	~Train();

private:
	
};

#endif // TRAIN_H