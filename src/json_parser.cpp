#include "json_parser.h"

namespace json_parser {
    std::pair<std::string, size_t> parseToken(const std::string& token_json) {
        json result = json::parse(token_json);
        std::string player_token = result.at("authToken");
        size_t playerId = result.at("playerId");
        return {player_token, playerId};
    }

    std::vector<Player> parseState(const std::string& state_json) {
        json result = json::parse(state_json);
        std::vector<Player> player_vec;

        auto player_array = result.at("players");
        for (const auto& player : player_array) {
            auto bag_vec  =  player.at("bag");
            std::vector<Item> bag;
            for (const auto bgitem : bag_vec) {
                size_t id = bgitem.at("id");
                size_t type = bgitem.at("type");
                bag.emplace_back(id, type);
            }
            std::string dir = player.at("dir");
            Point2D pos{player.at("pos")[0], player.at("pos")[1]};
            size_t score = player.at("score");
            Point2D speed{player.at("speed")[0], player.at("speed")[1]};
            player_vec.emplace_back(bag, dir, pos, score, speed);
        }
        return player_vec;
    }

    std::vector<MapParameters> parseMapList(const std::string& state_json) {
        json result = json::parse(state_json);
        std::vector<MapParameters> map_vec;

        for (const auto& map_p : result) {
            std::string id  = map_p.at("id");
            std::string name = map_p.at("name");
            map_vec.emplace_back(id, name);
        }
        return map_vec;
    }

    std::ostream& operator<<(std::ostream& os, const Point2D& point) {
        os << "[" << point.x << ", " << point.y << "]";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << "[id = " << item.id << ", type = " << item.type << "]";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const MapParameters& mp) {
        os << "id = " << mp.id << ", name = " << mp.name;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "bag: ";
        for (const auto item : player.bag) {
            os << item << "\t";
        }
        os << "\n";

        os << "dir: " << player.dir << "\n" 
            << "pos: " << player.pos << "\n"
            << "score: " << player.score << "\n"
            << "speed: " << player.speed;

        return os;
    }
}


