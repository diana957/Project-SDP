#include "Menu.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

Menu::Menu() : company(){}

void Menu::readFromFile(const string& path) {
	company.readFromFile(path);
}

void Menu::menu() {
	displayCommands();

	string command;
	getline(cin, command);

	while (command != "exit") {
		if (command == "add") {
			cout << "Add boss or unpractised: \n"
				<< "For boss - with, otherwise - without\n";
			string option;
			getline(cin, option);
			string boss;
			cout << "Enter the name of the boss: ";
			getline(cin, boss);
			company.add(createEmployee(), boss, option);
			cin.get();
		}
		if (command == "dismiss") {
			string employee;
			cout << "Enter the name of the employee that will be dismissed: ";
			getline(cin, employee);
			company.dissmiss(employee);
		}
		if (command == "raise") {
			string employee;
			cout << "Enter the name of the employee that will be raised: ";
			getline(cin, employee);
			company.newRank(employee);
		}
		if (command == "directSub") {
			string employee;
			cout << "Enter the name of the employee for showing their direct subordinates: ";
			getline(cin, employee);
			company.directSubordinates(employee);
		}
		if (command == "allSub") {
			string employee;
			cout << "Enter the name of the employee for showing their all subordinates: ";
			getline(cin, employee);
			company.allSubordinates(employee);
		}
		if (command == "boss") {
			string employee;
			cout << "Enter the name of the employee for showing their boss: ";
			getline(cin, employee);
			company.directBoss(employee);
		}

		displayCommands();
		getline(cin, command);
	}
	
}

void Menu::displayCommands()const {
	cout << "The above menu is for manupulating current company:\n"
		<< "1. Add another employee - add "
		<< "\n2. Dismiss an employee - dismiss "
		<< "\n3. Raise the position of an employee - raise "
		<< "\n4. See all the direct subordinates of one employee - directSub "
		<< "\n5. See all the subordinates of one employee - allSub "
		<< "\n6. See the boss of an employee - boss "
		<< "\n7. Exit from the program - exit\n";
}

const Employee Menu::createEmployee()const {
	string name;
	unsigned practice, age;

	cout << "Enter the information for the new Employee:\n"
		<< "1. name: ";
	getline(cin, name);
	cout << "2. practice: ";
	cin >> practice;
	cout << "3. age: ";
	cin >> age;

	return Employee(name, practice, age);
}