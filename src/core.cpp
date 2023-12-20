#include "../includes/core.h"
#include "../includes/gui.h"
#include <map>
#include <functional>
#include <fstream>
#include <iostream>
#include <random>
#define QUESTION_COUNT 10
Core::Core(int verCount, int horCount) {
    this->model = new Model();

    this->longestSize = 0;
    this->longestIndex = 0;

    // board initialization u
    for (size_t i = 0; i <= verCount / 2; ++i) {
        vector<char> row;       
        for (size_t j = 0; j <= horCount / 4; ++j) {
            row.push_back(' ');
        }
        this->table.push_back(row);
        this->showTable.push_back(row);
    }

    this->fillWords();
    this->fillTable();
    this->user_interface = new Gui( verCount, horCount );
}

int Core::startGame(){
    this->user_interface->adjustScreenSize();
    int key = 0;
    do {
        key = user_interface->detectConrtolKeys();  
        if (key == KEY_UP) {
            // For changing a pointer selection to one level up
            this->user_interface->changeItem(0);
        } else if (key == KEY_DOWN) {
            // For changing a pointer selection to one level down
            this->user_interface->changeItem(1);
        } else if ( key == 10 ){
            if (*this->user_interface->menu->currentItem == "start"){
                this->menuStartCase();
            }
            else if (*this->user_interface->menu->currentItem == "how control")
            {
                this->chngeMenuState({"mouse", "keyboard"});
            }
            else if (*this->user_interface->menu->currentItem == "color")
            {
                this->chngeMenuState({"console", "window"});
            }
            else if (*this->user_interface->menu->currentItem == "exit")
            {
                endwin();
                return FALSE;
            }
            else if ( *this->user_interface->menu->currentItem == "console" || 
                        *this->user_interface->menu->currentItem == "window" )
            {
                this->user_interface->menu->colorOption = *this->user_interface->menu->currentItem;
                this->chngeMenuState({"black", "red", "blue", "cyan", "green", "magenta"});
            }
            else if ( *this->user_interface->menu->currentItem == "mouse" || 
                        *this->user_interface->menu->currentItem == "keyboard" ) {
                this->controlType = *this->user_interface->menu->currentItem;
                this->chngeMenuState();
            } else {
                this->setColor();
            }
        } else if (key == KEY_LEFT && this->user_interface->menu->prevActiveItems.size() > 1){
            this->chngeMenuState();
        }
        this->user_interface->clearWindow(this->user_interface->menu->mainWindow);
        this->user_interface->drawMenu(this->user_interface->menu->height, this->user_interface->menu->width);
    } while (key != 'q');
    refresh();
    endwin();
}

void Core::chngeMenuState(const std::vector<std::string> options)
{
    this->user_interface->menu->prevActiveItems.push_back(options);
    this->user_interface->menu->activeItems = this->user_interface->menu->prevActiveItems.back();
    this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
}

void Core::chngeMenuState()
{
    this->user_interface->menu->prevActiveItems.pop_back();
    this->user_interface->menu->activeItems = this->user_interface->menu->prevActiveItems.back();
    this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
}

void Core::getCords(std::pair<int, int> &cords) {
    // TODO make same thing without useing if else(by controlType obj {should be created})
    if(this->controlType == "keyboard")
    {
        cords = this->user_interface->getKeyCords();
    } else if (this->controlType == "mouse") {
        cords = this->user_interface->getMouseCords();
    }
}

