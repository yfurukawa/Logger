#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "TextFileWriter.h"
#include "ToFileLogger.h"

namespace AbstLogger 
{

ToFileLogger::ToFileLogger( std::unique_ptr<::IClock> clock )
    : clock_( std::move(clock) ),
    fileWriter_( std::make_unique<::TextFileWriter>( createFilePath() ) )
{
}

void ToFileLogger::log( const std::string logContent, Severity severity ) const
{
    std::stringstream ss;
    ss << currentTime() << " : " << severityName[static_cast<int>(severity)] << " : " << logContent << std::endl;
    auto result = fileWriter_->write( ss.str() );
    if( result != std::nullopt ) {
        std::cerr << result.value() << std::endl;
    }
}

std::filesystem::path ToFileLogger::createFilePath() const
{
    const auto& ct = clock_->now();
    auto localTime = *std::localtime( &ct );
    constexpr auto formatDateTime = "%Y%m%d%H%M";
    std::stringstream ss;
    ss << std::put_time( &localTime, formatDateTime );
    std::filesystem::path path( "./log_"+ss.str() );
    return path;
}

}
