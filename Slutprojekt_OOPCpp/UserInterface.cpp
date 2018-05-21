

#include "UserInterface.h"
#include "auxilliary.h"



UserInterface::~UserInterface()
{
}

void UserInterface::run()
{
	while (true) {
		clearScreen();
		vehicleMenu.display();
		goOn("Press enter...");
	}
}

void UserInterface::setupMenus()
{
	vehicleMenu.addItem("Show vehicle by id", [this]() {
		locateVehicle();
	});
}

void UserInterface::locateVehicle()
{
	using namespace std;

	int searched = getIntInput("Input id number of vehicle: ", 0);

	auto v = m_railway->locateVehicle(searched);
	auto vehicle = get<0>(v);
	auto train = get<1>(v);
	auto station = get<2>(v);
	if (vehicle != nullptr)
	{
		cout << "Type:\t" << vehicleTypeStrings[static_cast<int>(vehicle->getType())] << endl <<
			"Seats:\t" << vehicle->getNumSeats() << endl <<
			"Beds:\t" << vehicle->getNumBeds() << endl <<
			"Capacity:\t" << vehicle->getCapacity() << endl <<
			"Area:\t" << vehicle->getArea() << endl <<
			"Volume:\t" << vehicle->getVolume() << endl <<
			"Max speed:\t" << vehicle->getMaxSpeed() << endl <<
			"Effect:\t" << vehicle->getEffect() << endl <<
			"Consumption:\t" << vehicle->getFuelConsumption() << endl;
		cout << "Found in station:\t" << station->getName() << endl;
	}
}
