#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h"
#include "gui.h"

class Core{
private:
    string active_state;
    Menu* menu;
    Gui* user_interface;
public:
    Core();
    ~Core();
    void drawMenu(Menu *);
    void detecting_key();
};
