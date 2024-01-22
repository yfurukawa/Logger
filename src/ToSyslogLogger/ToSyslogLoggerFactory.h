/*!
 @file      ToSyslogLoggerFactory.h
 @brief     syslogサーバへログを出力するロガーのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include "../LoggerFactory.h"
#include "IPv4.h"
#include "ToSyslogLogger.h"
#include "UdpClient.h"
#include "Port.h"
#include "Hostname.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToSyslogLoggerFactory
 @brief     syslogサーバへログを出力するロガーのファクトリクラス
 @note      本クラスとLoggerクラスでAbstruct Factoryパターンを形成している
*/
class ToSyslogLoggerFactory final : public LoggerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToSyslogLoggerFactory() {
        ToSyslogLoggerFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToSyslogLoggerFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return ToSyslogLoggerFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     ToSyslogLoggerインスタンス
    */
    Logger* createLogger() override
    {
        if( !logger_ ) {
            std::lock_guard<std::mutex> lock(loggerMtx_);
            if( !logger_ ) {
                auto ip = new IPv4("127.0.0.1");
                auto host = new Hostname("localhost");
                auto port = new Port(514);
                //logger_ = dynamic_cast<Logger*>( new ToSyslogLogger( std::make_unique<::UdpClient>( ip, port ) ) );
                logger_ = dynamic_cast<Logger*>( new ToSyslogLogger( std::make_unique<::UdpClient>( host, port ) ) );
                delete ip;
                delete host;
                delete port;
            }
        }
        return logger_;
    }

private:
    static bool destroyed_;    //!< インスタンスの破棄ステータス
    Logger* logger_{nullptr};  //!< 具象クラスのインスタンス
};

}
