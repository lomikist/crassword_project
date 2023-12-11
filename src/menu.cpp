#include "../includes/menu.h"

Menu::Menu(vector<string> options){
    this->activeItems = options;
    this->prevActiveItems = options;
    this->currentItem = &this->activeItems[0];
}

Menu::~Menu(){

}

vector<string> Menu::getActiveItems()
{
    return this->activeItems;
}

void Menu::setActiveItems(vector<string> newItems){
    this->activeItems = newItems;
}