#include "Company.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>

using std::ifstream;
using std::queue;
using std::cin;
using std::cout;
using std::cerr;
using std::stack;

Company::Company()
	: root(nullptr)
	, nameRegister() {}

Company::~Company() {
	clear(root);
}

void Company::readFromFile(const string& path) {
	ifstream input(path);
	if (!input) {
		cerr << "Cannot open this file for reading\n";
		return;
	}
	string name, boss, how;
	unsigned practice, age;
	while (input.peek() != EOF) {
		getline(input, name, ' ');
		input >> practice >> age;
		Employee employee(name, practice, age);
		if (root) {
			input.ignore();
			getline(input, boss, ' ');
		}
		getline(input, how);
		if (!root) {
			root = new Employees(employee);
			nameRegister.addToRegister(employee.getName());
		}
		else
			add(employee, boss, how);
	}

	input.clear();
	input.close();
}

void Company::add(const Employee& employee, const string& boss, const string& how) {
	if (!employee.checkEmployee()) {
		cerr << "This Employee cannot be hired because of unappropriate age or practice.\n";
		return;
	}
	
	if (!nameRegister.addToRegister(employee.getName())) {
		cerr << "Cannot hire this employee. Already exits.\n";
		return;
	}

	Employees *rootBoss = correspondPtr(boss);
	if (!rootBoss) {
		cerr << "Cannot hire this Employee because the boss doesn't exist.\n";
		return;
	}

	if (how == "without") rootBoss->children.push_back(new Employees(employee));
	else addBossWithSurbodinate(employee, rootBoss);
}

void Company::dissmiss(const string& employee) {
	if (isBoss(employee)) {
		cerr << "Cannot dismiss Boss!\n";
		return;
	}

	if (!nameRegister.deleteFromRegister(employee)) {
		cerr << "Cannot hire this employee. Already exits.\n";
		return;
	}

	Employees *rootBoss = correspondPtr(employee);
	if (!rootBoss) {
		cerr << "Cannot dismiss this Employee.\n";
		return;
	}

	if (rootBoss->children.empty()) {
		Employees *parent = findParent(rootBoss);
		unsigned index = indexBoss(parent, rootBoss);
		if (index != (parent->children.size() - 1))
			parent->children[index] = parent->children[parent->children.size() - 1];
		parent->children.pop_back();
	}
	else dissmissWithSurbodinate(rootBoss);
}

void Company::allSubordinates(const string& employee)const {
	const Employees *rootBoss = correspondPtr(employee);
	if (!rootBoss) {
		cerr << "This Employee doesn't exist.\n";
		return;
	}

	if (rootBoss->children.empty())
		cout << "This person doesn't have subordinates.\n";

	unsigned levels = rootBoss->children.size(), nextLevels = 0, cnt = 0;
	queue<const Employees*> queue;
	queue.push(rootBoss);
	const Employees *temp = nullptr;

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();

		for (size_t i = 0; i < temp->children.size(); ++i) {
			cout << temp->children[i]->employee.getName() << "  ";
			if (!temp->children.empty()) {
				queue.push(temp->children[i]);
				++cnt;
				nextLevels += temp->children[i]->children.size();
			}
			if (cnt == levels) {
				cnt = 0;
				levels = nextLevels;
				nextLevels = 0;
				cout << "\n";
			}
		}
	}
}

void Company::addBossWithSurbodinate(const Employee& employee, Employees *rootBoss) {
	Employees *newBoss = new Employees(employee);
	vector<Employees*> backUp = rootBoss->children;

	rootBoss->children.clear();
	rootBoss->children.push_back(newBoss);
	for (size_t i = 0; i < backUp.size(); ++i)
		newBoss->children.push_back(backUp[i]);
}

Employees* Company::correspondPtr(const string& name)const {
	if (root->employee.getName() == name) return root;

	queue<Employees*> queue;
	queue.push(root);

	while (!queue.empty()) {
		Employees *temp = queue.front();
		queue.pop();

		for (size_t i = 0; i < temp->children.size(); ++i) {
			if (temp->children[i]->employee.getName() == name)
				return temp->children[i];
			queue.push(temp->children[i]);
		}
	}

	return nullptr;
}

void Company::dissmissWithSurbodinate(Employees *rootBoss) {
	Employees *parent = findParent(rootBoss);
	Employees *findnewBoss = highestHeight(rootBoss);

	Employees *newBoss = new Employees(findnewBoss->employee);
	for (size_t i = 0; i < findnewBoss->children.size(); ++i)
		newBoss->children.push_back(findnewBoss->children[i]);
	vector<Employees*> backUp = rootBoss->children;

	unsigned index = indexBoss(parent, rootBoss);
	if (index != (parent->children.size() - 1))
		parent->children[index] = parent->children[parent->children.size() - 1];
	parent->children.pop_back();
	delete rootBoss;

	rootBoss = nullptr;

	parent->children.push_back(newBoss);
	for (size_t i = 0; i < backUp.size(); ++i) {
		if (backUp[i]->employee.getName() != newBoss->employee.getName())
			newBoss->children.push_back(backUp[i]);
	}
}

bool Company::isBoss(const string& name)const {
	return name == root->employee.getName();
}

Employees* Company::findParent(Employees* rootChild)const {
	queue<Employees*> queue;
	queue.push(root);
	Employees *temp = nullptr;

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();

		for (size_t i = 0; i < temp->children.size(); ++i) {
			if (temp->children[i]->employee.getName() == rootChild->employee.getName())
				return temp;
			queue.push(temp->children[i]);
		}
	}

	return nullptr;
}

Employees* Company::highestHeight(Employees *rootBoss)const {
	Employees *maxPtr = nullptr;
	unsigned max = 0, currHeight = 0;

	for (size_t i = 0; i < rootBoss->children.size(); ++i) {
		currHeight = height(rootBoss->children[i]);
		if (currHeight > max) {
			max = currHeight;
			maxPtr = rootBoss->children[i];
		}
	}
	if (max == 0) maxPtr = rootBoss->children[rootBoss->children.size() - 1];
	return maxPtr;
}

unsigned Company::height(Employees *rootBoss)const {
	int curr = -1;
	unsigned max = 0;

	stack<Employees*> stack;
	stack.push(rootBoss);
	const Employees *temp = nullptr;
	while (!stack.empty()) {
		++curr;
		if (curr > max) max = curr;

		temp = stack.top();
		stack.pop();

		if (temp->children.empty()) --curr;

		for (size_t i = 0; i < temp->children.size(); ++i)
			stack.push(temp->children[i]);
	}

	return max;
}

unsigned Company::indexBoss(Employees *parent, Employees *rootBoss)const {
	for (size_t i = 0; i < parent->children.size(); ++i) {
		if (!rootBoss || parent->children[i]->employee.getName() == rootBoss->employee.getName())
			return i;
	}
	return -1;
}


void Company::clear(Employees *&root) {
	if (!root)
		return;

	for (size_t i = 0; i < root->children.size(); ++i)
		clear(root->children[i]);

	delete root;
}
