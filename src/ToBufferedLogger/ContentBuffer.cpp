#include "ContentBuffer.h"

namespace AbstLogger
{

void ContentBuffer::addContent( std::string content )
{
    std::lock_guard<std::mutex> lock(bufferMtx_);
    contentBuffer_.push( content );
}

std::string ContentBuffer::pickUpContent()
{
    std::lock_guard<std::mutex> lock(bufferMtx_);
    std::string content( contentBuffer_.front() );
    contentBuffer_.pop();
    return content;
}

bool ContentBuffer::isStoredContent()
{
    std::lock_guard<std::mutex> lock(bufferMtx_);
    return !contentBuffer_.empty();
}

}
