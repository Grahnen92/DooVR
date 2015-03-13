#include "Device.h"

using namespace std;

static int gotReport;

//! Callback function to get data of analog tracker from vrpn server
void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a);
//! Callback function to get data of button tracker from vrpn server
void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b);
//! Callback function to get data of position tracker from vrpn server
void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t);


Device::Device(bool analog, bool button, bool tracker, string name) {
	// Add additional cases for STEM and Kienct2
	if (name == "Wand") {
		additionalAddress = "IS900" + LOCAL;
		name = name + LOCAL;
	}
	else {
		name = name + "0" + LOCAL;
		additionalAddress = name;
	}

	// Open the connection to trackers
	// Set up the tracker callback handler
	if (analog) {
		vrpnAnalog = new vrpn_Analog_Remote(name.c_str());
		vrpnAnalog->register_change_handler(this, handle_analog);
	}
	if (button) {
		vrpnButton = new vrpn_Button_Remote(name.c_str());
		vrpnButton->register_change_handler(this, handle_button);
	}
	if (tracker) {
		vrpnTracker = new vrpn_Tracker_Remote(additionalAddress.c_str());
		vrpnTracker->register_change_handler(this, handle_tracker, 0);
		// the last argument --> handle_tracker will be called only when sensor #1 (wand) is updated. How do we handle this generally?
	}
}
Device::~Device() {
}


void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a) {
	Device* analogTracker = static_cast<Device*> (userData);
	float analog[3] = { a.channel[0], a.channel[1], 0.0f };
	analogTracker->setAnalogPosition(analog);
}

void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b) {
	cout << "Button '" << b.button << "': " << b.state << endl;
	Device* buttonTracker = static_cast<Device*> (userData);
	buttonTracker->setButtonState(b.state);
}

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t) {
	Device* posTracker = static_cast<Device*> (userData);

	// Handle position data
	float position[3] = { t.pos[0], t.pos[1], t.pos[2] };
	posTracker->setTrackerPosition(position);

	// Handle rotation data
	double orient_local[16];
	q_to_ogl_matrix(orient_local, t.quat);
	posTracker->setTrackerRotation(orient_local);

	// Tell the main loop that we got another report
	gotReport = 1;
}

void Device::sendtoMainloop() {
	// Run mainloop only if pointer has been initialised.
	if (vrpnAnalog) vrpnAnalog->mainloop();
	if (vrpnButton) vrpnButton->mainloop();
	if (vrpnTracker) vrpnTracker->mainloop();

	// Make sure that we get a new report
	gotReport = 0;
	while (!gotReport && vrpnTracker) vrpnTracker->mainloop();

	//SleepEx(1, FALSE); //  <16.6ms for 60fps on render loop
}

// Get functions
bool Device::getButtonState() {
	return button;
}
float* Device::getAnalogPosition() {
	//cout << analogPos[0] << " " << analogPos[1] << endl;
	return analogPos;
}
float* Device::getTrackerPosition() {
	return trackerPosition;
}
float* Device::getTrackerRotation() {
	return trackerRotation;
}


// Set functions
void Device::setTrackerPosition(float t[3]) {
	// Wierd copies due to fixing axis and multiplying movement
	trackerPosition[0] = 2.0f*t[0];
	trackerPosition[1] = -2.0f*t[2]+0.5f;
	trackerPosition[2] = 5.0f*t[1];
}
void Device::setTrackerRotation(double o[16] ) {
	std::copy(o, o + 16, trackerRotation);
}
void Device::setAnalogPosition(float p[3]) {
	analogPos[0] = p[0];
	analogPos[1] = p[1];
	analogPos[2] = p[2];
}
void Device::setButtonState(bool b) {
	button = b;
}