#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h"
#include "gui.h"
#include "board.h"

class Core{
private:
    // string active_state;
    Gui* user_interface;
public:
    Core(int = 30, int = 30);
    ~Core();
    void detecting_key();
    void startGame();
    vector<vector<char>> table;

    void getDecimal(int& );
};
