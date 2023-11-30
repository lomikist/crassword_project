#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h" 
#include "gui.h"
#include "board.h"
#include "word.h"
#include "../json/single_include/nlohmann/json.hpp"
// #include "core.h"

using json = nlohmann::json;

class Model
{
public:
    Model();
    ~Model();
    std::vector<Word> getQuestions();
};