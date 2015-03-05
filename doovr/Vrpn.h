
#pragma once

#include "vrpn/vrpn_Tracker.h"
#include "vrpn/vrpn_Button.h"
#include "vrpn/vrpn_Analog.h"

class Vrpn
{
public:
	Vrpn();
	~Vrpn();
	void connectDevices();
	void sendtoMainloop();

	// Open the connection to trackers
	vrpn_Analog_Remote* vrpnAnalog;
	vrpn_Button_Remote* vrpnButton;
	vrpn_Tracker_Remote* vrpnTracker;

private:
	int done = 0;


};
