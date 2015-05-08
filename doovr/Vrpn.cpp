#include "Vrpn.h"


using namespace std;

static int gotReport;

//! Callback function to get data of analog tracker from vrpn server
void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a);
//! Callback function to get data of button tracker from vrpn server
void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b);
//! Callback function to get data of position tracker from vrpn server
void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t);


Vrpn::Vrpn(bool analog, bool button, bool tracker, string name) {
	// Add additional cases for STEM and Kienct2
	if (name == "Wand") {
		// vrpn_print_devices.exe Wand@130.236.142.25
		// vrpn_print_devices.exe Wand@itn-vortex.itn.liu.se

		additionalAddress = "IS900@itn-vortex.itn.liu.se";
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
Vrpn::~Vrpn() {
	delete vrpnAnalog;
	delete vrpnButton;
	delete vrpnTracker;
}

// VRPN Callbacks
void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a) {
	Vrpn* analogTracker = static_cast<Vrpn*> (userData);
	float analog[3] = { a.channel[0], a.channel[1], 0.0f };
	analogTracker->setAnalogPosition(analog);
	//cout << "Button '" << a.channel[0] << "': " << a.channel[1] << endl;
}
													
void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b) {
	Vrpn* buttonTracker = static_cast<Vrpn*> (userData);
	buttonTracker->setButtonNumber((int) b.button);
	buttonTracker->setButtonState(b.state);
	//cout << "Button '" << b.button << "': " << b.state << endl;
}

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t) {
	Vrpn* posTracker = static_cast<Vrpn*> (userData);

	// Set the new position
	double position[3];
	position[0] = t.pos[0] + posTracker->getTransformMatrix()[3];
	position[1] = -t.pos[2] + posTracker->getTransformMatrix()[7];
	position[2] = t.pos[1] + posTracker->getTransformMatrix()[11];
	posTracker->setWandPosition(position);

	// Set new orientation
	double T[16];
	float floatT[16] = { 0.0f };
	float out[16] = { 0.0f };
	q_to_ogl_matrix(T, t.quat);
	T[3] = 0.0;
	T[7] = 0.0;
	T[11] = 0.0;
	T[15] = 1.0f;
	posTracker->setWandOrientation(T);

	// Tell the main loop that we got another report
	gotReport = 1;
}

void Vrpn::sendtoMainloop() {
	// Run mainloop only if pointer has been initialised.
	if (vrpnAnalog) vrpnAnalog->mainloop();
	if (vrpnButton) vrpnButton->mainloop();
	if (vrpnTracker) vrpnTracker->mainloop();

	// Make sure that we get a new report
	gotReport = 0;
	while (!gotReport && vrpnTracker) vrpnTracker->mainloop();

	//SleepEx(1, FALSE); //  <16.6ms for 60fps on render loop
}

// Set functions
void Vrpn::setWandPosition(double* t) {
	wandPosition[0] = (float) t[0];
	wandPosition[1] = (float) t[1];
	wandPosition[2] = (float) t[2];
}

void Vrpn::setWandOrientation(double* o ) {
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
	std::copy(o, o + 16, wandOrientation);
}
void Vrpn::setAnalogPosition(float* p) {
	analogPos[0] = p[0];
	analogPos[1] = p[1];
	analogPos[2] = p[2];
}
void Vrpn::setButtonState(bool b) {
	buttonState = b;
}
void Vrpn::setButtonNumber(int b) {
	buttonNumber = b;
}