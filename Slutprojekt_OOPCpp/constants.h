

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>

enum class VehicleType {
	SeatedCoach = 0, SleeperCoach, OpenGoods, CoveredGoods, ElectricEngine, DieselEngine
};

enum class TrainState {
	NOT_ASSEMBLED = 0, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED
};

enum class LogLevel {
	LOW = 0, NORMAL, HIGH
};

const std::vector<std::string> vehicleTypeStrings = {
	"Seated Coach",
	"Sleeper Coach",
	"Open Goods Wagon",
	"Covered Goods Wagon",
	"Electric Engine",
	"Diesel Engine"
};

const std::vector<std::string> trainStateStrings = {
	"NOT ASSEMBLED",
	"INCOMPLETE",
	"ASSEMBLED",
	"READY",
	"RUNNING",
	"ARRIVED",
	"FINISHED"
};

const std::vector<std::string> logLevelStrings = {
	"Low",
	"Normal",
	"High"
};

#endif // CONSTANTS_H


