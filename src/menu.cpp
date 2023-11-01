#include "../includes/menu.h"

Menu::Menu(){
    this->items.push_back("one");
    this->items.push_back("two");
    this->items.push_back("tree");
    this->active_item = &items[0];
}