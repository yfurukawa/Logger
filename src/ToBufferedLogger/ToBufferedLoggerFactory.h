/*!
 @file      ToBufferedLoggerFactory.h
 @brief     一旦出力バッファにログを溜めた後、ファイルへログを出力するロガーのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <mutex>
#include "../LoggerFactory.h"
#include "Chronos.h"
#include "ToBufferedLogger.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToBufferedLoggerFactory
 @brief     一旦出力バッファにログを溜めた後、ファイルへログを出力するロガーのファクトリクラス
 @note      本クラスとLoggerクラスでAbstruct Factoryパターンを形成している
*/
class ToBufferedLoggerFactory final : public LoggerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToBufferedLoggerFactory() {
        ToBufferedLoggerFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToBufferedLoggerFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return ToBufferedLoggerFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     ToBufferedLoggerLoggerインスタンス
    */
    Logger* createLogger() override
    {
        if( !logger_ ) {
            std::lock_guard<std::mutex> lock(loggerMtx_);
            if( !logger_ ) {
                logger_ = dynamic_cast<Logger*>( new ToBufferedLogger( std::make_unique<Chronos>() ) );
            }
        }
        return logger_;
    }

private:
    static bool destroyed_;    //!< インスタンスの破棄ステータス
    Logger* logger_{nullptr};  //!< 具象クラスのインスタンス
};

}
