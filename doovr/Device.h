#pragma once
#include "Utilities.h"

#include "vrpn/vrpn_Tracker.h"
#include "vrpn/vrpn_Button.h"
#include "vrpn/vrpn_Analog.h"
#include "vrpn/quat.h"

#include <iostream>

//! A class that handles vrpn connected devices
/*!
* 
*/
class Device {
	public:
		//! A Constructor 
		/*!
		*	Create the device class, connect vrpn callback functions.
		*/
		Device(bool analog, bool button, bool tracker, std::string name);
		//! A destructor
		~Device();

		//! Collects data from the vrpn server.
		void sendtoMainloop();

		//! Get position vector of the device position
		float* getTrackerPosition();
		//! Get the rotation matrix for the device
		float* getTrackerRotation();
		//! Get analog position of the device
		float* getAnalogPosition();
		//! Get button state
		bool getButtonState();

		//! Set position vector of the device position to a variable
		void setTrackerPosition(float t[3]);
		//! Set the rotation matrix for the device to a variable
		void setTrackerRotation(double o[16]);
		
		//! Set button state to a variable
		void setButtonState(bool b);
		//! Set analog position of the device to a variable
		void setAnalogPosition(float pos[2]);

		//! vrpn Analog tracker
		vrpn_Analog_Remote* vrpnAnalog = nullptr;
		//! vrpn Button tracker
		vrpn_Button_Remote* vrpnButton = nullptr;
		//! vrpn Position tracker
		vrpn_Tracker_Remote* vrpnTracker = nullptr;

	private:
		//! Addidional address to devices position tracker
		std::string additionalAddress;
		//! Constant local address
		const std::string LOCAL = "@localhost";
	
		//! Saved variable from setTrackerPosition
		float trackerPosition[3];
		//! Saved variable from setTrackerRotation
		float trackerRotation[16];
		//! Saved variable from setAnalogPosition
		float analogPos[3];
		//! Saved variable from setButtonState
		bool button;
};
