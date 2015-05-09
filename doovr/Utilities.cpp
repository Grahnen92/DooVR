#include "Utilities.h"

/*
* displayFPS() - Calculate, display and return frame rate statistics.
* Called every frame, but statistics are updated only once per second.
* The time per frame is a better measure of performance than the
* number of frames per second, so both are displayed.
*
* NOTE: This function doesn't work properly if you call it for multiple
* windows. Call it only for one window, and only once for each frame.
*/
double Utilities::displayFPS(GLFWwindow *window) {

	static double t0 = 0.0;
	static int frames = 0;
	double fps = 0.0;
	double frametime = 0.0;
	static char titlestring[200];

	double t;

	// Get current time
	t = glfwGetTime();  // Gets number of seconds since glfwInit()
	// If one second has passed, or if this is the very first frame
	if ((t - t0) > 1.0 || frames == 0)
	{
		fps = (double)frames / (t - t0);
		if (frames > 0) frametime = 1000.0 * (t - t0) / frames;
		sprintf(titlestring, "DooVR, %.2f ms/frame (%.1f FPS)", frametime, fps);
		glfwSetWindowTitle(window, titlestring);
		// printf("Speed: %.1f FPS\n", fps);
		t0 = t;
		frames = 0;
	}
	frames++;
	return fps;
}