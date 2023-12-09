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
    Menu* startMenu;
    Board* gameBoard;
    static int windowHeight;
    static int windowWidth;
public:
    Gui(int, int);
    ~Gui();
    static void adjustScreenSize();
    void changeItem(int );
    
    void startDrawBoadr(std::vector<std::vector<char>>& );

    void drawStartMenu(int,int);
    void drawVerticalLines();
    void drawHorizontalLines();
    int detectConrtolKeys();
    void clearScreen();
    int getDecimalNumber();
};
