#include <regex>
#include "Hostname.h"

Hostname::Hostname(std::string hostname) : hostname_(std::move(hostname))
{
    // ホスト名がIPv4でないことを確認
    std::regex ipv4Regex(R"(^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$)");
    if( std::regex_match( hostname_, ipv4Regex) ) {
        std::__throw_invalid_argument("Hostname matches IPv4 format");
    }
    // ホスト名には下線(_)が含まれていてはならない
    std::regex includeUnderscore(R"(*underscore*)");
    if( std::regex_match(hostname_, includeUnderscore) ) {
        std::__throw_invalid_argument("Hostname does not includes underscore");
    }
    // ホスト名はダッシュ(-)で終わっていてはならない
    std::regex end(R"(*-$)");
    if( std::regex_match(hostname_, end) ) {
        std::__throw_invalid_argument("End of charactor of Hostname is dash");
    }
}

std::string Hostname::get() const
{
    return hostname_;
}
