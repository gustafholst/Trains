

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Time.h"


class Simulation
{
public:
	Simulation()
		:m_currentTime(0), m_interval(10) {}
	~Simulation();

	void changeInterval(const Time &p_newInterval) { m_interval = p_newInterval; }

private:
	Time m_currentTime;
	Time m_interval;
};

#endif //!SIMULATION_H