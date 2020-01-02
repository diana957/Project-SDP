#ifndef _HEADER_MENU_INCLUDED_
#define _HEADER_MENU_INCLUDED_

#include "Company.h"

class Menu {
public:
	Menu();

public:
	void readFromFile(const string& path);
	void menu();

private:
	void displayCommands()const;
	const Employee createEmployee()const;

private:
	Company company;
};

#endif
