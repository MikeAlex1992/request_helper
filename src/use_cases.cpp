#include "use_cases.h"

namespace use_cases {
    std::string GetMapList() {
        const std::string url = address + "/api/v1/maps/"s;
        return request_manager::getGetRequest(url);
    }

    std::string GetMapId(const std::string& map_id) {
        const std::string url = address + "/api/v1/maps/"s + map_id;
        return request_manager::getGetRequest(url);
    }

    std::string Tick(size_t time_delta) {
        const std::string url = address + "/api/v1/game/tick"s;
        const std::string postthis = "{\"timeDelta\":" + std::to_string(time_delta) + "}";
        return request_manager::getPostRequest(url, postthis);
    }

    std::string Authorize(const std::string& name, const std::string& mapId) {
        const std::string url = address + "/api/v1/game/join"s;
        const std::string postthis = "{\"userName\":"s +
            "\""s + name + "\", \"mapId\": \""s + mapId + "\"}"s;
        return request_manager::getPostRequest(url, postthis);
    }

    std::string GetState(const std::string& token) {
        const std::string url = address + "/api/v1/game/state"s;
        return request_manager::getAuthentificationRequest(url, token);
    }

    std::string GetPlayerList(const std::string& token) {
        const std::string url = address + "/api/v1/game/players"s;
        return request_manager::getAuthentificationRequest(url, token);
    }

    std::string SendPlayerMovement(const std::string& token, const std::string& movement) {
        const std::string url = address + "/api/v1/game/player/action"s;
        const std::string postthis = "{\"move\": \""s + movement + "\"}"s;

        return request_manager::getAuthentificationPostRequest(url, token, postthis);
    }

    std::string GetRecords(size_t start, size_t maxItems) {
        const std::string url = address + 
            "/api/v1/game/records?start="s + std::to_string(start) + "&maxItems=" + std::to_string(maxItems);
        return request_manager::getGetRequest(url);
    }
}
