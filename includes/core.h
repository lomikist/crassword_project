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
    Gui* user_interface;
public:
    Core();
    ~Core();
    void detecting_key();
};
