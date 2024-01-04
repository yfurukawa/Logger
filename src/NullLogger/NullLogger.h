/*!
 @file      NullLogger.h
 @brief     何もロギングしないロガー
*/
#pragma once

// ---------------< include >----------------------------
#include "../Logger.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     NullLogger
 @brief     何もロギングしないロガー
 @note      本クラスとLoggerFactoryクラスでAbstruct Factoryパターンを形成している
*/
class NullLogger final : public Logger
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    NullLogger() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~NullLogger() = default;

    /*!
    @brief      ログデータを記録する
    @param[in]  logContent 記録内容
    @param[in]  severity   RFC5424に規定されているseverity
    */
    void log( const std::string logContent, Severity severity = Severity::informational ) const override;
};

}
