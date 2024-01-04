#include "NullLogger.h"

namespace AbstLogger 
{

void NullLogger::log( const std::string logContent, Severity severity ) const
{
    // 本クラスは、何もロギングしない機能を提供するものである。
    // このため、本メソッドでは何もしないことを実装している。
}

}
