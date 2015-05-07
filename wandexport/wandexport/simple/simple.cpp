#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

#include "wand3d/wand3d.h"
#include "wand3d/wand3d_exception.h"

int main(int argc, char* argv[]) {
  std::cout << "Loading: " << wand3d::getVersion() << std::endl;
  // Get serial port from argument
  if (argc != 2) {
    std::cerr << "Wrong number of arguments, please specify serial port (e.g program COM3)" << std::endl;
    return 1;
  }
  const char* deviceName = argv[1];

  // Construct new Wand3d using the specified port
  wand3d::Wand3d* wand;
  try {
    wand = new wand3d::Wand3d(deviceName);
  } catch (wand3d::Wand3dSerialException error) {
    std::cout << error.what() << std::endl;
    return 2;
  }

  // Start reading from serial port and computing data
  wand->start();

  // Loop for a while, then exit.
  for (int i = 0; i < 5e4; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    // Print position to console
    if (wand->isCalibrated()) {
	    // Get latest wand data
      wand3d::WandData data = wand->getData();
      std::cout << "position: (" << std::setprecision(3) << std::fixed
                << data.position[0] << ",  "
                << data.position[1] << ",  "
                << data.position[2] << ") " << std::endl;
    }
  }

  // Clean up.
  delete wand;

  return 0;
}
