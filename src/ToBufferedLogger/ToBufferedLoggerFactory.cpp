#include <new>
#include "ToBufferedLoggerFactory.h"

namespace AbstLogger
{

bool ToBufferedLoggerFactory::destroyed_ = false;

LoggerFactory* LoggerFactory::getInstance()
{
    static ToBufferedLoggerFactory theFactory;
    if( ToBufferedLoggerFactory::isDestroyed() ) {
        (void) new (&theFactory) ToBufferedLoggerFactory;
    }
    return &theFactory;
}

ToBufferedLoggerFactory::~ToBufferedLoggerFactory()
{
    dynamic_cast<ToBufferedLogger*>(logger_)->stopBehavior();
    delete logger_;
    destroyed_ = true;
}

}
