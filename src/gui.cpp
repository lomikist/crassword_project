#include "../includes/gui.h"
#include <map>
#include <functional>

using namespace std;

int Gui::windowHeight;
int Gui::windowWidth;

Gui::Gui(int verCount, int horCount){
    this->initScreen(); 
    this->adjustScreenSize();

    // (height, width)
    this->initMenu(20, 30);
    // (width, height)
    this->initGameBoard(verCount, horCount);
}

Gui::~Gui(){
}

void Gui::adjustScreenSize(){
    getmaxyx(stdscr, Gui::windowHeight, Gui::windowWidth);
}

void Gui::drawMenu(int height, int width){
    box(this->menu->mainWindow, 0, 0);

    for (int i = 0; i < this->menu->activeItems.size(); ++i) {
        if ( &this->menu->activeItems[i] == this->menu->currentItem ) {
            mvwprintw(this->menu->mainWindow, (i + 0.5) * height / this->menu->activeItems.size(), 2, "----->");
            mvwprintw(this->menu->mainWindow, (i + 0.5) * height / this->menu->activeItems.size(), 9, "%s", this->menu->currentItem->c_str() );
        } else {
            mvwprintw(this->menu->mainWindow, (i + 0.5) * height / this->menu->activeItems.size(), 2, "%s", this->menu->activeItems[i].c_str());
        }
    }

    wrefresh(this->menu->mainWindow);
}

void Gui::drawInput(){

    wrefresh(this->gameBoard->inputWindow);
}

void Gui::changeItem(int key){
    // for down
    if ( key == 1 && this->menu->currentItem != &this->menu->activeItems[this->menu->activeItems.size() - 1] ) {
        this->menu->currentItem = this->menu->currentItem + 1;
    } else if (key == 0 && this->menu->currentItem != &this->menu->activeItems[0]) {
        // for up
        this->menu->currentItem = this->menu->currentItem - 1;
    }
}

void Gui::drawBoadr(std::vector<std::vector<char>> & table){
    box(this->gameBoard->mainWindow, 0, 0);

    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            // wattron(this->gameBoard->mainWindow, COLOR_PAIR(7));
            mvwaddch(this->gameBoard->mainWindow, 1 + i * 2, 2 + j * 4, table[i][j]);
            // wattroff(this->gameBoard->mainWindow, COLOR_PAIR(7));
            // wattron(this->gameBoard->mainWindow, COLOR_PAIR(1));
        }
    }   

    this->drawHorizontalLines();
    this->drawVerticalLines();

    wrefresh(this->gameBoard->mainWindow);
}

void Gui::drawChangedBoard(std::vector<std::vector<char>> & table, std::pair<int,int> &cords, bool flag) {
    if (flag)
        wattron(this->gameBoard->mainWindow, COLOR_PAIR(8));
    else 
        wattron(this->gameBoard->mainWindow, COLOR_PAIR(7));

    mvwaddch(this->gameBoard->mainWindow, 1 + cords.first * 2, 2 + cords.second * 4, table[cords.first][cords.second]);

    if (flag)
        wattroff(this->gameBoard->mainWindow, COLOR_PAIR(8));
    else 
        wattroff(this->gameBoard->mainWindow, COLOR_PAIR(7));}

void Gui::drawQuestions(const std::vector<Word> & list, const std::vector<int>  &indexes) { 
    box(this->gameBoard->questWindow, '*', '*');
    
    int showIndex = 0;
    for(int i = 0; i < indexes.size(); ++i){
        mvwprintw(this->gameBoard->questWindow, 1 + i, 1,
                                                "%d) %s - [start (%d,%d)] [end (%d,%d)]",
                                                i + 1,
                                                list[indexes[i]].question.c_str(),
                                                list[indexes[i]].xCord,
                                                list[indexes[i]].yCord,
                                                list[indexes[i]].xCord + (list[indexes[i]].direction == "right" ? list[indexes[i]].length : 0),
                                                list[indexes[i]].yCord + (list[indexes[i]].direction == "down" ? list[indexes[i]].length : 0)
                );
    }
    wrefresh(this->gameBoard->questWindow);
}

