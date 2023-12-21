#include "../includes/core.h"
#include "../includes/gui.h"
#include <map>
#include <functional>
#include <fstream>
#include <iostream>
#include <random>

#define QUESTION_COUNT 2

Core::Core(int verCount, int horCount)
{
    this->model = new Model();

    this->longestSize = 0;
    this->longestIndex = 0;

    // board initialization u
    for (size_t i = 0; i <= verCount / 2; ++i)
    {
        vector<char> row;
        for (size_t j = 0; j <= horCount / 4; ++j)
        {
            row.push_back(' ');
        }
        this->table.push_back(row);
        this->showTable.push_back(row);
    }

    this->fillWords();
    this->fillTable();
    this->user_interface = new Gui(verCount, horCount);
}

int Core::startGame()
{
    this->user_interface->adjustScreenSize();
    int key = 0;
    this->user_interface->drawMenu(this->user_interface->menu->height, this->user_interface->menu->width);
    do {
        key = this->user_interface->detectConrtolKeys();
        switch (key) {
            case KEY_UP:
                this->user_interface->changeItem(0);
                break;
            case KEY_DOWN:
                this->user_interface->changeItem(1);
                break;
            case 10: //enter code
                this->menuActions();
                break;
            case KEY_LEFT:
                if (this->user_interface->menu->prevActiveItems.size() > 1) {
                    this->chngeMenuState();
                }
                break;
        }
        user_interface->clearWindow(user_interface->menu->mainWindow);
        user_interface->drawMenu(user_interface->menu->height, user_interface->menu->width);
    } while (key != 'q');
    refresh();
    endwin();
}

void Core::menuActions()
{
    if (*this->user_interface->menu->currentItem == "start")
    {
        menuStartCase();
    }
    else if (*this->user_interface->menu->currentItem == "how control")
    {
        chngeMenuState({"mouse", "keyboard"});
    }
    else if (*this->user_interface->menu->currentItem == "color")
    {
        chngeMenuState({"console", "window"});
    }
    else if (*this->user_interface->menu->currentItem == "exit")
    {
        endwin();
        exit(EXIT_SUCCESS);
    }
    else if (*this->user_interface->menu->currentItem == "play again")
    {
        this->user_interface->clearWindow(this->user_interface->gameBoard->mainWindow);
        this->clearShowTable();
        this->chngeMenuState({"start", "how control", "color","exit"});
        this->menuStartCase();
    }
    else if (*this->user_interface->menu->currentItem == "console" || *this->user_interface->menu->currentItem == "window")
    {
        this->user_interface->menu->colorOption = *this->user_interface->menu->currentItem;
        this->chngeMenuState({"black", "red", "blue", "cyan", "green", "magenta"});
    }
    else if (*this->user_interface->menu->currentItem == "mouse" || *this->user_interface->menu->currentItem == "keyboard")
    {
        this->controlType = *this->user_interface->menu->currentItem;
        this->chngeMenuState();
    }
    else
    {
        this->setColor();
    }
}

