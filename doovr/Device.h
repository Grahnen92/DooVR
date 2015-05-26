#pragma once

#include "Utilities.h"
#include "linAlg.h"

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
    float *getTrackerPosition();

    //! Get the rotation matrix for the device
    float *getTrackerRotation();

    //! Get analog position of the device
    float *getAnalogPosition();

    //!
    float *getTransformMatrix() { return transformMatrix; };

    //! Get button state
    bool getButtonState();

    //! Get button number
    int getButtonNumber();


    //! Get both button number and the state, replaces the 2 button functions from above
    bool *getButton();

    //! Set position vector of the device position to a variable
    void setTrackerPosition(float *t);

    //! Set the rotation matrix for the device to a variable
    //void setTrackerRotation(double* o);
    void setTrackerRotation(float *o);

    //! Set button state to a variable
    void setButtonState(bool b);

    //! Set button number to a variable
    void setButtonNumber(int b);

    //! Set button number and the state
    void setButton(int n, bool b);

    //! Set analog position of the device to a variable
    void setAnalogPosition(float *pos);

    //!
    void setTransformMatrix(float *T);

    //! vrpn Analog tracker
    vrpn_Analog_Remote *vrpnAnalog = nullptr;
    //! vrpn Button tracker
    vrpn_Button_Remote *vrpnButton = nullptr;
    //! vrpn Position tracker
    vrpn_Tracker_Remote *vrpnTracker = nullptr;


    //!
    void print_transformMatrix();

private:
    //! Addidional address to devices position tracker
    std::string additionalAddress;
    //! Constant local address

    std::string LOCAL = "@localhost";
    std::string VORTEX = "@130.236.142.1";

    //! Saved variable from setTrackerPosition
    float trackerPosition[3];
    //! Saved variable from setTrackerRotation
    float trackerRotation[16];
    //! Saved variable from setAnalogPosition
    float analogPos[3];

    //!
    float transformMatrix[16];

    //! Saved variable from setButtonState
    bool buttonState;
    //! Saved variable from setButtonNumber
    int buttonNumber;
    //! Saved variable for setButton
    bool button[100];

};
