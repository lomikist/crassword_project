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
                this->user_interface->menu->prevActiveItems.push_back({"console", "window"});
                this->user_interface->menu->activeItems = this->user_interface->menu->prevActiveItems.back();
                this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
            }
            else if ( *this->user_interface->menu->currentItem == "exit" )
            {
                endwin();
                abort();
            } else if ( *this->user_interface->menu->currentItem == "console" || 
                        *this->user_interface->menu->currentItem == "window" ) {
                this->user_interface->menu->colorOption = *this->user_interface->menu->currentItem;
                this->user_interface->menu->prevActiveItems.push_back({"black", "red", "blue", "cyan", "green", "magenta"});
                this->user_interface->menu->activeItems = this->user_interface->menu->prevActiveItems.back();
                this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
            } else {
                this->setColor();
            }
        } else if (key == KEY_LEFT && this->user_interface->menu->prevActiveItems.size() > 1){
            this->user_interface->menu->prevActiveItems.pop_back();
            this->user_interface->menu->activeItems = this->user_interface->menu->prevActiveItems.back();
            this->user_interface->menu->currentItem = &this->user_interface->menu->activeItems[0];
        }
        this->user_interface->clearWindow(this->user_interface->menu->mainWindow);
        this->user_interface->drawMenu(this->user_interface->menu->height, this->user_interface->menu->width);
    } while (key != 'q');
    refresh();
    endwin();
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

    for(int i = 0; i < words[longestIndex].answer.length(); ++i){
        int k = table.size();
        int m = table[5].size();
        table[words[longestIndex].yCord][words[longestIndex].xCord + i] = words[longestIndex].answer[i];
    }
    
    int randomIndex = randomStrIndex(words[longestIndex].answer, words[longestIndex].usedLetterIndexed);

    fillVertical(randomIndex, words[longestIndex].yCord, &words[longestIndex].answer[randomIndex]);
}

void Core::fillVertical(int horIndex, int verIndex, char *letter){
    int choosedIndex = 0;
    //TODO in the future change to randome selection.
    for (int i = 0; i < words.size(); i++){
        int findedIndex = 0;
        if (
            words[i].answer.find(*letter) != std::string::npos &&
            ! containsElement(usedWordsIndexes, i)
        ){
            findedIndex = words[i].answer.find(*letter);
            words[i].usedLetterIndexed.push_back(findedIndex);
            // std::cout << "finded_index -- " << findedIndex << "\n";
            // std::cout << "vertical_index -- " << verIndex << "\n";
            // std::cout << "answer -- " << words[i].answer << "\n";
            if (verticalSuitable(findedIndex, horIndex, verIndex, words[i].answer)) {
                for (int j = 0; j < words[i].length; j++)
                {
                    table[verIndex - findedIndex + j][horIndex] = words[i].answer[j];
                }
                usedWordsIndexes.push_back(i);
                int randomVerIndex = randomStrIndex(words[i].answer , words[i].usedLetterIndexed);
                // std::cout << "random Index" << randomVerIndex << "---\n";
                // std::cout << "horizontal Index" << horIndex << "---\n";
                // std::cout << "word - " << words[i].answer << "---\n";
                // std::cout << "letter - " << words[i].answer[randomVerIndex] << "---\n";
                // std::cout << "~~~~~~~~~~~~~~~~~~\n";
                fillHorizontal(horIndex, randomVerIndex + (verIndex - findedIndex), &words[i].answer[randomVerIndex]);
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
            words[i].usedLetterIndexed.push_back(findedIndex);
            
            std::cout << "finded_index -- " << findedIndex << "\n";
            std::cout << "vertical_index -- " << verIndex << "\n";
            std::cout << "answer -- " << words[i].answer << "\n";
            
            std::cout << "fill horizontal\n";
            if (horizontalSuitable(findedIndex, horIndex, verIndex, words[i].answer)) {
                for (int j = 0; j < words[i].length; j++) {
                    table[verIndex][horIndex - findedIndex + j] = words[i].answer[j];
                }
                usedWordsIndexes.push_back(i);
                int randomHorIndex = randomStrIndex(words[i].answer , words[i].usedLetterIndexed);
                std::cout << "random Index" << randomHorIndex << "---\n";
                std::cout << "horizontal Index" << horIndex << "---\n";
                std::cout << "word - " << words[i].answer << "---\n";
                std::cout << "letter - " << words[i].answer[randomHorIndex] << "---\n";
                fillVertical(randomHorIndex + (horIndex - findedIndex)  , verIndex, &words[i].answer[randomHorIndex]); 
            }
        }
    }
};

bool Core::verticalSuitable(int findedInd, int horInd, int verInd, std::string &word) {
    // TODO check word crossing 
    if (
        verInd > findedInd && 
        verInd - findedInd + word.size() <= 25/2
    ) { // 25 / 2 is seted in the main
        int j = 0; 
        for (int i = verInd - findedInd; i < (verInd + word.size()); i++){
            std::cout << "word is " << word << "\n";
            std::cout << "table letter --" << table[i][horInd] << "    word letter --- " << word[j] << "\n";
            if (table[i][horInd] != ' ' && table[i][horInd] != word[j]) {
                return false;
            }     
            j++;       
        }
        std::cout << "verticll this word is suitable" <<  word << "\n !=================!\n";
        return true;   
    }
    return false;
}

bool Core::horizontalSuitable(int findedInd, int horInd, int verInd, std::string &word) {
    // TODO check word crossing 
    if(
        horInd > findedInd && 
        horInd - findedInd + word.size() <= 125/4
    ) { // ! 125 / 4 is seted in the main (change in the future) 
        int j = 0; 
        for (int i = horInd - findedInd; i < (horInd + word.size()); i++){
            std::cout << "==========horizontal============";
            std::cout << "word is " << word << "\n";
            std::cout << "table letter --" << table[verInd][i] << "    word letter --- " << word[j] << "\n";
            if (table[verInd][i] != ' ' && table[verInd][i] != word[j]) {
                return false;
            }     
            j++;
        }
        return true;
        std::cout << "this word is suitable horizontally  " <<  word << "\n";
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