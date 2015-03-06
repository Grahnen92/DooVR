#include "Vrpn.h"

using namespace std;

static int got_report;

Vrpn::Vrpn(bool analog, bool button, bool tracker , string name)
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
	if (analog) vrpnAnalog = new vrpn_Analog_Remote(name.c_str());
	if (button) vrpnButton = new vrpn_Button_Remote(name.c_str());
	if (tracker) vrpnTracker = new vrpn_Tracker_Remote(additionalAddress.c_str());
}


Vrpn::~Vrpn()
{
}

void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a)
{
	Vrpn* analogTracker = static_cast<Vrpn*> (userData);
	analogTracker->setAnalogPosition(glm::vec2(a.channel[0], a.channel[1]));

	int nbChannels = a.num_channel;

	cout << "Analog : ";

	for (int i = 0; i < a.num_channel; i++)
	{
		cout << a.channel[i] << " ";
	}

	cout << endl;
}

void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b)
{
	cout << "Button '" << b.button << "': " << b.state << endl;
}

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t)
{
	Vrpn* posTracker = static_cast<Vrpn*> (userData);
	glm::quat q = glm::quat(t.quat[0], t.quat[1], t.quat[2], t.quat[3]);
	glm::mat4 rotation = glm::mat4_cast(q);
	glm::mat4 translation = glm::translate(glm::vec3(t.pos[0], t.pos[1], t.pos[2]));
	glm::mat4 transform = rotation * translation;
	posTracker->setTrackerTransform(transform);
	
	//static int count = 0;
	//cout << "Tracker '" << t.sensor << "' X: " << t.pos[0] << " Y: " << t.pos[1] << " Z: " << t.pos[2] << endl;
	//cout << count << endl;
	//count++;
	//cout << count << endl;
	//glTranslated(t.pos[0], )

	// Tell the main loop that we got another report
	got_report = 1;

}


void Vrpn::connectDevices()
{
	// Set up the tracker callback handler
	if (vrpnAnalog) vrpnAnalog->register_change_handler(this, handle_analog);
	if (vrpnButton) vrpnButton->register_change_handler(this, handle_button);
	if (vrpnTracker) vrpnTracker->register_change_handler(this, handle_tracker, 1);
	// the last argument --> handle_tracker will be called only when sensor #1 (wand) is updated. How do we handle this generally?
}

void Vrpn::sendtoMainloop()
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
glm::mat4 Vrpn::getTrackerTransform() {

	double dArray[16] = { 0.0 };

	const float *pSource = (const float*)glm::value_ptr(trackerTransform);
	for (int i = 0; i < 16; ++i)
		dArray[i] = pSource[i];

	cout << dArray[0] << " " << dArray[1] << " " << dArray[2] << " " << dArray[3] << endl
		<< dArray[4] << " " << dArray[5] << " " << dArray[6] << " " << dArray[7] << endl
		<< dArray[8] << " " << dArray[9] << " " << dArray[10] << " " << dArray[11] << endl
		<< dArray[12] << " " << dArray[13] << " " << dArray[14] << " " << dArray[15] << endl << endl << endl;
	return trackerTransform;
}
bool Vrpn::getButtonState() {
	return true;
}
glm::vec2 Vrpn::getAnalogPosition() {
	cout << analogPos[0] << " " << analogPos[1] << endl;
	return analogPos;
}

// Set functions
void Vrpn::setTrackerTransform(glm::mat4 t) {
	trackerTransform = t;
}
void Vrpn::setAnalogPosition(glm::vec2 p) {
	analogPos = p;
}
void Vrpn::setButtonState(vrpn_BUTTONCB b) {
	button = b;
}