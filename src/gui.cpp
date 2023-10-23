#include "../includes/gui.h"
#include <menu.h>

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
};