#pragma once

#include <limits>

#include "wand3d/wand3d_network.h"

namespace wand3d {
  class WandData;
  namespace utils {
    /**
    *  @brief   TrackingUtils class containing utility methods for the tracking
    */
    class TrackingUtils {
      public:
        /**
        *  @brief          Constructs a TrackingUtils object
        *   @param[in]  Network   Network object from Wand3d object
        **/
        TrackingUtils(const Network& network);

        /**
        *  @brief          Calculates safety measure from distance to trackingvolume
        *  @param[in]  WandData   WandData object holding target data
        *  @retval    safety    Returns safety value ranging from 0 to 1 with 0 being in center of volume and 1 on the edge
        **/
        double getSafetyMeasure(const WandData &data) const;

      private:
        Network network;      ///<  Copy of Network object

        double minPlaneDistance;  ///<   Minimum plane distance calculated in constructor
        double trackingVolume[6];  ///<   Tracking volume as defined in Network ([XMIN XMAX YMIN YMAX ZMIN ZMAX])

        /**
        *  @brief          Extracts trackingVolume from Network object and calculated minPlaneDistance
        **/
        void calculateDistance();
    };
  }
}
