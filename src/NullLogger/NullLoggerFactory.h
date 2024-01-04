/*!
 @file      NullLoggerFactory.h
 @brief     何もロギングしないロガーのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include "../LoggerFactory.h"
#include "NullLogger.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     NullLoggerFactory
 @brief     何もロギングしないロガーのファクトリクラス
 @note      本クラスとLoggerクラスでAbstruct Factoryパターンを形成している
*/
class NullLoggerFactory final : public LoggerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    NullLoggerFactory() {
        NullLoggerFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~NullLoggerFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return NullLoggerFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     NullLoggerインスタンス
    */
    Logger* createLogger() override
    {
        if( !logger_ ) {
            std::lock_guard<std::mutex> lock(loggerMtx_);
            if( !logger_ ) {
                logger_ = dynamic_cast<Logger*>( new NullLogger() );
            }
        }
        return logger_;
    }

private:
    static bool destroyed_;    //!< インスタンスの破棄ステータス
    Logger* logger_{nullptr};  //!< 具象クラスのインスタンス
};

}
