/*!
 @file      ToConsoleLogger.h
 @brief     コンソールへログを表示するロガー
*/
#pragma once

// ---------------< include >----------------------------
#include "../Logger.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToConsoleLogger
 @brief     コンソールへログを表示するロガー
 @note      本クラスとLoggerFactoryクラスでAbstruct Factoryパターンを形成している
*/
class ToConsoleLogger final : public Logger
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToConsoleLogger() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToConsoleLogger() = default;

    /*!
    @brief      ログデータを記録する
    @param[in]  logContent 記録内容
    @param[in]  severity   RFC5424に規定されているseverity
    */
    void log( const std::string logContent, Severity severity = Severity::informational ) const override;
};

}
