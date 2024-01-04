/*!
 @file      UdpClient.h
 @brief     UDP Client
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <string>
#include <arpa/inet.h>
#include "IUdpClient.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     UdpClient
 @brief     UDP Client
 @attention
*/
class UdpClient final : public IUdpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    UdpClient() = delete;

    /*!
    @brief      コンストラクタ
    @param[in]  ipAddress サーバアドレス
    @param[in]  port サーバの待ち受けポート番号
    */
    UdpClient( std::unique_ptr<IPv4> ipAddress, std::unique_ptr<Port> port );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~UdpClient() = default;

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    void send( const std::string content ) const override;

private:
    std::unique_ptr<IPv4> ipAddress_;  //!< サーバアドレス
    std::unique_ptr<Port> port_;       //!< サーバ待ち受けポート
    int sock_;                         //!< 送信用ソケット
    struct sockaddr_in addr_;          //!< ネットワーク設定
};
