#pragma once

#include "wand3d_types.h"

namespace wand3d {
  /**
   *  @brief   Interface for Wand3d observers, used to get notifications when new data is available.
   *      To get callback when new data is available, you must:
   *        1. Inherit from this class.
   *        2. Implement the method wand3dCallback.
   *        3. Add the object to the list of observers with Wand3d::addObserver()
   */
  class Wand3dObserver {
    public:
      /**
      *  @brief   This method is called when new data is available.
      **/
      virtual void wand3dCallback(WandData data) = 0;
      virtual ~Wand3dObserver() {}
  };
}
