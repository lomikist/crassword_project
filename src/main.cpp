
#include "../includes/main.h"

int main(int argc, char *argv[]){
	Menu* start_menu = new Menu("start menue");
	Gui* user_interface = new Gui();
	user_interface->start_Drawing();
	return 0;
}