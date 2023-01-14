#pragma once

#include <string>
#include "request_manager.h"
using namespace std::literals;

namespace {
    static const std::string server_address = "http://127.0.0.1"s;
    static const std::string port = "8080"s;
    static const std::string address = server_address + ":"s + port;
}

//=================================================================================================
namespace use_cases {
    std::string GetMapList();
    std::string GetMapId(const std::string& map_id);
    std::string Tick(size_t time_delta);
    std::string Authorize(const std::string& name, const std::string& mapId);
    std::string GetState(const std::string& token);
    std::string GetPlayerList(const std::string& token);
    std::string SendPlayerMovement(const std::string& token, const std::string& movement);
    std::string GetRecords(size_t start, size_t maxItems);
}
