#include <new>
#include "ToFileLoggerFactory.h"

namespace AbstLogger
{

bool ToFileLoggerFactory::destroyed_ = false;

LoggerFactory* LoggerFactory::getInstance()
{
    static ToFileLoggerFactory theFactory;
    if( ToFileLoggerFactory::isDestroyed() ) {
        (void) new (&theFactory) ToFileLoggerFactory;
    }
    return &theFactory;
}

ToFileLoggerFactory::~ToFileLoggerFactory()
{
    delete logger_;
    destroyed_ = true;
}

}