void Gui::drawVerticalLines(){
    for(int i = 1; i < this->gameBoard->sizes.second / 4; ++i){
        // from +1 to -1 because this function for inner lines.
        mvwvline(this->gameBoard->mainWindow, 1, i * 4, 0, this->gameBoard->sizes.first - 2);
    }
}

void Gui::drawHorizontalLines(){
    for(int i = 1; i < this->gameBoard->sizes.first / 2; ++i){
        // last argument .second because for horizontal line we should print vertical coutn time. 
        mvwhline(this->gameBoard->mainWindow, i * 2, 1, 0, this->gameBoard->sizes.second - 2);
    }
}

int Gui::detectConrtolKeys(){    
    int key = getch();
    if ( key == KEY_UP 
        || key == KEY_DOWN 
        || key == KEY_LEFT 
        || key == KEY_RIGHT
        || key == 10
        || key == 'q'
        ) {
        return key;
    }
    return 0;
}

int Gui::getDecimalNumber(const std::string &turn){
    int input = 0;
    int number = 0;

    this->clearWindow(this->gameBoard->inputWindow);
    box(this->gameBoard->inputWindow, 0, 0);
    do {
        input = getch();
        // take a input from user and convert it to number the case if assci code between 9 and 1.
        int j = 0;
        if (input <= '9' && input >= '1') {
            number = number * 10 + input - '0';
            if (turn == "y")
                mvwprintw(this->gameBoard->inputWindow, 1, 1, "y - %d", number);
            else if (turn == "x")
                mvwprintw(this->gameBoard->inputWindow, 1, 1, "x - %d", number);
            j++;
        }
        wrefresh(this->gameBoard->inputWindow);
    } while (input != 10);
    this->clearWindow(this->gameBoard->inputWindow);
    this->verHorTurn = !this->verHorTurn;
    return number == 0 ? 1 : number;
}

void Gui::initMenu(int height, int width)
{
    std::vector<string> menuOptions = {"start", "how control", "color","exit"};
    int y = (Gui::windowHeight - height) / 2;
    int x = (Gui::windowWidth - width) / 2;

    this->menu = new Menu(menuOptions);
    this->menu->height = height;
    this->menu->width = width;
    this->menu->mainWindow = newwin(this->menu->height, this->menu->width, y, x);
}

void Gui::initGameBoard(int verCount, int horCount)
{
    this->gameBoard = new Board(verCount, horCount);
    int y = 1;
    int x = (Gui::windowWidth - this->gameBoard->sizes.second);
    this->gameBoard->mainWindow = newwin(this->gameBoard->sizes.first , this->gameBoard->sizes.second, y, x);
    this->gameBoard->questWindow = newwin(Gui::windowHeight - this->gameBoard->sizes.first - y, this->gameBoard->sizes.second, this->gameBoard->sizes.first + y, x);
    this->gameBoard->inputWindow = newwin(this->gameBoard->sizes.first, x, 1, 0);
}   

void Gui::clearScreen(){
    clear();
}

void Gui::clearWindow(WINDOW *win){
    wclear(win);
}

void Gui::initScreen() {    
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, true);
    if (!has_colors()) {
        endwin();
        printf("Bratan your teminal dose not support colors.\n");
        abort();
    }

    // pait for color
    init_pair(1, COLOR_WHITE, COLOR_BLACK); 
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
}

void Gui::changeConsoleColor(const int pairIndex) {
    bkgd(COLOR_PAIR(pairIndex));
}

void Gui::changeWindowColor(const int pairIndex) {
    wbkgd(this->menu->mainWindow, COLOR_PAIR(pairIndex));
    wbkgd(this->gameBoard->mainWindow, COLOR_PAIR(pairIndex));
    wbkgd(this->gameBoard->questWindow, COLOR_PAIR(pairIndex));
}

void Gui::printErrors(const std::string &error) {
    mvwprintw(this->gameBoard->inputWindow, 1, 1, error.c_str());
}
