/*!
 @file      ContentBuffer.h
 @brief     ログデータの出力バッファ
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>
#include <queue>
#include <string>

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     ContentBuffer
 @brief     ログデータの出力バッファ
 @note      本クラスはログデータをファイルに書き出す前の出力バッファである
*/
class ContentBuffer final
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ContentBuffer() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ContentBuffer() = default;

    /*!
    @brief      バッファにデータを追加する
    @param[in]  content 出力データ
    */
    void addContent( const std::string content );

    /*!
    @brief      バッファからデータを取り出す
    @return     取り出したデータ
    */
    std::string pickUpContent();

    /*!
    @brief      バッファ内のデータ有無を確認する
    @return     true : バッファ内にデータあり
    */
    bool isStoredContent();

private:
    std::mutex bufferMtx_;                     //!< バッファ読み書き時の保護用mutex
    std::queue<std::string> contentBuffer_{};  //!< 出力バッファ

};

}
