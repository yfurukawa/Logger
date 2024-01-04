#include <new>
#include "ToConsoleLoggerFactory.h"

namespace AbstLogger
{

bool ToConsoleLoggerFactory::destroyed_ = false;

LoggerFactory* LoggerFactory::getInstance()
{
    static ToConsoleLoggerFactory theFactory;
    if( ToConsoleLoggerFactory::isDestroyed() ) {
        (void) new (&theFactory) ToConsoleLoggerFactory;
    }
    return &theFactory;
}

ToConsoleLoggerFactory::~ToConsoleLoggerFactory()
{
    delete logger_;
    destroyed_ = true;
}

}
