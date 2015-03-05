#pragma once
#include "Utilities.h"

#include "vrpn/vrpn_Tracker.h"
#include "vrpn/vrpn_Button.h"
#include "vrpn/vrpn_Analog.h"

#include <iostream>

class Vrpn
{
public:
	Vrpn(bool analog, bool button, bool tracker, std::string name);
	~Vrpn();
	void connectDevices();
	void sendtoMainloop();

	// Open the connection to trackers
	vrpn_Analog_Remote* vrpnAnalog = nullptr;
	vrpn_Button_Remote* vrpnButton = nullptr;
	vrpn_Tracker_Remote* vrpnTracker = nullptr;

private:
	int done = 0;
	std::string additionalAddress;
	std::string LOCAL = "@localhost";
	//glm::mat4 transform;
	//vector positions
	//buttons
	//analogs
	//vrpn_BUTTONCB
};
