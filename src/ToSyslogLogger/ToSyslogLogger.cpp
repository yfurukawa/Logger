#include <fstream>
#include <iostream>
#include <unistd.h>
#include "ToSyslogLogger.h"

namespace AbstLogger 
{

ToSyslogLogger::ToSyslogLogger( std::unique_ptr<::IUdpClient> udpClient )
    : facility_(Facility::local1),
        version_("1"),
        udpClient_( std::move(udpClient) )
{
}

void ToSyslogLogger::log( const std::string logContent, Severity severity ) const
{
    std::string content = prival(severity) + version_ + " " + currentTime() + " " 
        + getHostname() + " " + getProcessName() + " - - - " + logContent;
    udpClient_->send( content );
}

std::string ToSyslogLogger::prival( Severity const& severity ) const
{
    return "<" + std::to_string( static_cast<int>(facility_) * 8 + static_cast<int>(severity) ) + ">";
}

std::string ToSyslogLogger::getHostname() const
{
    size_t bufferSize( 1024 );
    char hostname[bufferSize];
    gethostname( hostname, bufferSize );
    return std::string( hostname );
}

std::string ToSyslogLogger::getProcessName() const
{
    std::ifstream comm("/proc/self/comm");
    std::string processName{};
    getline( comm, processName );
    return processName;
}

}
