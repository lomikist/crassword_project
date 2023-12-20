#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <utility>
#include "menu.h"
#include "board.h"
#include "word.h"

using namespace std;
class Gui
{
private:

public:
    Menu* menu;
    Board* gameBoard;

    static int windowHeight;
    static int windowWidth;

    int verHorTurn = 0;
public:
    Gui(int, int);
    ~Gui();
    static void adjustScreenSize();
    void    changeItem(int );
    void    changeConsoleColor(const int);
    void    changeWindowColor(const int);

    void    drawBoadr(std::vector<std::vector<char>>& );
    void    drawChangedBoard(std::vector<std::vector<char>>& , std::pair<int, int>& , bool);
    void    drawQuestions(const std::vector<Word> &, const std::vector<int> &);
    void    drawInput();
    void    drawVerticalLines();
    void    drawHorizontalLines();
    void    drawWinWindow();


    void    initScreen();
    std::pair<int, int>  getKeyCords();
    void    drawSelectedField(const std::pair<int, int> &);
    void    drawMenu(int,int);
    int     detectConrtolKeys();
    void    clearScreen();
    int     getDecimalNumber(const std::string &);
    void    printErrors(const std::string &);
    void    initMenu(int, int);
    void    initGameBoard(int, int);
    void    initQuestBoard(int, int);
    void    clearWindow(WINDOW *);
    std::pair<int, int> getMouseCords();
private:
    bool    insideWindow(int , int , int , int , std::pair<int, int> );
};