void Core::setColor(){
    if ( *this->user_interface->menu->currentItem == "black") {
        if(this->user_interface->menu->colorOption == "console"){
            this->user_interface->changeConsoleColor(1);
        }
        else if(this->user_interface->menu->colorOption == "window"){
            this->user_interface->changeWindowColor(1);
        }
    }
    else if ( *this->user_interface->menu->currentItem == "red") {
        if(this->user_interface->menu->colorOption == "console"){
            this->user_interface->changeConsoleColor(2);
        }
        else if(this->user_interface->menu->colorOption == "window"){
            this->user_interface->changeWindowColor(2);
        }
    }
    else if ( *this->user_interface->menu->currentItem == "blue") {
        if(this->user_interface->menu->colorOption == "console"){
            this->user_interface->changeConsoleColor(3);
        }
        else if(this->user_interface->menu->colorOption == "window"){
            this->user_interface->changeWindowColor(3);
        }
    }
    else if ( *this->user_interface->menu->currentItem == "cyan") {
        if(this->user_interface->menu->colorOption == "console"){
            this->user_interface->changeConsoleColor(6);
        }
        else if(this->user_interface->menu->colorOption == "window"){
            this->user_interface->changeWindowColor(6);
        }
    }
    else if ( *this->user_interface->menu->currentItem == "magenta") {
        if(this->user_interface->menu->colorOption == "console"){
            this->user_interface->changeConsoleColor(5);
        }
        else if(this->user_interface->menu->colorOption == "window"){
            this->user_interface->changeWindowColor(5);
        }
    }
    else if ( *this->user_interface->menu->currentItem == "green") {
        if(this->user_interface->menu->colorOption == "console"){
            this->user_interface->changeConsoleColor(4);
        }
        else if(this->user_interface->menu->colorOption == "window"){
            this->user_interface->changeWindowColor(4);
        }
    }
}

void Core::fillWords(){
    this->words = this->model->getQuestions();
    for(int i = 0; i < words.size(); ++i){
        if( words[i].length > longestSize ){
            this->longestIndex = i;
            this->longestSize = words[i].length;
        }
    }
};

void Core::fillTable(){
    words[longestIndex].xCord = 0;
    words[longestIndex].yCord = 5;
    words[longestIndex].direction = "right";

    for(int i = 0; i < words[longestIndex].answer.length(); ++i){
        int k = table.size();
        int m = table[5].size();
        table[words[longestIndex].yCord][words[longestIndex].xCord + i] = words[longestIndex].answer[i];
        showTable[words[longestIndex].yCord][words[longestIndex].xCord + i] = words[longestIndex].answer[i];
    }
    this->usedWordsIndexes.push_back(longestIndex);

    int randomIndex = randomStrIndex(words[longestIndex].answer, words[longestIndex].usedLetterIndexed);
    while (usedWordsIndexes.size() < QUESTION_COUNT)
    {
        randomIndex = randomStrIndex(words[longestIndex].answer, words[longestIndex].usedLetterIndexed);
        fillVertical(randomIndex, words[longestIndex].yCord, words[longestIndex].answer[randomIndex]);
    }
}

void Core::fillVertical(int horIndex, int verIndex, char &letter){
    int choosedIndex = 0;
    for (int i = 0; i < words.size(); i++){
        int findedIndex = 0;
        if (
            words[i].answer.find(letter) != std::string::npos &&
            ! containsElement(usedWordsIndexes, i)
        ){
            findedIndex = words[i].answer.find(letter);
            words[i].usedLetterIndexed.push_back(findedIndex);
            if (verticalSuitable(findedIndex, horIndex, verIndex, words[i].answer)) {
                for (int j = 0; j < words[i].length; j++) {
                    table[verIndex - findedIndex + j][horIndex] = words[i].answer[j];
                }
                words[i].yCord = verIndex - findedIndex;
                words[i].xCord = horIndex;
                words[i].direction = "down";
                usedWordsIndexes.push_back(i);
                
                int randomVerIndex = randomStrIndex(words[i].answer , words[i].usedLetterIndexed);
                if (usedWordsIndexes.size() < QUESTION_COUNT)
                {
                    fillHorizontal(horIndex, randomVerIndex + (verIndex - findedIndex), words[i].answer[randomVerIndex]);
                }   
            }         
        }
    }
};

void Core::fillHorizontal(int horIndex, int verIndex, char &letter) {
    for (int i = 0; i < words.size(); i++) {
        int findedIndex = 0;
        if (
            words[i].answer.find(letter) != std::string::npos && 
            ! containsElement(usedWordsIndexes, i)
        ) {
            findedIndex = words[i].answer.find(letter);
            words[i].usedLetterIndexed.push_back(findedIndex);
            if (horizontalSuitable(findedIndex, horIndex, verIndex, words[i].answer)) {
                for (int j = 0; j < words[i].length; j++) {
                    table[verIndex][horIndex - findedIndex + j] = words[i].answer[j];
                }
                words[i].yCord = verIndex;
                words[i].xCord = horIndex - findedIndex;
                words[i].direction = "right";
                usedWordsIndexes.push_back(i);

                int randomHorIndex = randomStrIndex(words[i].answer , words[i].usedLetterIndexed);
                if (usedWordsIndexes.size() < QUESTION_COUNT)
                {
                    fillVertical(randomHorIndex + (horIndex - findedIndex), verIndex, words[i].answer[randomHorIndex]); 
                }
            }
        }
    }
};

