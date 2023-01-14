#include <string>
#include <iostream>
#include "view.h"
//#include "menu.h"
//========================================================================================

int main(void) {
    menu::Menu menu{std::cin, std::cout};
    menu.AddAction("Help"s, {}, "Show instructions"s, [&menu](std::istream&) {
        menu.ShowInstructions();
        return true;
    });
    menu.AddAction("Exit"s, {}, "Exit program"s, [&menu](std::istream&) {
        return false;
    });
    ui::View view{menu, std::cin, std::cout};
    menu.Run();

    return 0;
}
