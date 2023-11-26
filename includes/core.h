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
    // string active_state;
    Gui* user_interface;
    vector<Word> words;
public:
    Core(int = 30, int = 30);
    ~Core();
    void detecting_key();
    void startGame();
    vector<vector<char>> table;
    Model* model;
    void fillTable();
    vector<int> usedWordsIndexes; 
private:
    void fillWords();
    int longestIndex;
    int longestSize;
    void fillVertical(int, int, char*);
    void fillHorizontal();
    bool verticalSuitable(int, int, std::string*);
};
