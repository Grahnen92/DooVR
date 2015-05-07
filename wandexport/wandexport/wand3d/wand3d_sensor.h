#pragma once

#include <armadillo>

namespace wand3d {
/**
 *  @brief Sensor specific parameters
 */
class Sensor {
 public:
  /// Standard deviation of the measurement noise for the sensor.
  double noise;
  arma::mat R;  ///< Covariance matrix of the measurment noise.
  double sFreq;  ///< Sampling frequency [Hz].

  /**
   *  @brief Default constructor, sets noise to 1000 and sFreq to 300
   *  and Calculates R.
   */
  Sensor();
  /**
   *  @brief Constructor, sets the parameters and calculates R.
   *  @param[in] noise  Standard deviation of the measurement noise for the sensor.
   *  @param[in] sFreq  Sampling frequency [Hz].
   */
  Sensor(double noise, double sFreq);

 private:
  void init(double noise, double sFreq);
};
}  // Namespace wand3d
