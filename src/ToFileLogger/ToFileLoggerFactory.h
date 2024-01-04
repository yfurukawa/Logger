/*!
 @file      ToFileLoggerFactory.h
 @brief     ログファイルへログを出力するロガーのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <mutex>
#include "../LoggerFactory.h"
#include "Chronos.h"
#include "ToFileLogger.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToFileLoggerFactory
 @brief     ログファイルへログを出力するロガーのファクトリクラス
 @note      本クラスとLoggerクラスでAbstruct Factoryパターンを形成している
*/
class ToFileLoggerFactory final : public LoggerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToFileLoggerFactory() {
        ToFileLoggerFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToFileLoggerFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return ToFileLoggerFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     ToFileLoggerインスタンス
    */
    Logger* createLogger() override
    {
        if( !logger_ ) {
            std::lock_guard<std::mutex> lock(loggerMtx_);
            if( !logger_ ) {
                logger_ = dynamic_cast<Logger*>( new ToFileLogger( std::make_unique<Chronos>() ) );
            }
        }
        return logger_;
    }

private:
    static bool destroyed_;    //!< インスタンスの破棄ステータス
    Logger* logger_{nullptr};  //!< 具象クラスのインスタンス
};

}