bool Core::verticalSuitable(int findedInd, int horInd, int verInd, std::string &word) {
    if (
        verInd > findedInd && 
        verInd - findedInd + word.size() <= 25/2
    ) { // 25 / 2 is seted in the main
        int j = 0; 
        //! Problem are here
        for (int i = verInd - findedInd; i < (verInd - findedInd + word.size()); i++) {
            if (table[i][horInd] != ' ' && table[i][horInd] != word[j]) {
                return false;
            }     
            j++;       
        }
        return true;   
    }
    return false;
}

bool Core::horizontalSuitable(int findedInd, int horInd, int verInd, std::string &word) {
    if(
        horInd > findedInd && 
        horInd - findedInd + word.size() <= 125/4
    ) { // ! 125 / 4 is seted in the main (change in the future) 
        int j = 0; 
        for (int i = horInd - findedInd; i < (horInd - findedInd + word.size()); i++){
            if (table[verInd][i] != ' ' && table[verInd][i] != word[j]) {
                return false;
            }     
            j++;
        }
        return true;
    }
    return false;
}

bool Core::containsElement(std::vector<int> &vec, int &element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

int Core::randomStrIndex(std::string& string, std::vector<int>& existIndexes) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, string.size() - 1);

    int generatedNum = distrib(gen);
    if ( !containsElement(existIndexes, generatedNum) ){
        existIndexes.push_back(generatedNum);
        return (generatedNum);
    } else{ 
        return randomStrIndex(string, existIndexes);
    }
}

bool Core::compareTables(const std::vector<std::vector<char>>& table, const std::vector<std::vector<char>>& showTable) {
    bool flag = true;
    for (auto item : this->usedWordsIndexes)
    {
        if (this->words[item].direction == "right")
        {
            if (!this->chekcHorizontal(item))   
            {
                flag = false;
            }
        } else if (this->words[item].direction == "down")
        {
            if (!this->checkVertical(item))
            {
                flag = false;
            } 
        }
    }
    return flag;
}

bool Core::checkVertical(int index)
{
    for (size_t i = 0; i < words[index].length; i++)
    {
        if (this->showTable[words[index].yCord + i][words[index].xCord] != words[index].answer[i])
        {
            this->words[index].filled = false;
            return false;
        }
    }
    this->words[index].filled = true;
    return true;
}

bool Core::chekcHorizontal(int index)
{    
    for (size_t i = 0; i < words[index].length; i++)
    {
        if (showTable[words[index].yCord][words[index].xCord + i] != words[index].answer[i])
        {
            this->words[index].filled = false;
            return false;
        }
    }
    this->words[index].filled = true;
    return true;
}

void Core::menuStartCase()
{
    this->user_interface->drawBoadr(this->showTable);
    // this->user_interface->drawBoadr(this->table);
    do {
        std::pair<int, int> cords(0, 0);
        char letter;
        this->user_interface->drawQuestions(this->words, this->usedWordsIndexes);
        this->user_interface->drawInput();

        this->getCords(cords);
        this->user_interface->drawSelectedField(cords);

        do {
            letter = wgetch(this->user_interface->gameBoard->inputWindow);
        } while ((letter < 'a' || letter > 'z') && letter != ' ');

        this->showTable[cords.first][cords.second] = letter;
        if (this->showTable[cords.first][cords.second] == this->table[cords.first][cords.second]){
            this->user_interface->drawChangedBoard(this->showTable, cords, true);
        }else {
            this->user_interface->drawChangedBoard(this->showTable, cords, false);
        }
        this->user_interface->clearWindow(this->user_interface->menu->mainWindow);
        wrefresh(this->user_interface->gameBoard->mainWindow);
    } while (!this->compareTables(this->table, this->showTable));
    // } while (this->compareTables(this->table, this->showTable));

    int k;
    do {
        k = getch();
        this->user_interface->drawWinWindow();
    } while (k != 'q');
    clear();
    this->user_interface->menu->prevActiveItems.clear();
    this->chngeMenuState({"play again", "exit"});
}