void Core::clearShowTable()
{
    for (size_t i = 0; i < showTable.size(); ++i)
    {
        for (size_t j = 0; j < showTable[0].size(); ++j)
        {
            showTable[i][j] = ' ';
        }
    }
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

void Core::getCords(std::pair<int, int> &cords)
{
    // TODO make same thing without useing if else(by controlType obj {should be created})
    if (this->controlType == "keyboard")
    {
        cords = this->user_interface->getKeyCords();
    }
    else if (this->controlType == "mouse")
    {
        cords = this->user_interface->getMouseCords();
    }
}

void Core::setColor()
{
    std::unordered_map<std::string, int> colorMap = {
        {"black", 1},
        {"red", 2},
        {"blue", 3},
        {"cyan", 6},
        {"magenta", 5},
        {"green", 4}};

    std::string colorOption = this->user_interface->menu->colorOption;

    auto foundColor = colorMap.find(*this->user_interface->menu->currentItem);
    if (foundColor != colorMap.end())
    {
        int colorValue = foundColor->second;

        if (colorOption == "console")
        {
            this->user_interface->changeConsoleColor(colorValue);
        }
        else if (colorOption == "window")
        {
            this->user_interface->changeWindowColor(colorValue);
        }
    }
}

void Core::fillWords()
{
    this->words = this->model->getQuestions();
    for (int i = 0; i < words.size(); ++i)
    {
        if (words[i].length > longestSize)
        {
            this->longestIndex = i;
            this->longestSize = words[i].length;
        }
    }
};

void Core::fillTable()
{
    words[longestIndex].xCord = 0;
    words[longestIndex].yCord = 5;
    words[longestIndex].direction = "right";

    for (int i = 0; i < words[longestIndex].answer.length(); ++i)
    {
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

void Core::fillVertical(int horIndex, int verIndex, char &letter)
{
    int choosedIndex = 0;
    for (int i = 0; i < words.size(); i++)
    {
        int findedIndex = 0;
        if (
            words[i].answer.find(letter) != std::string::npos &&
            !containsElement(usedWordsIndexes, i))
        {
            findedIndex = words[i].answer.find(letter);
            words[i].usedLetterIndexed.push_back(findedIndex);
            if (verticalSuitable(findedIndex, horIndex, verIndex, words[i].answer))
            {
                for (int j = 0; j < words[i].length; j++)
                {
                    table[verIndex - findedIndex + j][horIndex] = words[i].answer[j];
                }
                words[i].yCord = verIndex - findedIndex;
                words[i].xCord = horIndex;
                words[i].direction = "down";
                usedWordsIndexes.push_back(i);

                int randomVerIndex = randomStrIndex(words[i].answer, words[i].usedLetterIndexed);
                if (usedWordsIndexes.size() < QUESTION_COUNT)
                {
                    fillHorizontal(horIndex, randomVerIndex + (verIndex - findedIndex), words[i].answer[randomVerIndex]);
                }
            }
        }
    }
};

void Core::fillHorizontal(int horIndex, int verIndex, char &letter)
{
    for (int i = 0; i < words.size(); i++)
    {
        int findedIndex = 0;
        if (
            words[i].answer.find(letter) != std::string::npos &&
            !containsElement(usedWordsIndexes, i))
        {
            findedIndex = words[i].answer.find(letter);
            words[i].usedLetterIndexed.push_back(findedIndex);
            if (horizontalSuitable(findedIndex, horIndex, verIndex, words[i].answer))
            {
                for (int j = 0; j < words[i].length; j++)
                {
                    table[verIndex][horIndex - findedIndex + j] = words[i].answer[j];
                }
                words[i].yCord = verIndex;
                words[i].xCord = horIndex - findedIndex;
                words[i].direction = "right";
                usedWordsIndexes.push_back(i);

                int randomHorIndex = randomStrIndex(words[i].answer, words[i].usedLetterIndexed);
                if (usedWordsIndexes.size() < QUESTION_COUNT)
                {
                    fillVertical(randomHorIndex + (horIndex - findedIndex), verIndex, words[i].answer[randomHorIndex]);
                }
            }
        }
    }
};

bool Core::verticalSuitable(int findedInd, int horInd, int verInd, std::string &word)
{
    if (
        verInd > findedInd &&
        verInd - findedInd + word.size() <= 25 / 2)
    { //! 25 / 2 is seted in the main
        int j = 0;
        for (int i = verInd - findedInd; i < (verInd - findedInd + word.size()); i++)
        {
            if (table[i][horInd] != ' ' && table[i][horInd] != word[j])
            {
                return false;
            }
            j++;
        }
        return true;
    }
    return false;
}

bool Core::horizontalSuitable(int findedInd, int horInd, int verInd, std::string &word)
{
    if (
        horInd > findedInd &&
        horInd - findedInd + word.size() <= 125 / 4)
    { //! 125 / 4 is seted in the main (change in the future)
        int j = 0;
        for (int i = horInd - findedInd; i < (horInd - findedInd + word.size()); i++)
        {
            if (table[verInd][i] != ' ' && table[verInd][i] != word[j])
            {
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

int Core::randomStrIndex(std::string &string, std::vector<int> &existIndexes)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, string.size() - 1);

    int generatedNum = distrib(gen);
    
    if (!containsElement(existIndexes, generatedNum))
    {
        existIndexes.push_back(generatedNum);
        return (generatedNum);
    }
    else
    {
        return randomStrIndex(string, existIndexes); //!
    }
}

bool Core::compareTables(const std::vector<std::vector<char>> &table, const std::vector<std::vector<char>> &showTable)
{
    bool flag = true;
    for (auto item : this->usedWordsIndexes)
    {
        if (this->words[item].direction == "right")
        {
            if (!this->chekcHorizontal(item))
            {
                flag = false;
            }
        }
        else if (this->words[item].direction == "down")
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
    this->compareTables(this->table, this->showTable);
    do
    {
        std::pair<int, int> cords(0, 0);
        char letter;
        this->user_interface->drawQuestions(this->words, this->usedWordsIndexes);
        this->user_interface->drawInput();

        this->getCords(cords);
        this->user_interface->drawSelectedField(cords);
        letter = this->user_interface->getLetter();

        if (letter == 27)
        {
            startGame();
        }

        this->showTable[cords.first][cords.second] = letter;
        if (this->showTable[cords.first][cords.second] == this->table[cords.first][cords.second])
        {
            this->user_interface->drawChangedBoard(this->showTable, cords, true);
        }
        else
        {
            this->user_interface->drawChangedBoard(this->showTable, cords, false);
        }
        this->user_interface->clearWindow(this->user_interface->menu->mainWindow);
        wrefresh(this->user_interface->gameBoard->mainWindow);
    } while (!this->compareTables(this->table, this->showTable));

    int k;
    do
    {
        k = getch();
        this->user_interface->drawWinWindow();
    } while (k != 'q');
    // clear();
    this->user_interface->menu->prevActiveItems.clear();
    this->chngeMenuState({"play again", "exit"});
}
