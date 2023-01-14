#pragma once
#include <iosfwd>
#include <optional>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

#include "use_cases.h"
#include "json_parser.h"
#include "menu.h"

namespace menu {
class Menu;
}

namespace app {
class UseCases;
}

namespace ui {

class View {
public:
    View(menu::Menu& menu, std::istream& input, std::ostream& output);

private:
    bool AddPlayer(std::istream& cmd_input);
    bool ShowMapList();
    bool ImplementTick(std::istream& cmd_input);
    bool ShowMapConfig(std::istream& cmd_input);
    bool ShowState(std::istream& cmd_input);
    bool ShowPlayerList(std::istream& cmd_input);
    bool SendMovement(std::istream& cmd_input);
    bool ShowRecords(std::istream& cmd_input);

    std::map<size_t, std::pair<std::string, std::string>> player_list;

    menu::Menu& menu_;
    std::istream& input_;
    std::ostream& output_;
    std::string ShowPlayers();
};

}  // namespace ui
