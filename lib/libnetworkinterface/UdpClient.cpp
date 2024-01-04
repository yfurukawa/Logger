#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "UdpClient.h"
#include "Port.h"
#include "IPv4.h"

UdpClient::UdpClient( std::unique_ptr<IPv4> ipAddress, std::unique_ptr<Port> port )
    : ipAddress_( std::move(ipAddress) ),
    port_( std::move(port) )
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

void UdpClient::send( std::string content ) const
{
    auto result = sendto( sock_, content.c_str(), content.length(), 0, (struct sockaddr *)&addr_, sizeof(addr_) );
    if( result < 1 ) {
        perror("sendto");
        exit(1);
    }
}
