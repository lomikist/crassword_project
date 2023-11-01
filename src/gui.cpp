#include "../includes/gui.h"
#include <menu.h>
#include "gui.h"
#include "board.h"

using namespace std;

Gui::Gui(){
    this->menu = new Menu();

    this->board = new Board( 0, 0, 30,66);
}

Gui::~Gui(){
}

void Gui::drawMenu(){
    Menu* item = this->menu;
    for(int i = 0; i < item->items.size(); i++ ){
        if( &item->items[i] == item->active_item ){
            printw("---->");
            printw (item->items[i].c_str());
            printw ( "\n" );
        }else { 
            printw ( item->items[i].c_str());
            printw ( "\n" );
        }
    }
}
/**
 * function for drawing a board
*/
void Gui::drawBoard(){
    this->drawVerticalLines();
    this->drawHorizontalLines();
    this->drawBoarders();
}

/**
 * function to draw vertical lines
*/
void Gui::drawVerticalLines(){
    for(int i = 1; i < this->board->lineCount.second; i++){
        // from +1 to -1 because this function for inner lines.
        mvvline(this->board->startPoint.second + 1, this->board->startPoint.first + 2 * i, 0, this->board->endPoint.second - 1);
    }
}

/**
 * function to draw horizontal lines
*/
void Gui::drawHorizontalLines(){
    for(int i = 1; i < this->board->lineCount.first; i++){
        // last argument .second because for horizontal line we should print vertical coutn time. 
        mvhline(this->board->startPoint.second + 2 * i, this->board->startPoint.first + 1, 0, this->board->endPoint.first - 1);
    }
}

/**
 * function to draw boarders
*/
void Gui::drawBoarders(){
    // for vertical boarder
    mvvline(this->board->startPoint.second, this->board->startPoint.first, 0, this->board->endPoint.second);
    mvvline(this->board->startPoint.second, this->board->endPoint.first, 0, this->board->endPoint.second);
    
    // for horizontal boarder
    mvhline(this->board->startPoint.second, this->board->startPoint.first, 0, this->board->endPoint.first);
    mvhline(this->board->endPoint.second, this->board->startPoint.first, 0, this->board->endPoint.first);

    // for corner symbols
    mvaddch(this->board->startPoint.second, this->board->startPoint.first, ACS_ULCORNER);
    mvaddch(this->board->endPoint.second, this->board->startPoint.first, ACS_LLCORNER);
    mvaddch(this->board->startPoint.second, this->board->endPoint.first, ACS_URCORNER);
    mvaddch(this->board->endPoint.second, this->board->endPoint.first, ACS_LRCORNER);
}

void Gui::changeItem(int key){
    // for down
    if ( key == 1 && this->menu->active_item != &menu->items[menu->items.size() - 1] ) {
        this->menu->active_item = this->menu->active_item + 1;
    }
    // for up
    else if (key == 0 && this->menu->active_item != &menu->items[0])
    {
        this->menu->active_item = this->menu->active_item - 1;
    }
}