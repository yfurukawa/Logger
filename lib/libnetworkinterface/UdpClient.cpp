#include <netdb.h>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "UdpClient.h"
#include "Port.h"
#include "Hostname.h"
#include "IPv4.h"

UdpClient::UdpClient( std::unique_ptr<IPv4> ipAddress, std::unique_ptr<Port> port )
    : ipAddress_( std::move(ipAddress) ),
    port_( std::move(port) ),
    hostname_(nullptr)
{
    this->initialize();
}

UdpClient::UdpClient( std::unique_ptr<Hostname> hostname, std::unique_ptr<Port> port )
    : ipAddress_( nullptr ),
    port_( std::move(port) ),
    hostname_( std::move(hostname) )
{
    this->resolveHostname();
    this->initialize();
}

void UdpClient::send( std::string content ) const
{
    auto result = sendto( sock_, content.c_str(), content.length(), 0, (struct sockaddr *)&addr_, sizeof(addr_) );
    if( result < 1 ) {
        perror("sendto");
        exit(1);
    }
}

void UdpClient::initialize()
{
    sock_ = socket( AF_INET, SOCK_DGRAM, 0 );
    if( sock_ == -1 ) {
        perror("socket");
        exit(1);
    }
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr( ipAddress_->get().c_str() );
    addr_.sin_port = htons( port_->get() );
}

void UdpClient::resolveHostname()
{
    auto host = gethostbyname( hostname_->get().c_str() );
    std::stringstream ss;
    ss << (unsigned char)*((host->h_addr_list[0])) << "."
    << (unsigned char)*((host->h_addr_list[0] + 1)) << "."
    << (unsigned char)*((host->h_addr_list[0] + 2)) << "."
    << (unsigned char)*((host->h_addr_list[0] + 3));
    ipAddress_ = std::make_unique<IPv4>(ss.str());
}
