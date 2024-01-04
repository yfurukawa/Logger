/*!
 @file      Logger.h
 @brief     Loggerの抽象クラス
*/
#pragma once

// ---------------< include >----------------------------
#include "Severity.h"
#include "ToISO8601String.hpp"

// --------------< namespace >---------------------------
namespace AbstLogger {
// ---------< forward declaration >----------------------

/*!
 @class     Logger
 @brief     Loggerの抽象クラス
 @note      本クラスとLoggerFactoryクラスでAbstruct Factoryパターンを形成している
*/
class Logger
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    Logger() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~Logger() = default;

    /*!
    @brief      ログデータを記録する
    @param[in]  logContent 記録内容
    @param[in]  severity   RFC5424に規定されているseverity
    */
    virtual void log( const std::string logContent, Severity severity = Severity::informational ) const = 0;

protected:
    /*!
    @brief      現在日時
    @note       ISO8601準拠の日時文字列を取得する。<br>toString_iso8601メソッドの第2引数により秒の精度を変更することが可能。
    */
    std::string currentTime() const
    {
        return toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>();
    }
};

}
