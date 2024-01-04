/*!
 @file      IUdpClient.h
 @brief     UDP Client
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------
class IPv4;
class Port;

/*!
 @class     IUdpClient
 @brief     UDP Client
 @attention
*/
class IUdpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    IUdpClient() = default;

    /*!
    @brief      コンストラクタ
    @param[in]  ipAddress サーバアドレス
    @param[in]  port サーバの待ち受けポート番号
    */
    IUdpClient( std::unique_ptr<IPv4> ipAddress, std::unique_ptr<Port> port ){};

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~IUdpClient() = default;

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    virtual void send( const std::string content ) const = 0;

};
