#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace json_parser {
    struct Point2D {
        size_t x;
        size_t y;
    };

    struct Item {
        size_t id;
        size_t type;
    };

    struct Player {
        std::vector<Item> bag;
        std::string dir;
        Point2D pos;
        size_t score;
        Point2D speed;
    };

    struct MapParameters {
        std::string id;
        std::string name;
    };


    std::pair<std::string, size_t> parseToken(const std::string& token_json);
    std::vector<Player> parseState(const std::string& state_json);
    std::vector<MapParameters> parseMapList(const std::string& state_json);

    std::ostream& operator<<(std::ostream& os, const Point2D& point);
    std::ostream& operator<<(std::ostream& os, const Item& item);
    std::ostream& operator<<(std::ostream& os, const MapParameters& mp);
    std::ostream& operator<<(std::ostream& os, const Player& player);
}





