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
public:
    Core(int = 30, int = 30);
    void detecting_key();
    void startGame();
    std::vector<std::vector<char>> table;
    Model* model;
    void fillTable();
    std::vector<int> usedWordsIndexes; 
private:
    void fillWords();
    int longestIndex;
    int longestSize;
    
    void fillVertical(int, int, char &);
    void fillHorizontal(int, int, char &);
    void setColor();
    bool verticalSuitable(int ,int, int, std::string &);
    bool horizontalSuitable(int, int, int, std::string &);

    bool containsElement(std::vector<int> &, int &);
    int randomStrIndex(std::string &, std::vector<int> &);
};
