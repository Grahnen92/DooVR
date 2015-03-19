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

		//! Get transformation matrix of the device
		glm::mat4 getTrackerTransform();
		//! Get position vector of the device position
		glm::vec3 getTrackerPosition();
		//! Get the rotation matrix for the device
		glm::mat4 getTrackerRotation();

		//! Get button state
		bool getButtonState();
		//! Get analog position of the device
		glm::vec2 getAnalogPosition();

		//! Set transformation matrix of the device to a variable
		void setTrackerTransform(glm::mat4 t);
		//! Set position vector of the device position to a variable
		void setTrackerPosition(glm::vec3 t);
		//! Set the rotation matrix for the device to a variable
		void setTrackerRotation(glm::mat4 t);

		//! Set button state to a variable
		void setButtonState(bool b);
		//! Set analog position of the device to a variable
		void setAnalogPosition(glm::vec2 pos);

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
		std::string LOCAL = "@localhost";
		std::string VORTEX = "@130.236.142.25";
	
		//! Saved variable from setTrackerTransform
		glm::mat4 trackerTransform = { 1.0, 0.0, 0.0, 0.0, 
									  0.0, 1.0, 0.0, 0.0, 
									  0.0, 0.0, 1.0, 0.0,
									  0.0, 0.0, 0.0, 1.0 };
		//! Saved variable from setTrackerPosition
		glm::vec3 trackerPosition = {0.0f,0.0f,0.0f };
		//! Saved variable from setAnalogPosition
		glm::vec2 analogPos = { 0.0, 0.0 };
		//! Saved variable from setButtonState
		bool button;
};
