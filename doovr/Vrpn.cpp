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

	static int count = 0;

	//cout << "Tracker '" << t.sensor << "' X: " << t.pos[0] << " Y: " << t.pos[1] << " Z: " << t.pos[2] << endl;
	//cout << count << endl;
	count++;
	cout << count << endl;

	//transform = t.

	// Tell the main loop that we got another report
	got_report = 1;

}

void Vrpn::connectDevices()
{
	// Set up the tracker callback handler
	if (vrpnAnalog) vrpnAnalog->register_change_handler(0, handle_analog);
	if (vrpnButton) vrpnButton->register_change_handler(0, handle_button);
	if (vrpnTracker) vrpnTracker->register_change_handler(0, handle_tracker, 1);
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