#pragma once

#include <iosfwd>

namespace wand3d {

typedef int Measurement[12];

/**
 *  @brief parameters for the tracked target, e.g. dipole strength.
 **/
struct Target {
  double dipole_strength;  ///< The strength of the magnetic dipole.

  /**
   *  @brief Default constructor, sets dipole_strength to 3000.
   */
  Target() : dipole_strength(3e3) { }

  /**
   *  @brief Constructor, sets the specfied dipole_strength.
   */
  Target(double dipole_strength) : dipole_strength(dipole_strength) { }
};

/**
 * @brief Struct holding the output from the Wand3D algorithm.
 */
struct WandData {
  double position[3]; ///< Position (x, y, z) relative to origin [m].
  double velocity[3];  ///< Velocity (x, y, z) [m/s].
  double orientation[3];  ///< Dipole (x, y, z) including strength.
};

std::ostream& operator<<(std::ostream& os, const wand3d::WandData &data);

}  // Namespace wand3d
