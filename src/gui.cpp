#include "../includes/gui.h"
#include <menu.h>
#include "gui.h"
#include "board.h"

using namespace std;

Gui::Gui(){
    printw("** gui is now initialized **");
    this->menu = new Menu();
    this->board = new Board( 0, 0, 30, 30);
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

void Gui::drawBoard(){
   this->rectangle();
}

void Gui::rectangle() {
    mvaddch(this->board->startPoint.second, this->board->startPoint.first, ACS_ULCORNER);
    mvaddch(this->board->endPoint.second, this->board->startPoint.first, ACS_LLCORNER);
    mvaddch(this->board->startPoint.second, this->board->endPoint.first, ACS_URCORNER);
    mvaddch(this->board->endPoint.second, this->board->endPoint.first, ACS_LRCORNER);
    this->drawVerticalLines();
    this->drawHorizonatalLines();
}

void Gui::drawVerticalLines(){

}

void Gui::drawHorizonatalLines(){

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