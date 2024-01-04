/*!
 @file      Severity.h
 @brief     IETF-Syslogメッセージフォーマット(RFC5424)で規定されているSeverity
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <array>
#include <string>

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     Severity
 @brief     IETF-Syslogメッセージフォーマット(RFC5424)で規定されているSeverity
*/
enum class Severity {
    emergency,
    alert,
    critical,
    error,
    warning,
    notice,
    informational,
    debug
};

static const std::array<std::string, 8> severityName {
    "emergency",
    "alert",
    "critical",
    "error",
    "warning",
    "notice",
    "informational",
    "debug"
};

}
