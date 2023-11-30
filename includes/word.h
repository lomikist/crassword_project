#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

class Word {
private:
    
public:
    Word();
    ~Word();

    int qIndex;
    int xCord;
    int yCord;
    int length;
    std::string answer;
    std::string question;
    std::string direction;//! not neded for now
    std::vector<int> usedLetterIndexed;
public:
    bool checkAnswer(const std::string& aswer);
};