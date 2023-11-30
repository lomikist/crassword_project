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

    // board initialization 
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

    initscr();
    keypad(stdscr, true);

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
            if ( *this->user_interface->startMenu->startMenuActiveItem == "start"){
                int entered;
                user_interface->clearScreen();
                do {
                    // start board drawing part.
                    int a, b;
                    this->user_interface->startDrawBoadr( this->table );
                    a = this->user_interface->getDecimalNumber();
                    b = this->user_interface->getDecimalNumber();

                    this->table[a - 1][b - 1] = 'd';
                    refresh();
                } while ( entered != 'q');                
            }    
        } 
        this->user_interface->drawStartMenu(19,30);
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

    usedWordsIndexes.push_back(3);
};

void Core::fillTable(){
    std::cout << words[longestIndex].question << " question\n";
    std::cout << words[longestIndex].answer << " answear\n";

    words[longestIndex].xCord = 0;
    words[longestIndex].yCord = 2;

    std::cout << words[longestIndex].xCord << " x\n";
    std::cout << words[longestIndex].yCord << " y\n";
    
    for(int i = 0; i < words[longestIndex].answer.length(); ++i){
        int k = table.size();
        int m = table[5].size();
        table[5][i] = words[longestIndex].answer[i];
    }
    
    int randomIndex = randomStrIndex(words[longestIndex].answer, words[longestIndex].usedLetterIndexed);

    fillVertical(randomIndex, 5, &words[longestIndex].answer[randomIndex]);
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
            if (horizontalSuitable(findedIndex, verIndex, &words[i].answer)) {
                for (int j = 0; j < words[i].length; j++) {
                    table[verIndex + 1][horIndex - findedIndex + j] = words[i].answer[j];
                }
                // ! continu from here 
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
    if ( !containsElement(existIndexes, generatedNum) == true){
        existIndexes.push_back(generatedNum);
        return (generatedNum);
    } else{ 
        return randomStrIndex(string, existIndexes);
    }
}