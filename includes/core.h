#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h"
#include "gui.h"
#include "board.h"

class Core{
private:
    string active_state;
    Menu* menu;
    Gui* user_interface;
    Board* board;
public:
    Core();
    ~Core();
    void drawMenu(Menu *);
    void detecting_key();
};
