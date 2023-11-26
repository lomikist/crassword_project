#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h"
#include "board.h"

using namespace std;
class Gui
{
private:

public:
    Gui(int, int);
    ~Gui();
    Menu* startMenu;
    Board* gameBoard;
    
    void changeItem(int );
    
    void startDrawBoadr(vector<vector<char>>& );
    
    void drawStartMenu(int,int);

    static void adjustScreenSize();
    static int windowHeight;
    static int windowWidth;
    void drawVerticalLines();
    void drawHorizontalLines();

    int detectConrtolKeys();
    void clearScreen();
    int getDecimalNumber();
};
