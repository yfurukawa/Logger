/*!
 @file      ToSyslogLogger.h
 @brief     syslogサーバへログを出力するロガー
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include "../Logger.h"
#include "../Severity.h"
#include "Facility.h"
#include "IUdpClient.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ToSyslogLogger
 @brief     syslogサーバへログを出力するロガー
 @note      本クラスとLoggerFactoryクラスでAbstruct Factoryパターンを形成している
*/
class ToSyslogLogger final : public Logger
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ToSyslogLogger() = delete;

    /*!
    @brief  コンストラクタ
    */
    ToSyslogLogger( std::unique_ptr<::IUdpClient> udpClient );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ToSyslogLogger() = default;

    /*!
    @brief      ログデータを記録する
    @param[in]  logContent 記録内容
    @param[in]  severity   RFC5424に規定されているseverity
    */
    void log( const std::string logContent, Severity severity = Severity::informational ) const override;

private:
    Facility const facility_;                  //!< Syslogサーバが待ち受けているfacility
    std::string const version_;                //!< Syslogのバージョン "1"固定
    std::unique_ptr<::IUdpClient> udpClient_;  //!< UDP送信するネットワークインターフェース

    /*!
    @brief      RFC5424で規定されているsyslogメッセージのPRI値を生成する
    @param[in]  severity 送信メッセージのSeverity
    @return     生成されたPRI値の文字列
    @note       severityはRFC5424に準拠していること
    */
    std::string prival( Severity const& severity ) const;

    /*!
    @brief      ホスト名を取得する
    @return     動作しているホスト名
    @note       linux用
    */
    std::string getHostname() const;

    /*!
    @brief      プログラムのプロセス名を取得する
    @return     取得したプロセス名
    @note       linux用
    */
    std::string getProcessName() const;
};

}
