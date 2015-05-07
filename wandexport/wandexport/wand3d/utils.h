#pragma once

namespace wand3d {

class Wand3d;

namespace utils {
  /**
   *  @brief          Saves the current static field to file
   *  param[in]   wand     Wand3d pointer which holds the static field
   *  param[in]   filename  Name of file of which to save the static field
   **/
  void saveStaticField(const wand3d::Wand3d* wand, const char* filename);

  /**
   *  @brief          Loads static field from the specified file
   *  param[out]   wand     Wand3d pointer which holds the static field
   *  param[in]   filename   Name of file with saved static field
   **/
  void loadStaticField(wand3d::Wand3d* wand, const char* filename);

  /**
   *  @brief          Method for saving calibrating using a predefined point
   *  param[in]   wand     Wand3d object (must be properly calibrated)
   *   param[in]   filename   Name of file to save point calibration
  **/
  void saveCalibrationPointField(const wand3d::Wand3d* wand, const char* filename);

  /**
   *   @brief                Recalibrate using a predefined point
   *   param[in]   wand           Wand3d object to be calibrated
   *   param[in]   calibrationPointFile  Name of file to load save point calibration
   *
   *   __Note__. When calibrating using predefined points you need to
   *  place the wand in the exact same position when saving and
   *  loading a point calibration. This is useful if using the same
   *  setup but the static field somewhat changes (due to magnetic
   *  material in the vicinity of the sensors) and you dont want to do
   *  a classic calibration which requires the magnetic wand to be
   *  placed far away from the sensors.
  **/
  void updateStaticField(wand3d::Wand3d *wand, const char *calibrationPointFile);
}
}
