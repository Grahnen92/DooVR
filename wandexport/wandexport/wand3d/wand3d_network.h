#pragma once

#include <armadillo>

namespace wand3d {
/**
 *  @brief  Class containing sensor network information
 **/
class Network {
 public:
  /// Number of sensors in the network.
  static const unsigned int kNumSensors = 4;
  /// Number of dimensions in each sensor.
  static const unsigned int kNumDimensions = 3;

  /// Sensor positions relative to set origin.
  arma::vec sensorPositions[kNumSensors];
  /// Sensor rotation relative to the nominal pose.
  arma::mat sensorRotations[kNumSensors];

  /// Tracking volume specified as [XMIN XMAX YMIN YMAX ZMIN ZMAX].
  arma::vec tracking_volume;

  /**
   *  @brief Constructor, sets sensor positions and tracking volume
   *  according to prototype in plastic casing
   **/
  Network();

  /**
   *  @brief Set sensor position.
   *  @param[in] sensor  sensor number to set, less than Network::kNumSensors.
   *  @param[in] x  x-component of sensor position.
   *  @param[in] y  y-component of sensor position.
   *  @param[in] z  z-component of sensor position.
   **/
  void setSensorPosition(unsigned int sensor, double x, double y, double z);

  /**
   *  @brief Get sensor position as 3-component double array.
   *  @param[in] sensor Sensor number to set, less than
   *  Network::kNumSensors.
   *  @param[out] position 3-component array where the position will
   *  be stored as {x,y,z}.
   **/
  void getSensorPosition(unsigned int sensor, double position[3]) const;

  /**
   *  @brief Set sensor rotation.
   *  @param[in] sensor  sensor number to set, less than Network::kNumSensors.
   *  @param[in] R  rotation stored matrix row-major.
   **/
  void setSensorRotation(unsigned int sensor, const double R[9]);

  /**
   *  @brief Get sensor rotation.
   *  @param[in] sensor Sensor number to set, less than Network::kNumSensors.
   *  @param[out] R rotation matrix stored row-major.
   **/
  void getSensorRotation(unsigned int sensor, double R[9]) const;

  /**
   *  @brief Set tracking volume as an axis-aligned bounding box,
   *  which limits the tracked position to that box.
   *
   *  @param[in] xmin  Minimum x-axis value.
   *  @param[in] xmax  Maximum x-axis value.
   *  @param[in] ymin  Minimum y-axis value.
   *  @param[in] ymax  Maximum y-axis value.
   *  @param[in] zmin  Minimum z-axis value.
   *  @param[in] zmax  Maximum z-axis value.
   **/
  void setTrackingVolume(double xmin, double xmax, double ymin, double ymax,
                         double zmin, double zmax);

  /**
   *  @brief Set tracking volume as an axis-aligned bounding box,
   *  which limits the tracked position to that box.
   *
   *  @param[in] minmax  Defines the tracking volume as
   *  {xmin, xmax, ymin, ymax, zmin, zmax}.
   **/
  void setTrackingVolume(double minmax[6]);

  /**
   *  @brief Get the tracking volume, an axis-aligned bounding box.
   *
   *  @param[out] volume  Defines defining the tracking volume as
   *  {xmin, xmax, ymin, ymax, zmin, zmax}.
   **/
  void getTrackingVolume(double volume[6]) const;
};
}  // Namespace wand3d
