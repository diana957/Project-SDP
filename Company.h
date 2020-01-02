#ifndef _HEADER_COMPANY_INaCLUDED_
#define _HEADER_COMPANY_INCLUDED_

#include "Employee.h"
#include "NameRegister.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

struct Employees {
	Employee employee;
	vector<Employees*> children;

	Employees(const Employee& employee)
		: employee(employee.getName(), employee.getPractice(), employee.getAge())
		, children() {}
};

class Company {
public:
	Company();
	~Company();

public:
	//Read from Text file
	void readFromFile(const string& path);

public:
	void add(const Employee& employee, const string& boss, const string& how);
	void dissmiss(const string& employee);
	void allSubordinates(const string& employee)const;

private:
	void addBossWithSurbodinate(const Employee& employee, Employees *rootBoss);
	Employees* correspondPtr(const string& name)const;
	void dissmissWithSurbodinate(Employees *rootBoss);

private:
	bool isBoss(const string& name)const;
	Employees* findParent(Employees *rootChild)const;
	Employees* highestHeight(Employees *rootBoss)const;
	unsigned height(Employees *rootBoss)const;
	unsigned indexBoss(Employees *parent, Employees *rootBoss)const;

private:
	void clear(Employees *&root);

private:
	Company(const Company&);
	void operator=(const Company&) {}

private:
	Employees *root;
	NameRegister nameRegister;
};

#endif
