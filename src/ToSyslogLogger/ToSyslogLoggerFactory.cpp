#include <new>
#include "ToSyslogLoggerFactory.h"

namespace AbstLogger
{

bool ToSyslogLoggerFactory::destroyed_ = false;

LoggerFactory* LoggerFactory::getInstance()
{
    static ToSyslogLoggerFactory theFactory;
    if( ToSyslogLoggerFactory::isDestroyed() ) {
        (void) new (&theFactory) ToSyslogLoggerFactory;
    }
    return &theFactory;
}

ToSyslogLoggerFactory::~ToSyslogLoggerFactory()
{
    delete logger_;
    destroyed_ = true;
}

}
