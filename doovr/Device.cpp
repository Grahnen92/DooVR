#include "Device.h"

using namespace std;

static int got_report;

//! Callback function to get data of analog tracker from vrpn server
void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a);
//! Callback function to get data of button tracker from vrpn server
void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b);
//! Callback function to get data of position tracker from vrpn server
void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t);


Device::Device(bool analog, bool button, bool tracker, string name)
{
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
Device::~Device()
{
}


void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a)
{
	Device* analogTracker = static_cast<Device*> (userData);
	analogTracker->setAnalogPosition(glm::vec2(a.channel[0], a.channel[1]));

	int nbChannels = a.num_channel;

	//cout << "Analog : ";

	//for (int i = 0; i < a.num_channel; i++)
	//{
	//	cout << a.channel[i] << " ";
	//}

	//cout << endl;
}

void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b)
{
	cout << "Button '" << b.button << "': " << b.state << endl;
	Device* buttonTracker = static_cast<Device*> (userData);
	buttonTracker->setButtonState(b.state);
}

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t)
{
	Device* posTracker = static_cast<Device*> (userData);
	
	glm::quat q = glm::quat(t.quat[0], t.quat[1], t.quat[2], t.quat[3]);

	glm::mat4 rotation = glm::mat4_cast(q);
	glm::mat4 translation = glm::transpose(glm::translate(glm::vec3(t.pos[0], t.pos[1], t.pos[2])));
	
	posTracker->setTrackerPosition(glm::vec3(t.pos[0], t.pos[1], t.pos[2]));

	glm::mat4 transform = rotation* translation;
	posTracker->setTrackerTransform(transform);


	cout << t.pos[0] << " :"<< t.pos[1] << " :" <<  t.pos[2] << endl;
	double dArray[16] = { 0.0 };

	const float *pSource = (const float*)glm::value_ptr(transform);
	for (int i = 0; i < 16; ++i)
	dArray[i] = pSource[i];

	/*
	cout << dArray[0] << " " << dArray[1] << " " << dArray[2] << " " << dArray[3] << endl
	<< dArray[4] << " " << dArray[5] << " " << dArray[6] << " " << dArray[7] << endl
	<< dArray[8] << " " << dArray[9] << " " << dArray[10] << " " << dArray[11] << endl
	<< dArray[12] << " " << dArray[13] << " " << dArray[14] << " " << dArray[15] << endl << endl << endl;
	
	*/
	//q_print(t.quat);

	// Tell the main loop that we got another report
	got_report = 1;
}

void Device::sendtoMainloop()
{
	// Run mainloop only if pointer has been initialised.
	if (vrpnAnalog) vrpnAnalog->mainloop();
	if (vrpnButton) vrpnButton->mainloop();
	if (vrpnTracker) vrpnTracker->mainloop();

	// Make sure that we get a new report
	got_report = 0;
	while (!got_report && vrpnTracker) vrpnTracker->mainloop();

	//SleepEx(1, FALSE); //  <16.6ms for 60fps on render loop
}

// Get functions
glm::mat4 Device::getTrackerTransform() {

	glm::mat4 rotX = { 1.0, 0.0, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, -1.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 1.0 };

	glm::mat4 rotY = { 0.0, 0.0, -1.0, 0.0,
						0.0, 1.0, 0.0, 0.0,
						1.0, 0.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 1.0 };

	glm::mat4 trans = rotY * rotX * trackerTransform;
	return trans;
}
bool Device::getButtonState() {
	return button;
}
glm::vec2 Device::getAnalogPosition() {
	//cout << analogPos[0] << " " << analogPos[1] << endl;
	return analogPos;
}
glm::vec3 Device::getTrackerPosition() {

	glm::mat3 rotX = { 1.0, 0.0, 0.0,
						0.0, 0.0, 1.0,
						0.0, -1.0, 0.0 };
	glm::mat3 rotY = { 1.0, 0.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 0.0, -1.0 };


	glm::vec3 pos = rotY * rotX * trackerPosition;
	pos.y = pos.y + 0.5f;
	return pos;
}

// Set functions
void Device::setTrackerTransform(glm::mat4 t) {
	trackerTransform = t;
}
void Device::setTrackerPosition(glm::vec3 t) {
	trackerPosition = t;
}
void Device::setAnalogPosition(glm::vec2 p) {
	analogPos = p;
}
void Device::setButtonState(bool b) {
	button = b;
}