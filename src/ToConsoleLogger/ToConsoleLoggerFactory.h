/*!
 @file      ToConsoleLoggerFactory.h
 @brief     コンソールへログを表示するロガーのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include "../LoggerFactory.h"
#include "ToConsoleLogger.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToConsoleLoggerFactory
 @brief     コンソールへログを表示するロガーのファクトリクラス
 @note      本クラスとLoggerクラスでAbstruct Factoryパターンを形成している
*/
class ToConsoleLoggerFactory final : public LoggerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToConsoleLoggerFactory() {
        ToConsoleLoggerFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToConsoleLoggerFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return ToConsoleLoggerFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     ToConsoleLoggerインスタンス
    */
    Logger* createLogger() override
    {
        if( !logger_ ) {
            std::lock_guard<std::mutex> lock(loggerMtx_);
            if( !logger_ ) {
                logger_ = dynamic_cast<Logger*>( new ToConsoleLogger() );
            }
        }
        return logger_;
    }

private:
    static bool destroyed_;    //!< インスタンスの破棄ステータス
    Logger* logger_{nullptr};  //!< 具象クラスのインスタンス
};

}
