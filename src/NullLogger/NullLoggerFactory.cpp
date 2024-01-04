#include <new>
#include "NullLoggerFactory.h"

namespace AbstLogger
{

bool NullLoggerFactory::destroyed_ = false;

LoggerFactory* LoggerFactory::getInstance()
{
    static NullLoggerFactory theFactory;
    if( NullLoggerFactory::isDestroyed() ) {
        (void) new (&theFactory) NullLoggerFactory;
    }
    return &theFactory;
}

NullLoggerFactory::~NullLoggerFactory()
{
    delete logger_;
    destroyed_ = true;
}

}
