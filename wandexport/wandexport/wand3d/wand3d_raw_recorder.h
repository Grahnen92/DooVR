#pragma once

#include <string>

#include "wand3d/wand3d_observer.h"

#include <fstream>

namespace wand3d {
  class Wand3d;

  namespace utils {
  /**
   *  @brief  Helper class for saving raw input to file.
   */
  class Wand3dRawRecorder : public wand3d::Wand3dObserver {
  private:
    wand3d::Wand3d* wand;
    std::string filename;
    std::ofstream file;
    bool recording;

  public:
    /**
     *  @brief  Constructs an Wand3dRawRecorder object
     *  @param  wand     Pointer to wand3d object to use.
     *  @param  filename   The file/path to save data in, must have an ".w3d" extension.
     */
    Wand3dRawRecorder(wand3d::Wand3d *wand, std::string filename)
      : wand(wand), filename(filename), recording(false) { }
    ~Wand3dRawRecorder();

    /**
     *  @brief  Observer callback, used to fetch and save raw data when available
     */
    void wand3dCallback(wand3d::WandData data);

    /**
     *  @brief  Block and record for seconds and save to filename.
     *  @param   seconds    the amount of time to record (and block).
     */
    void recordAndBlock(unsigned int seconds);

    /**
     *  @brief  Start recording and saving data.
     */
    void startRecording();

    /**
     *  @brief  Stop recording and close file.
     */
    void stopRecording();

    /**
     *  @brief  Check if the object is recording data.
     */
    inline bool isRecording() const { return recording; }
  };
}
}
