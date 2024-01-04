/*!
 @file      LoggerFactory.h
 @brief     LoggerFactoryの抽象クラス
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace AbstLogger {
// ---------< forward declaration >----------------------
class Logger;

/*!
 @class     LoggerFactory
 @brief     LoggerFactoryの抽象クラス
 @note      本クラスとLoggerクラスでAbstruct Factoryパターンを形成している
*/
class LoggerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    LoggerFactory() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~LoggerFactory() = default;

    /*!
    @brief      LoggerFactoryインスタンスを生成する
    @return     LoggerFactoryインスタンス
    @note       本メソッドは、各具象クラス内でLoggerFactoryクラスのメソッドとして実装される。
    */
    static LoggerFactory* getInstance();

    /*!
    @brief      Loggerインスタンスを生成する
    @return     Loggerインスタンス
    */
    virtual Logger* createLogger() = 0;

protected:
    std::mutex loggerMtx_;  //!< インスタンス生成処理保護用mutex
};

}
