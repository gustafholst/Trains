

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>


const int ASSEMBLY_TIME = 20;    // assembly takes place 30 min (20 + 10) before departure;
const int READY_TIME = 10;       // train comes to the platform 10 mins before departure;
const int RETRY_TIME = 10;       // if incomplete, a train will try to assemble every 10 minutes
const int DISASSEMBLY_TIME = 20; // disassembly takes place 20 mins after arrival

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


