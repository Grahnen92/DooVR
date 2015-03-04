#include "Vrpn.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

//TODO
//static int got_report;     // Tells when a new report has come in


Vrpn::Vrpn()
{

}


Vrpn::~Vrpn()
{
}

void VRPN_CALLBACK Vrpn::handle_analog(void* userData, const vrpn_ANALOGCB a)
{
	int nbChannels = a.num_channel;

	cout << "Analog : ";

	for (int i = 0; i < a.num_channel; i++)
	{
		cout << a.channel[i] << " ";
	}

	cout << endl;
}

void VRPN_CALLBACK Vrpn::handle_button(void* userData, const vrpn_BUTTONCB b)
{
	cout << "Button '" << b.button << "': " << b.state << endl;
}

void VRPN_CALLBACK Vrpn::handle_tracker(void* userData, const vrpn_TRACKERCB t)
{
	
	//static int count = 0;

	cout << "Tracker '" << t.sensor << "' X: " << t.pos[0] << " Y: " << t.pos[1] << " Z: " << t.pos[2] << endl;

	//got_report = 1; // Tell the main loop that we got another report

}

void Vrpn::connectDevices() 
{
	// Set up the tracker callback handler
	vrpnAnalog->register_change_handler(0, handle_analog);
	vrpnButton->register_change_handler(0, handle_button);
	vrpnTracker->register_change_handler(0, handle_tracker, 1); // the last argument --> handle_tracker will be called only when sensor #1 (wand) is updated. 
}


