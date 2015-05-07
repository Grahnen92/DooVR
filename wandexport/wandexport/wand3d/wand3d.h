#pragma once

#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "wand3d_config.h"

#include "wand3d_network.h"
#include "wand3d_sensor.h"
#include "wand3d_types.h"

namespace wand3d {

class ExtendedKalmanFilter;
class Wand3dObserver;
class Wand3dSerialInterface;

/**
 * @brief Returns a version string for the API
 *
 * @retval A string representing the current API version.
 */
std::string getVersion();

/**
 *  @brief Implementation of the 3D Wand algorithm.
 *
 *  This is the main class of the 3D Wand tracking system and is responsible for:
 *    - Creating and starting the serial input.
 *    - Holding various paramaters of the system
 *    - Running the update loop
 *    - Performing calibration
 *    - Holding a list of observers to be notified when new data is available.
 */
class Wand3d {

private:
  std::string devname_;  ///<  Name of device
  ///  Input source, provides measurements from the sensors
  std::unique_ptr<Wand3dSerialInterface> input_;

  Sensor sensor_;  ///<  Sensor parameters
  Target target_;  ///<  Target parameters

  bool calibrated_;  ///<  Initial calibration completed
  bool initialized_;  ///<  Setup parameters set

  ///  User in calculation of the static field (sample 100
  ///  measurements and calculating mean values)
  unsigned int calibrationIndex_;

  ///  arma::vec used in calculation of the static field (average of a
  ///  set of measurements)
  arma::vec staticField_;

  Measurement meas_;  ///<  Measurement values
  std::unique_ptr<ExtendedKalmanFilter> filter_;  ///<  Holds the filter step function

  /// Container type used to store observers
  typedef std::vector<Wand3dObserver*> ObserverList;
  /// Observers to notify when new data is available
  ObserverList observerList_;
  WandData data_;  ///< WandData structure of the last sample

  /// Boolean telling if the updatethread should continue working
  bool shouldUpdate_;
  std::thread updateThread_;  ///< Thread that performs the signal processing
  std::condition_variable measWait_;  ///< Indicate measurements are available
  mutable std::mutex updateMutex_;  ///< Mutex for core data
  mutable std::mutex observerListMutex_;  ///< Mutex for observer list
  mutable std::mutex modelMutex_;  ///< Mutex for model
  mutable std::mutex measurementMutex_;  ///<  Mutex for raw data-operations

  /**
   *  @brief        Notify observers with new data.
   *  param[in]  data   Newest WandData
  **/
  void notifyObservers(const WandData &data);

  /**
   *  @brief  Restarts input, called when there was a problem in reading
  **/
  void restartInput();

  /**
   *  @brief  Internal calibration routine, computes average static magnetic field
  **/
  void calibrate(int meas[12]);

  /**
   *  @brief  Saves state to data, calls notifyObservers()
  **/
  void setData(const arma::vec& x);

  /**
   *  @brief  Private initialization
  **/
  void init();

  /**
   *  @brief  update loop, called in updateThread
  **/
  void update();


public:
  /**
   *  @brief Constructs a Wand3d object and initializes state.
   *
   *  The serial port communication is initialized unless the devname
   *  is left empty.
   *
   *  @param[in] devname The name of the device to be
   *  used as serial input, e.g. "COM3" or
   *  "/dev/tty.usbmodem12345671".
   *
   *  Note. if using "test" as name of device, a test version will
   *  start which will work without the actual hardware installed This
   *  will generate dummy data which can be used to test your
   *  application. If using the name of a file with recorded wand3d
   *  raw data this file will be loaded and used as input to the
   *  tracking, this is also to help testing the application.
  **/
  Wand3d(const std::string& devname);

  /**
   *  @brief  Clean up and destruct object, must be called to close port.
  **/
  ~Wand3d(void);

  /**
   *  @brief  Stop the update loop
  **/
  void stop();

  /**
   *  @brief          Start the update loop
   *  retval  initialized    returns false if not initialized and true if initialized
  **/
  bool start();

  /**
   *  @brief          Check if wand3d is initialized
   *  retval   initialized   returns false if not initialized and true if initialized
  **/
  bool isInitialized();

  /**
   * @brief        Retrieves the newest data available.
   * @retval        WandData struct containing the newest position, velocity and orientation.
   */
  WandData getData();

  /**
   *  @brief        Sets the COM port to read from
   *  param[in]  name   Name of device
   *
   *  Note: if using "test" as name of device, a test version will start which will work without the actual hardware installed
   *  This will generate dummy data which can be used to test your application. If using the name of a file (ending in .w3d) with recorded wand3d raw data
   *   this file will be loaded and used as input to the tracking, this is also used to help testing the application.
  **/
  bool setInput(const std::string& name);

  /**
   *  @brief        Check if the input used is a serial port
  **/
  bool isSerialInput() const;

  /**
   *  @brief  Set calibration flag to false, causing recalibration of the static magnetic field.
  **/
  void reCalibrate();

  /**
   *  @brief  Check if Wand3d is calibrated (static magnetic field saved)
  **/
  bool isCalibrated() const { return calibrated_; }

  /**
   *  @brief  Get Network object describing the geometry of the tracking system
  **/
  Network getNetwork();

  /**
   *  @brief Set Network object describing the geometry of the tracking system
   *  @param[in] net  The Network object to be set.
  **/
  void setNetwork(Network net);

  /**
   *  @brief Add new observer to be notified when new data is available.
   *  @param[in] object  The object which implements the Wand3dObserver interface.
   *  @retval Success status, true if the observer was added
  **/
  bool addObserver(Wand3dObserver* object);

  /**
   *  @brief Remove observer from the list of observers to notified
   *  when new data is available.
   *  @param[in] object Object to be removed.  @retval Success status,
   *  returns true if the object was in the list and got removed.
  **/
  bool removeObserver(Wand3dObserver* object);

  /**
   * @brief Get method for obtaining the current calculated static
   * field used for calibration
   * param[out] field  Static field containing 12 measurements (4 sensors, 3 axis)
  **/
  bool getStaticField(double field[12]) const;

  /**
   * @brief Set method for the static field which will change the calibration
   * param[in] field  The current static field of the 4 sensors.
  **/
  void setStaticField(double field[12]);

  /**
   * @brief Get method to retrieve the current measured magnetic field
   * by the 3dwand sensors
   * param[out] field  Array containing the latest measured magnetic field
  **/
  bool getRawData(Measurement measurement) const;

  /**
   * @brief Set method for changing the standard deviations of each process
   * param[in] acceleration  Stdev for the process noise on the acceleration
   * param[in] orientation  Stdev for the process on the orientation
   * param[in] gain  Stdev for the process noise of the sensor gain
   *
   * Note. These parameters changes the behaviour of the tracking system.
  **/
  void setStandardDeviations(double acceleration = 0.1,
                             double orientation = 0.1,
                             double gain = 1e-4);
};

}
