#include <iostream>
#include "config.h"

int main()
{
    std::cout << "Project Version: "
              << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "."
              << PROJECT_VERSION_PATCH << std::endl;
#ifdef ENABLE_LOGGING
    std::cout << "Logging is enabled!" << std::endl;
#else
    std::cout << "Logging is disabled." << std::endl;
#endif
    return 0;
}
