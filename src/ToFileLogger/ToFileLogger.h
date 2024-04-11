/*!
 @file      ToFileLogger.h
 @brief     ログファイルへログを出力するロガー
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <memory>
#include <string>
#include "../Logger.h"
#include "IClock.h"
#include "ITextFileWriter.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToFileLogger
 @brief     ログファイルへログを出力するロガー
 @note      本クラスとLoggerFactoryクラスでAbstruct Factoryパターンを形成している
*/
class ToFileLogger final : public Logger
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToFileLogger() = default;

    /*!
    @brief      コンストラクタ
    @param[in]  clock 日時情報を提供するクラス
    */
    ToFileLogger( std::unique_ptr<::IClock> clock );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToFileLogger();

    /*!
    @brief      ログデータを記録する
    @param[in]  logContent 記録内容
    @param[in]  severity   RFC5424に規定されているseverity
    */
    void log( const std::string logContent, Severity severity = Severity::informational ) const override;

private:
    std::unique_ptr<::IClock> clock_;                 //!< 時刻情報を提供するクラス
    std::unique_ptr<::ITextFileWriter> fileWriter_;   //!< テキストファイル書出しクラス

    /*!
    @brief      ログデータを保存するファイルパスを生成する
    @return     ログデータ記録用ファイルへのパス
    */
    std::filesystem::path createFilePath() const;
};

}
