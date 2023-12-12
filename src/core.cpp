#include "../includes/core.h"
#include "../includes/gui.h"
#include <map>
#include <functional>
#include <fstream>
#include <iostream>
#include <random>

Core::Core(int verCount, int horCount) {
    // this->model = new Model();

    this->longestSize = 0;
    this->longestIndex = 0;

    // board initialization u
    for (size_t i = 0; i <= verCount / 2; ++i) {
        vector<char> row;       
        for (size_t j = 0; j <= horCount / 4; ++j) {
            row.push_back(' ');
        }
        this->table.push_back(row);
    }

    this->fillWords();
    this->fillTable();
    this->user_interface = new Gui( verCount, horCount );
}

Core::~Core()
{
}

void Core::startGame(){
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
            if ( *this->user_interface->menu->currentItem == "start"){
                int entered;
                this->user_interface->clearScreen();
                do {
                    int a, b;
                    this->user_interface->drawBoadr(this->table);
                    this->user_interface->drawQuestions(this->words, this->usedWordsIndexes);

                    a = this->user_interface->getDecimalNumber();
                    b = this->user_interface->getDecimalNumber();

                    this->table[a - 1][b - 1] = 'd';
                    this->user_interface->clearWindow(this->user_interface->menu->mainWindow);
                    
                    wrefresh(this->user_interface->gameBoard->mainWindow);
                } while ( entered != 'q');              
            }
            else if ( *this->user_interface->menu->currentItem == "how control" )
            {
                
            }
            else if ( *this->user_interface->menu->currentItem == "color" )
            {
                this->user_interface->menu->prevActiveItems = this->user_interface->menu->activeItems;
                this->user_interface->menu->activeItems = {"console", "window"};
                this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
            }
            else if ( *this->user_interface->menu->currentItem == "exit" )
            {
                endwin();
                abort();
            } else if ( *this->user_interface->menu->currentItem == "console" || 
                        *this->user_interface->menu->currentItem == "window" ) {
                this->user_interface->menu->colorOption = *this->user_interface->menu->currentItem;
                this->user_interface->menu->prevActiveItems = {"start", "color", "exit", "how control"};
                this->user_interface->menu->activeItems = {"black", "red", "blue", "cyan", "green", "magenta"};
                this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
            } else {
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
        } else if (key == KEY_LEFT){
            this->user_interface->menu->activeItems = this->user_interface->menu->prevActiveItems;
            this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
        }
        this->user_interface->clearWindow(this->user_interface->menu->mainWindow);
        this->user_interface->drawMenu(this->user_interface->menu->height, this->user_interface->menu->width);
    } while (key != 'q');
    refresh();
    endwin();
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

    for(int i = 0; i < words[longestIndex].answer.length(); ++i){
        int k = table.size();
        int m = table[2].size();
        table[words[longestIndex].yCord][words[longestIndex].xCord + i] = words[longestIndex].answer[i];
    }
    
    int randomIndex = randomStrIndex(words[longestIndex].answer, words[longestIndex].usedLetterIndexed);

    fillVertical(randomIndex, words[longestIndex].yCord, &words[longestIndex].answer[randomIndex]);
}

void Core::fillVertical(int horIndex, int verIndex, char *letter){
    int choosedIndex = 0;
    // std::cout << *letter << "   searched letter\n";
    for (int i = 0; i < words.size(); i++){
        int findedIndex = 0;
        if (
                words[i].answer.find(*letter) != std::string::npos &&
                ! containsElement(usedWordsIndexes, i)
            ){
            findedIndex = words[i].answer.find(*letter);
            words[i].usedLetterIndexed.push_back(i);
            if (verticalSuitable(findedIndex, verIndex, &words[i].answer)) {
                for (int j = 0; j < words[i].length; j++)
                {
                    table[verIndex - findedIndex + j][horIndex] = words[i].answer[j];
                }
                usedWordsIndexes.push_back(i);
                int randomVerIndex = randomStrIndex(words[i].answer , words[i].usedLetterIndexed);
                
                // std::cout << "random Index" << randomI << "---\n";
                // std::cout << "horizontal Index" << horIndex << "---\n";
                // std::cout << "letter" << words[i].answer << "---\n";
                // std::cout << "letter" << words[i].answer[randomI] << "---\n";
                // ! from here
                fillHorizontal(horIndex, randomVerIndex, &words[i].answer[randomVerIndex]);
                break;
            }
            
        }
    }
};

void Core::fillHorizontal(int horIndex, int verIndex, char *letter) {
    for (int i = 0; i < words.size(); i++) {
        int findedIndex = 0;
        if (
            words[i].answer.find(*letter) != std::string::npos && 
            ! containsElement(usedWordsIndexes, i)
        ) {
            findedIndex = words[i].answer.find(*letter);

            words[i].usedLetterIndexed.push_back(i);
            if (horizontalSuitable(findedIndex, verIndex, &words[i].answer)) {
                for (int j = 0; j < words[i].length; j++) {
                    table[verIndex + 1][horIndex - findedIndex + j] = words[i].answer[j];
                }
                //! should make word crossing part, and check what is worng.`
                usedWordsIndexes.push_back(i);
                int randomHorIndex = randomStrIndex(words[i].answer , words[i].usedLetterIndexed);
                
                fillVertical(randomHorIndex , verIndex + 1, &words[i].answer[randomHorIndex]); 
                break;
            }
        }
    }
};

bool Core::verticalSuitable(int findedInd, int verInd, std::string *word) {
    // TODO check word crossing 
    if (
        verInd > findedInd && 
        verInd - findedInd + word->size() <= 25/2
    ) { // 25 / 2 is seted in the main 
        return true;   
    }
    return false;
}

bool Core::horizontalSuitable(int findedInd, int horInd, std::string *word) {
    // TODO check word crossing 
    if(
        horInd > findedInd && 
        horInd - findedInd + word->size() <= 125/4
    ) { // ! 125 / 4 is seted in the main (change in the future) 
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