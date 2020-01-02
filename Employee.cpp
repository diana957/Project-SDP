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

bool Employee::checkPerson(unsigned age)const {
	return (age >= 18 && age < 60) ? true : false;
}