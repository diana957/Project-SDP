#include "Employee.h"

Employee::Employee(const string& name, unsigned practice, unsigned age)
	: name(name)
	, practice(practice)
	, age(age) {}

const string& Employee::getName()const {
	return name;
}

unsigned Employee::getPractice()const {
	return practice;
}

unsigned Employee::getAge()const {
	return age;
}

bool Employee::checkEmployee()const {
	if (age >= 18 && age <= 65) {
		if (practice < age) return true;
		return false;
	 }

	return false;
}
