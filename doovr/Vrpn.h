#pragma once

#include "vrpn/vrpn_Tracker.h"
#include "vrpn/vrpn_Button.h"
#include "vrpn/vrpn_Analog.h"

class Vrpn
{
public:
	Vrpn()
	{
		// Open the connection to trackers
		vrpn_Analog_Remote* vrpnAnalog = new vrpn_Analog_Remote("Wand@localhost");
		vrpn_Button_Remote* vrpnButton = new vrpn_Button_Remote("Wand@localhost");
		vrpn_Tracker_Remote* vrpnTracker = new vrpn_Tracker_Remote("IS900@localhost");
	};
	~Vrpn();

	void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a);
	void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b);
	void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t);

	void connectDevices();

	// Open the connection to trackers
	vrpn_Analog_Remote* vrpnAnalog;
	vrpn_Button_Remote* vrpnButton;
	vrpn_Tracker_Remote* vrpnTracker;

private:
	int done = 0;






};

