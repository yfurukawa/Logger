#include <chrono>
#include <thread>
#include "Client.h"
#include "Logger.h"
#include "LoggerFactory.h"

void Client::run()
{
    AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[Client] : test log.");
}
