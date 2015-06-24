#pragma once
#include "Wand.h"
#include "Utilities.h"

#include <map>

#include "vrpn/vrpn_Tracker.h"
#include "vrpn/vrpn_Button.h"
#include "vrpn/vrpn_Analog.h"
#include "vrpn/quat.h"
#include <iostream>


//! A class that handles vrpn connected devices
/*!
*
*/
class Vrpn : public Wand
{
public:
	//! A Constructor 
	/*!
	*	Create the Vrpn class, connect vrpn callback functions.
	*/
	Vrpn(bool analog, bool button, bool tracker, std::string name);
	//! A destructor
	~Vrpn();

	//! Collects data from the vrpn server.
	void sendtoMainloop();

	//! Get analog position of the device
	float* getAnalogPosition() { return analogPos; }
	//! Get button state
	bool getButtonState() { return buttonState; }
	//! Get button number
	int getButtonNumber() { return buttonNumber; }

	//! Set position vector of the device position to a variable
	virtual void setWandPosition(double* t);
	//! Set the rotation matrix for the device to a variable
	virtual void setWandOrientation(double* o);

	virtual void setWandTransform(float* T);

	//! Set button state to a variable
	void setButtonState(bool b);
	//! Set button number to a variable
	void setButtonNumber(int b);
	//! Set analog position of the device to a variable
	void setAnalogPosition(float* pos);

private:
	//! vrpn Analog tracker
	vrpn_Analog_Remote* vrpnAnalog = nullptr;
	//! vrpn Button tracker
	vrpn_Button_Remote* vrpnButton = nullptr;
	//! vrpn Position tracker
	vrpn_Tracker_Remote* vrpnTracker = nullptr;

	//! Addidional address to devices position tracker
	std::string additionalAddress;
	//! Constant local address
	std::string LOCAL = "@localhost";
	std::string VORTEX = "@130.236.142.1";

	//! Saved variable from setAnalogPosition
	float analogPos[2];
	//! Saved variable from setButtonState
	bool buttonState;
	//! Saved variable from setButtonNumber
	int buttonNumber;
};

