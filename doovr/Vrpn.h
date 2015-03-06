#pragma once
#include "Utilities.h"

#include "vrpn/vrpn_Tracker.h"
#include "vrpn/vrpn_Button.h"
#include "vrpn/vrpn_Analog.h"
#include "vrpn/quat.h"

#include <iostream>

class Vrpn
{
public:
	Vrpn(bool analog, bool button, bool tracker, std::string name);
	~Vrpn();
	void connectDevices();
	void sendtoMainloop();

	// Get functions
	glm::mat4 getTrackerTransform();
	bool getButtonState();
	glm::vec2 getAnalogPosition();

	// Set functions
	void setTrackerTransform(glm::mat4 t);
	void setButtonState(vrpn_BUTTONCB b);
	void setAnalogPosition(glm::vec2 pos);

	// Open the connection to trackers
	vrpn_Analog_Remote* vrpnAnalog = nullptr;
	vrpn_Button_Remote* vrpnButton = nullptr;
	vrpn_Tracker_Remote* vrpnTracker = nullptr;

private:
	int done = 0;
	std::string additionalAddress;
	std::string LOCAL = "@localhost";
	
	glm::mat4 trackerTransform = { 1.0, 0.0, 0.0, 0.0, 
								  0.0, 1.0, 0.0, 0.0, 
								  0.0, 0.0, 1.0, 0.0,
								  0.0, 0.0, 0.0, 1.0 };
	glm::vec2 analogPos = { 0.0, 0.0 };
	//buttons
	//analogs
	vrpn_BUTTONCB button;
};
