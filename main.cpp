#include <iostream>
#include "Menu.h"

using std::cout;
using std::cerr;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cerr << "Not enough arguments\n";
		return -1;
	}

	Menu menu;
	menu.readFromFile(argv[1]);
	menu.menu();	
	
	return 0;
}
