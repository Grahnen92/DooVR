//	This is a VRPN example program that has a client and server for a
// tracker both within the same thread.
//	The basic idea is to instantiate both a vrpn_Tracker_NULL and
// a vrpn_Tracker_Remote using the same connection for each. Then, the
// local call handlers on the connection will send the information from
// the server to the client callbacks.


// Nice to have
#include "vrpn_Configure.h"             // for VRPN_CALLBACK, etc
#include "vrpn_Shared.h"                // for vrpn_SleepMsecs
#include "vrpn_Types.h"                 // for vrpn_float64


//
#include "vrpn_Connection.h"

// for handlers, vrpn_TRACKERCB, etc
#include "vrpn_Tracker.h"
#include "vrpn_Button.h"
#include "vrpn_Analog.h"

// for fprintf, stderr, printf, etc
#include <stdio.h>
#include <iostream>
using namespace std;

const char	*TRACKER_NAME = "Mouse0@localhost";
int	CONNECTION_PORT = vrpn_DEFAULT_LISTEN_PORT_NO;	// Port for connection to listen on

// Tracker server and connection port.
vrpn_Tracker_NULL	*ntkr;
vrpn_Connection		*connection;

// The Tracker type holds a position and an orientation.
// The Analog type is used for any type of axis : joystick axis, mouse axis.
// The Button type is used for any type of binary button : joystick button, mouse button.
vrpn_Analog_Remote  *vrpnAnalog;
vrpn_Button_Remote  *vrpnButton;
vrpn_Tracker_Remote* vrpnTracker;

/*****************************************************************************
 *
 Callback handlers
 *
 *****************************************************************************/

void	VRPN_CALLBACK handle_pos (void *, const vrpn_TRACKERCB t)
{
    static	int	count = 0;
    
    fprintf(stderr, "%d.", t.sensor);
    if ((++count % 20) == 0) {
        fprintf(stderr, "\n");
        if (count > 300) {
            printf("Pos, sensor %d = %f, %f, %f\n", t.sensor,
                   t.pos[0], t.pos[1], t.pos[2]);
            count = 0;
        }
    }
}

void	VRPN_CALLBACK handle_vel (void *, const vrpn_TRACKERVELCB t)
{
    //static	int	count = 0;
    
    fprintf(stderr, "%d/", t.sensor);
}

void	VRPN_CALLBACK handle_acc (void *, const vrpn_TRACKERACCCB t)
{
    //static	int	count = 0;
    
    fprintf(stderr, "%d~", t.sensor);
}

void    VRPN_CALLBACK handle_analog (void* userData, const vrpn_ANALOGCB a )
{
    
    cout << "Analog : ";
    
    for( int i=0; i < a.num_channel; i++ )
    {
        cout << a.channel[i] << " ";
    }
    
    cout << endl;
}

void    VRPN_CALLBACK handle_button (void* userData, const vrpn_BUTTONCB b )
{
    cout << "Button '" << b.button << "': " << b.state << endl;
}


void    VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t )
{
    cout << "Tracker '" << t.sensor << "' : " << t.pos[0] << "," <<  t.pos[1] << "," << t.pos[2] << endl;
}



int main (int argc, char * argv [])
{
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return -1;
    }
    
    // explicitly open the connection
    connection = vrpn_create_server_connection(CONNECTION_PORT);
    
    // Open the tracker server, using this connection, 2 sensors, update 60 times/sec
    ntkr = new vrpn_Tracker_NULL(TRACKER_NAME, connection, 2, 60.0);

    // Open the tracker remote using this connection.
    vrpnAnalog = new vrpn_Analog_Remote ("Trackpad0@localhost");
    vrpnButton = new vrpn_Button_Remote ("Mouse0@localhost");
    vrpnTracker = new vrpn_Tracker_Remote ( "HandTracker@localhost");
    
    
    vrpnAnalog->register_change_handler (0, handle_analog);
    vrpnButton->register_change_handler (0, handle_button);
    vrpnTracker->register_change_handler (0, handle_tracker);
    
    
    /*
     * main interactive loop
     */
    while ( 1 ) {
        // Let the tracker server, client and connection do their things
        ntkr->mainloop();
        vrpnAnalog->mainloop();
        vrpnButton->mainloop();
        connection->mainloop();
        
        // Sleep for 1ms so we don't eat the CPU
        vrpn_SleepMsecs(1);
    }
    
    return 0;
    
}   /* main */


