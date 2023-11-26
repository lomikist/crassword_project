#pragma once
#include <iostream>
#include <string.h>
#include <fstream>

class Word {
private:
    
public:
    Word();
    ~Word();

    int qIndex;
    std::string direction;
    int xCord;
    int yCord;
    std::string question;
    std::string answer;
    int length;
public:
    bool checkAnswer(const std::string& aswer);
};