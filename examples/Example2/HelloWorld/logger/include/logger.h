#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>

namespace Logger
{
inline void logMessage(const std::string& msg)
{
  std::cout << "[LOG] " << msg << std::endl;
}
} // namespace Logger

#endif // _LOGGER_H_