/*!
 @file      Client.h
 @brief     Loggerの簡単な使い方を見せる
*/
#pragma once

// ---------------< include >----------------------------

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     Client
 @brief     Loggerの簡単な使い方を見せる
*/
class Client final
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    Client() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    ~Client() = default;

    /*!
    @brief  Loggerを使う
    */
    void run();
};
