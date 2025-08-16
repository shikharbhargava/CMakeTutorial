#include <iostream>

#include "math_utils.h"
#include "logger.h"
#include "hello.h"

int main()
{
  std::cout << Hello::getMessage() << std::endl;
  std::cout << "2 + 3 = " << MathUtils::add(2, 3) << std::endl;
  Logger::logMessage("Main function executed successfully");
  return 0;
}