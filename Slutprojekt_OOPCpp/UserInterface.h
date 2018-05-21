

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "menu.h"
#include "RailwayCompany.h"

class UserInterface
{
public:
	UserInterface(RailwayCompany *p_railway)
		:m_railway(p_railway) {
		setupMenus();
	};
	~UserInterface();

	void run();

private:
	RailwayCompany * m_railway;
	Menu startMenu;
    Menu simMenu;
	Menu logLevelMenu;
	Menu trainMenu;
	Menu stationMenu;
	Menu vehicleMenu;

	void setupMenus();

	void locateVehicle();
};

#endif //!USERINTERFACE_H