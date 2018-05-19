

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>

enum class VehicleType {
	SeatedCoach = 0, SleeperCoach, OpenGoods, CoveredGoods, ElectricEngine, DieselEngine
};

const std::vector<std::string> vehicleTypeStrings = {
	"Seated Coach",
	"Sleeper Coach",
	"Open Goods Wagon",
	"Covered Goods Wagon",
	"Electric Engine",
	"Diesel Engine"
};

#endif // CONSTANTS_H


