/*!
 @file      ToBufferedLogger.h
 @brief     一旦出力バッファにログを溜めた後、ファイルへログを出力するロガー
*/
#pragma once

// ---------------< include >----------------------------
#include <condition_variable>
#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include "../Logger.h"
#include "IClock.h"
#include "ITextFileWriter.h"

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------
class ContentBuffer;

/*!
 @class     ToBufferedLogger
 @brief     一旦出力バッファにログを溜めた後、ファイルへログを出力するロガー
 @note      本クラスとLoggerFactoryクラスでAbstruct Factoryパターンを形成している
*/
class ToBufferedLogger final : public Logger
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    ToBufferedLogger() = default;

    /*!
    @brief      コンストラクタ
    @param[in]  clock 日時情報を提供するクラス
    */
    ToBufferedLogger( std::unique_ptr<::IClock> clock );

    /*!
    @brief  デフォルトデストラクタ
    */
    ~ToBufferedLogger();

    /*!
    @brief      ログデータを記録する
    @param[in]  logContent 記録内容
    @param[in]  severity   RFC5424に規定されているseverity
    */
    void log( const std::string logContent, Severity severity = Severity::informational ) const override;

    /*!
    @brief      スレッドの修了処理
    @attention  インスタンス破棄前に本スレッドを呼出し、スレッドを停止すること
    */
    void stopBehavior();

private:
    bool stop_;                                      //!< バッファリングされたログをファイルに書き出すスレッドの停止フラグ
    bool finished_;                                  //!< 全スレッドの処理完了フラグ。処理完了をもってスレッドの破棄が可能となる
    std::unique_ptr<::IClock> clock_;                //!< 日時情報を提供するインスタンス
    std::unique_ptr<::ITextFileWriter> fileWriter_;  //!< ログデータをファイルへ書き出すための出力ファイルインターフェース
    std::unique_ptr<ContentBuffer> contentBuffer_;   //!< ログデータの出力バッファ
    std::thread observerThread_;                     //!< 出力バッファ監視スレッド
    
    std::mutex bufferMtx_;                           //!< 出力バッファアクセス保護用mutex
    mutable std::condition_variable notEmpty_{};     //!< 出力バッファ監視スレッド待機用状態変数

    /*!
    @brief      ログデータを保存するファイルパスを生成する
    @return     ログデータ記録用ファイルへのパス
    */
    std::filesystem::path createFilePath() const;

    /*!
    @brief      出力バッファ監視処理
    @note       出力バッファにデータが追加されたら、それをファイルに出力する
    */
    void observeLogData();

};

}
