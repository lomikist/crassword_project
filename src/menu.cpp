#include "../includes/menu.h"

Menu::Menu(string name){
    this->items.push_back("start");
    this->items.push_back("exit");
    this->items.push_back("about me");
    this->active_item = &items[0];
}
void Menu::change_item(int key){
    // for down
    if ( key == 1 && this->active_item != &items[items.size() - 1] )
    {
        this->active_item = this->active_item + 1;
    }
    // for up
    else if (key == 0 && this->active_item != &items[0])
    {
        this->active_item = this->active_item - 1;
    }
}