#include "NameRegister.h"
#include <iostream>

using std::cerr;

NameRegister::NameRegister() : registerName() {}

bool NameRegister::addToRegister(const string& name) {
	if (isExisting(name) == -1) {
		registerName.push_back(name);
		return true;
	}

	return false;
}

bool NameRegister::deleteFromRegister(const string& name) {
	int index = isExisting(name);
	unsigned size = registerName.size() - 1;

	if (index == -1) {
		cerr << "Cannot dismiss this employee. It doesn't exits in the database.\n";
		return false;
	}

	if (index != size) registerName[index] = registerName[size];
	registerName.pop_back();
	return true;
}

int NameRegister::isExisting(const string& name)const {
	unsigned counter = 0;
	while (counter < registerName.size()) {
		if (registerName[counter] == name) return counter;
		++counter;
	}
	return -1;
}