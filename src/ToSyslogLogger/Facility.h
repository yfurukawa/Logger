/*!
 @file      Facility.h
 @brief     IETF-Syslogメッセージフォーマット(RFC5424)で規定されているFacility
*/
#pragma once

// ---------------< include >----------------------------

// --------------< namespace >---------------------------
namespace AbstLogger {

// ---------< forward declaration >----------------------

/*!
 @class     Facility
 @brief     IETF-Syslogメッセージフォーマット(RFC5424)で規定されているFacility
*/
enum class Facility {
    kernel_message,
    user_level_message,
    mail_system,
    system_daemons,
    security_authorization_messages,
    messages_generated_internally_by_syslogd,
    line_printer_subsystem,
    network_news_subsystem,
    _UUCP_subsystem,
    clock_daemon,
    security_authorization_messages_2,
    FTP_daemon,
    NTP_subsystem,
    log_audit,
    log_alert,
    clock_daemon_2,
    local0,
    local1,
    local2,
    local3,
    local4,
    local5,
    local6,
    local7
};

}
