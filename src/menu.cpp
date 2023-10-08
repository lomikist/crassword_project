#include "../includes/menu.h"

Menu::Menu(string name){
    this->items.push_back("start");
    this->items.push_back("exit");
    this->items.push_back("about me");
    this->active_item = &items[0];
}
