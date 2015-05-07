#pragma once

#include "wand3d/wand3d_types.h"
#include "wand3d/wand3d_network.h"

namespace wand3d {
  class Network;
  struct WandData;

  namespace utils {
    /**
    * @brief  Simple struct to hold screencoordinate data (x and y position)
    **/
    struct ScreenCoord {
      float x;
      float y;
    };

    /**
     * @brief  LaserPointer utility class
     */
    class LaserPointer {
    public:
      /**
      * @brief        Constructs LaserPointer object. Initializes sensor network properties.
      * @param[in]  network  The sensor network object.
      */
      LaserPointer(const Network& network);

      /**
      * @brief        Calculates screen coordinates (in pixels).
      * @param[in]  data  Reference to WandData struct populated with target data.
      * @retval        ScreenCoord containing x and y coordinates on screen.
      */
      ScreenCoord getScreenCoord(const WandData& data);

      /**
      * @brief        Set method for screen dimensions. Used to calculate correct screen space coordinates.
      * @param[in]  w     Screen width in pixels
      * @param[out]  h     Screen height in pixels
      */
      void setScreenDimensions(int w, int h);

      /**
      * @brief        Set method for weight used in the exponential average estimation of the screen coordinate
      * @param[in]  w     The weight for the running average, 0 disables running average, a value near 1 would give very smooth but slow update of the screen coord
      *
      *  In the calculation of the screencoordinate, an exponential weighted average is used to smooth out the resulting coordinate due to oscillations
      *  in the position and orientation data. The weight must be in the range of [0 1[.
      **/
      void setAverageWeight(float w);

    private:
      ScreenCoord lastCoord;  ///< keep track of last calculated coordinate to be used in running average

      Network network;    ///< private member of Network object, passed in the constructor

      int screen_w;      ///< screen width to transform coordinates within the screen dimensions
      int screen_h;      ///< screen height to transform coordinates within the screen dimensions

      float sensor_w;      ///< private member of precalculated sensor span (width)
      float sensor_h;      ///< private member of precalculated sensor span (height)

      float average_weight;  ///< weight to change behaviour of exponential weighted average (0 = no averaging occurs)
    };
  }
}
