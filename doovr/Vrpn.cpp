
#include "Vrpn.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

//TODO
static int got_report;     // Tells when a new report has come in

Vrpn::Vrpn()
{
	// Open the connection to trackers
	vrpnAnalog = new vrpn_Analog_Remote("Wand@localhost");
	vrpnButton = new vrpn_Button_Remote("Wand@localhost");
	vrpnTracker = new vrpn_Tracker_Remote("IS900@localhost");

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

	cout << "Tracker '" << t.sensor << "' X: " << t.pos[0] << " Y: " << t.pos[1] << " Z: " << t.pos[2] << endl;
	//cout << count << endl;
	//count++;

	//transform = 

	t.

	got_report = 1; // Tell the main loop that we got another report

}

void Vrpn::connectDevices() 
{
	// Set up the tracker callback handler
	vrpnAnalog->register_change_handler(0, handle_analog);
	vrpnButton->register_change_handler(0, handle_button);
	vrpnTracker->register_change_handler(0, handle_tracker, 1); // the last argument --> handle_tracker will be called only when sensor #1 (wand) is updated.
}

void Vrpn::sendtoMainloop()
{
	vrpnAnalog->mainloop();
	vrpnButton->mainloop();
	vrpnTracker->mainloop();

	// Make sure that we get a new report

	got_report = 0;

	while (!got_report) {
		vrpnTracker->mainloop();
	}
}

