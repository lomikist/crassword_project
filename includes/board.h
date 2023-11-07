#pragma once
#include <iostream>
#include <vector>
#include "string.h"
#include <utility> 
#include <ncurses.h>

class Board
{
public:
    // (width, height);
    Board(int, int);
    ~Board();
    std::pair<int, int> sizes;
    WINDOW* mainWindow;
    WINDOW* inputWindow;
};
