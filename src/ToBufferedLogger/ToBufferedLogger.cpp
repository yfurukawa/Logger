#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include "ContentBuffer.h"
#include "TextFileWriter.h"
#include "ToBufferedLogger.h"

namespace AbstLogger 
{

ToBufferedLogger::ToBufferedLogger( std::unique_ptr<::IClock> clock )
    : stop_(false), finished_(false),
    clock_( std::move(clock) ),
    fileWriter_( std::make_unique<::TextFileWriter>() ),
    contentBuffer_( std::make_unique<ContentBuffer>() ),
    observerThread_( std::thread( &ToBufferedLogger::observeLogData, this ) )
{
    fileWriter_->openFile(createFilePath());
    // インスタンス生成直後に1つログを出力して修了するとスレッドが待ち状態になる前に
    // プログラムが修了する場合がある。この場合にスレッドが正常に修了しないので、
    // 対策として少し待ち時間を取る。
    // TODO 他の対策に変えた方が良い
    std::this_thread::sleep_for( std::chrono::milliseconds(1) );
}

ToBufferedLogger::~ToBufferedLogger()
{
    fileWriter_->closeFile();
    observerThread_.detach();
}

void ToBufferedLogger::log( const std::string logContent, Severity severity ) const
{
    std::stringstream ss;
    ss << currentTime() << " : " << severityName[static_cast<int>(severity)] << " : " << logContent << std::endl;
    contentBuffer_->addContent( ss.str() );
    notEmpty_.notify_all();
}

void ToBufferedLogger::stopBehavior()
{
    stop_ = true;
    notEmpty_.notify_all();
    while( !finished_ ){}
}

std::filesystem::path ToBufferedLogger::createFilePath() const
{
    const auto& ct = clock_->now();
    auto localTime = *std::localtime( &ct );
    constexpr auto formatDateTime = "%Y%m%d%H%M";
    std::stringstream ss;
    ss << std::put_time( &localTime, formatDateTime );
    std::filesystem::path path( "./log_"+ss.str() );
    return path;
}

void ToBufferedLogger::observeLogData()
{
    std::optional<std::string> writeResult("");

    while ( !stop_ )
    {
        std::unique_lock<std::mutex> lock(bufferMtx_);
        notEmpty_.wait( lock, [this] {
            return contentBuffer_->isStoredContent() || stop_;
        });
        while ( contentBuffer_->isStoredContent() )
        {
            writeResult = fileWriter_->write( contentBuffer_->pickUpContent() );
            if( writeResult != std::nullopt ) {
                std::cerr << writeResult.value() << std::endl;
            }
        }
    }
    finished_ = true;
}

}
