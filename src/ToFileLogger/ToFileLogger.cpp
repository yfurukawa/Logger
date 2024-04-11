#include <chrono>
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "TextFileWriter.h"
#include "ToFileLogger.h"

namespace AbstLogger 
{

ToFileLogger::ToFileLogger( std::unique_ptr<::IClock> clock )
    : clock_( std::move(clock) ),
    fileWriter_( std::make_unique<::TextFileWriter>() )
{
    auto error = fileWriter_->openFile(createFilePath());
    if(error)
    {
        std::cerr << error.value() << std::endl;
    }
}

ToFileLogger::~ToFileLogger()
{
    fileWriter_->closeFile();
}

void ToFileLogger::log( const std::string logContent, Severity severity ) const
{
    std::stringstream ss;
    ss << currentTime() << " : " << severityName[static_cast<int>(severity)] << " : " << logContent << std::endl;
    auto writeErro = fileWriter_->write( ss.str() );
    if( writeErro ) {
        std::cerr << writeErro.value() << std::endl;
    }
}

std::filesystem::path ToFileLogger::createFilePath() const
{
    std::filesystem::path path( "./log_"+ clock_->nowIso8601Basic());
    return path;
}

}
