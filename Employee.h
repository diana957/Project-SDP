#ifndef _HEADER_EMPLOYEE_INCLUDED_
#define _HEADER_EMPLOYEE_INCLUDED_

#include <string>
using std::string;

class Employee {
public:
	Employee(const string& name, unsigned practice, unsigned age);

public:
	const string& getName()const;
	unsigned getPractice()const;
	unsigned getAge()const;
	bool checkPerson()const;

private:
	void operator=(const Employee&) {}

private:
	string name;
	unsigned practice;
	unsigned age;
};

#endif
