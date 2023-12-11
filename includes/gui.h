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
    Menu* menu;
    Board* gameBoard;
    static int windowHeight;
    static int windowWidth;
public:
    Gui(int, int);
    ~Gui();
    static void adjustScreenSize();
    void changeItem(int );
    void changeConsoleColor(const int);
    void changeWindowColor(const int);
    void startDrawBoadr(std::vector<std::vector<char>>& );
    void initScreen();
    void drawMenu(int,int);
    void drawVerticalLines();
    void drawHorizontalLines();
    int detectConrtolKeys();
    void clearScreen();
    int getDecimalNumber();
    void initMenu(int, int);
};
