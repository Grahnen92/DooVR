#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #define SLEEP(c) Sleep(c*1000)
#else
  #include <unistd.h>
  #define SLEEP(c) sleep(c)
#endif


#include "wand3d/wand3d.h"
#include "wand3d/wand3d_exception.h"
#include "wand3d/wand3d_observer.h"

// Wand3dObserver class implementation
class MyWand3dObserver : public wand3d::Wand3dObserver {

public:

  void wand3dCallback(wand3d::WandData data) {
    std::cout << data << std::endl;
  }

};

int main(int argc, char* argv[]) {
  std::cout << "Loading: " << wand3d::getVersion() << std::endl;
  // Get serial port from argument
  if (argc != 2) {
    std::cerr << "Wrong number of arguments, please specify serial port (e.g program COM3)" << std::endl;
    return 1;
  }
  const char* deviceName = argv[1];

  // Construct new Wand3d using the specified port
  wand3d::Wand3d *wand;
  try {
    wand = new wand3d::Wand3d(deviceName);
  } 
  catch (wand3d::Wand3dSerialException error) {
    std::cout << error.what() << std::endl;
    return 2;
  }

  // Create an observer object
  wand3d::Wand3dObserver *observer = new MyWand3dObserver();

  // Add observer to wand3d object
  wand->addObserver(observer);

  // Start reading from serial port and computing data
  wand->start();

  SLEEP(20);

  // Clean up.
  wand->removeObserver(observer);
  delete observer;
  delete wand;

  return 0;
}
