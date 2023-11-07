#include "../includes/menu.h"

Menu::Menu(vector<string> options){
    this->startMenuItems = options;
    this->startMenuActiveItem = &this->startMenuItems[0];
}

Menu::~Menu(){

}