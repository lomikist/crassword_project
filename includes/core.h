#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h" 
#include "gui.h"
#include "board.h"
#include "word.h"
#include "model.h"

class Core{
private:
    string active_state;
    Gui* user_interface;
    std::vector<Word> words;
    std::string controlType = "keyboard";
public:
    Core(int = 30, int = 30);
    void detecting_key();
    int startGame();
    void fillTable();
    void getCords(std::pair<int, int> &);

    std::vector<std::vector<char>> table;
    std::vector<std::vector<char>> showTable;
    std::vector<int> usedWordsIndexes;
    Model* model;
private:
    void fillWords();
    int longestIndex;
    int longestSize;
    bool compareTables(const std::vector<std::vector<char>>& table, const std::vector<std::vector<char>>& showTable);
    void fillVertical(int, int, char &);
    void fillHorizontal(int, int, char &);
    void setColor();
    bool verticalSuitable(int ,int, int, std::string &);
    bool horizontalSuitable(int, int, int, std::string &);
    void menuStartCase();
    void chngeMenuState(const std::vector<std::string>);
    void chngeMenuState();
    bool chekcHorizontal(int);
    bool checkVertical(int);
    void menuActions();
    void clearShowTable();

    bool containsElement(std::vector<int> &, int &);
    int randomStrIndex(std::string &, std::vector<int> &);
};
