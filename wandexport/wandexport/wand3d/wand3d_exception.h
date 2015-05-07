#pragma once

#include <exception>
#include <string>

namespace wand3d {

  /**
  * @brief  Exception class that inherits from std::runtime_error
  **/
  class Wand3dSerialException : public std::runtime_error {
  public:

    /**
    *  @brief    Constructs a Wand3dSerialException
    *   param[in]  std::string describing the error, use .what() to get the message
    **/
    Wand3dSerialException(const std::string &error) : std::runtime_error(error) { }
  };

}
