#include "../includes/menu.h"

Menu::Menu(vector<string> options){
    this->prevActiveItems.push_back(options);
    this->activeItems = this->prevActiveItems.back();
    this->currentItem = &this->activeItems[0];
}

vector<string> Menu::getActiveItems()
{
    return this->activeItems;
}

void Menu::setActiveItems(vector<string> newItems){
    this->activeItems = newItems;
}