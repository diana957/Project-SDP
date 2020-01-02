#include <iostream>
#include "Company.h"

using std::cout;
using std::cerr;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cerr << "Not enough arguments\n";
		return -1;
	}

	
	Company company;
	company.readFromFile(argv[1]);
	company.dissmiss("Dragomir");
	company.allSubordinates("Pesho");
	cout << "---------------------\n";
	company.allSubordinates("Pesho");
	cout << "------------------\n";
	company.allSubordinates("Smurkjkj");
	cout << "-------------------------\n";
	Employee emp("Genadi", 3, 22);
	company.add(emp, "Sashko", "without");
	company.allSubordinates("Stavri");
	cout << "-----------------\n";
	company.dissmiss("Stoimenka");
	company.allSubordinates("Pesho");
	
	system("pause");
	return 0;
}