#include <iostream>
#include "ToConsoleLogger.h"

namespace AbstLogger 
{

void ToConsoleLogger::log( const std::string logContent, Severity severity ) const
{
    std::cout << currentTime() << " : " << severityName[static_cast<int>(severity)] << " : " << logContent << std::endl;
}

}
