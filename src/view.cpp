#include "view.h"

using namespace std::literals;
//namespace ph = std::placeholders;

namespace ui {

    View::View(menu::Menu& menu, std::istream& input, std::ostream& output)
        :   menu_{menu}, input_{input}, output_{output}
    {
        menu_.AddAction(  //
                "AddPlayer"s, "name mapId"s, "Adds player"s,
                [this](auto& cmd_input) { return AddPlayer(cmd_input); }
                );
        menu_.AddAction(  //
                "MapList"s, ""s, "Shows list of map"s,
                [this](auto& cmd_input) { return ShowMapList(); }
                );
        menu_.AddAction(  //
                "MapConfig"s, "mapId"s, "Shows map config"s,
                [this](auto& cmd_input) { return ShowMapConfig(cmd_input); }
                );
        menu_.AddAction(  //
                "Tick"s, "dt"s, "Ticks server state"s,
                [this](auto& cmd_input) { return ImplementTick(cmd_input); }
                );
        menu_.AddAction(  //
                "ShowState"s, ""s, "Shows player state"s,
                [this](auto& cmd_input) { return ShowState(cmd_input); }
                );
        menu_.AddAction(  //
                "ShowPlayerList"s, ""s, "Shows player list"s,
                [this](auto& cmd_input) { return ShowPlayerList(cmd_input); }
                );

        menu_.AddAction(  //
                "SendPlayerMovement"s, ""s, "Sends player movement"s,
                [this](auto& cmd_input) { return SendMovement(cmd_input); }
                );
        menu_.AddAction(  //
                "ShowRecords"s, "start maxItems"s, "Shows records begin at start with maxItems offset"s,
                [this](auto& cmd_input) { return ShowRecords(cmd_input); }
                );
    }

    bool View::AddPlayer(std::istream& cmd_input) {
        try {
            std::string name;
            std::string mapId;

            std::string temp_string;
            std::string input_string;

            std::getline(cmd_input, input_string);

            std::istringstream iss(input_string);
            iss >> name >> mapId;
            auto player_token_json = use_cases::Authorize(name, mapId);
            auto [token, id] = json_parser::parseToken(player_token_json);
            player_list[id] = std::make_pair(token, name);
        } catch (const std::exception& ex) {
            output_ << "Failed to add player"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }

    bool View::ShowMapList() {
        try {
            auto map_list = use_cases::GetMapList();
            std::vector<json_parser::MapParameters> map_params = json_parser::parseMapList(map_list);
            for (const auto& mp : map_params) {
                std::cout << mp << std::endl;
            }
        } catch (const std::exception& ex) {
            output_ << "Failed show map list"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }

    bool View::ShowMapConfig(std::istream& cmd_input) {
        try {
            std::string mapId;
            std::string input_string;
            std::getline(cmd_input, input_string);
            std::istringstream iss(input_string);
            iss >> mapId;
            auto map_config = use_cases::GetMapId(mapId);
            std::cout << map_config << std::endl;
        } catch (const std::exception& ex) {
            output_ << "Failed to add player"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }


    bool View::ImplementTick(std::istream& cmd_input) {
        try {
            size_t time_delta;
            std::string input_string;

            std::getline(cmd_input, input_string);
            std::istringstream iss(input_string);
            if (!(iss>>time_delta)) {throw std::invalid_argument("Tick should be a number!"s);}
            auto tick_json = use_cases::Tick(time_delta);
            std::cout << "tick request:\n" << tick_json << std::endl;
            std::cout << "Ticking server state with "s << time_delta << " seconds"s << std::endl;
        } catch (const std::exception& ex) {
            output_ << "Failed to tick"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }

    bool View::ShowState(std::istream& cmd_input) {
        try {
            std::string player_token = ShowPlayers();
            auto res = use_cases::GetState(player_token);
            std::cout << "GetState request:\n" << res << std::endl;
        } catch (const std::exception& ex) {
            output_ << "Failed to add player"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }

    bool View::ShowPlayerList(std::istream& cmd_input) {
        try {
            std::string player_token = ShowPlayers();
            auto res = use_cases::GetPlayerList(player_token);
            std::cout << "GetPlayerList request:\n" << res << std::endl;
        } catch (const std::exception& ex) {
            output_ << "Failed to add player"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }
    
    bool View::SendMovement(std::istream& cmd_input) {
        try {
            std::string player_token = ShowPlayers();

            std::cout << "Type movement character [ U, D, L, R, __empty__]" << std::endl;
            std::string movement;
            std::getline(std::cin, movement);
            auto res = use_cases::SendPlayerMovement(player_token, movement);
            std::cout << "SendPlayerMovement request:\n" << res << std::endl;
        } catch (const std::exception& ex) {
            output_ << "Failed to add player"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }

    bool View::ShowRecords(std::istream& cmd_input) {
        try {
            size_t start;
            size_t maxItems;
            std::string input_string;

            std::getline(cmd_input, input_string);
            std::istringstream iss(input_string);
            if (!(iss>>start>>maxItems)) {throw std::invalid_argument("start and maxItems should be a number!"s);}
            auto records_json = use_cases::GetRecords(start, maxItems);
            std::cout << "Records request:\n" << records_json << std::endl;
        } catch (const std::exception& ex) {
            output_ << "Failed to tick"sv << std::endl;
            output_ << ex.what() << std::endl;
        }
        return true;
    }


    std::string View::ShowPlayers() {
        if (player_list.empty()) {
            throw std::invalid_argument("No players in player list!"s);
        }

        std::cout << "Choose registered player: " << std::endl;
        for (const auto [id, t] : player_list) {
            std::cout << id << ". " << std::get<1>(t) << "with token: " << std::get<0>(t) << std::endl;
        }
        size_t player_id;
        std::string input_string;
        std::getline(std::cin, input_string);
        std::istringstream iss(input_string);
        if (!(iss>>player_id)) {throw std::invalid_argument("PlayerId should be a number!"s);}
        return std::get<0>(player_list.at(player_id));
    }
}  // namespace ui
