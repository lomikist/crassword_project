#include "../includes/gui.h"
#include <menu.h>
#include "gui.h"
#include "board.h"

using namespace std;

Gui::Gui(){
    cout << "** gui is now initialized **" << endl;
}

Gui::~Gui(){
}

void Gui::drawMenu(Menu* item){
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

void Gui::drawBoard(Board* item){
   this->rectangle(0,0,20,50);
}

void Gui::rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}