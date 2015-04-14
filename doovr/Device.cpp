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
		// Default port "@localhost:3883"
		// DNS adress "@130.236.142.1"
		// vrpn_print_devices.exe Wand@130.236.142.25
		// vrpn_print_devices.exe Wand@itn-vortex.itn.liu.se

		//additionalAddress = "IS900@itn-vortex";
		name = name + "@itn-vortex.itn.liu.se";
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
	cout << "Button '" << a.channel[0] << "': " << a.channel[1] << endl;
	analogTracker->setAnalogPosition(analog);
}
													
void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b) {

	cout << "Button '" << b.button << "': " << b.state << endl;
	Device* buttonTracker = static_cast<Device*> (userData);

	buttonTracker->setButtonNumber((int) b.button);
	buttonTracker->setButtonState(b.state);

	//handles buttons in an array of bools instead. Can now handle more than one button at a time.
	buttonTracker->setButton(b.button, b.state);
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
	return buttonState;
}

int Device::getButtonNumber() {
	return buttonNumber;
}

bool* Device::getButton() {
	return button;
}

float* Device::getAnalogPosition() {
	return analogPos;
}
float* Device::getTrackerPosition() {
	return trackerPosition;
}
float* Device::getTrackerRotation() {
	return trackerRotation;
}

// Set functions
void Device::setTrackerPosition(float* t) {
	// fix point: 1.088f from floor.
	// Wierd copies due to fixing axis and multiplying movement
	trackerPosition[0] = t[0] + 0.2067f;
	trackerPosition[1] = -t[2] + 1.005; // offset to get correct wand coordinates
	trackerPosition[2] = t[1] - 0.0f;
}
void Device::setTrackerRotation(double* o ) {
	double temp;
	temp = o[1];
	o[1] = -o[2];
	o[2] = temp;

	temp = o[5];
	o[5] = -o[6];
	o[6] = temp;

	temp = o[9];
	o[9] = -o[10];
	o[10] = temp;

	std::copy(o, o + 16, trackerRotation);
}
void Device::setAnalogPosition(float* p) {
	analogPos[0] = p[0];
	analogPos[1] = p[1];
	analogPos[2] = p[2];
}
void Device::setButtonState(bool b) {
	buttonState = b;
}
void Device::setButtonNumber(int b) {
	buttonNumber = b;
}

void Device::setButton(int n, bool b) {
	button[n] = b;
}