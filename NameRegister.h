#ifndef _HEADER_NAMEREGISTER_INCLUDED_
#define _HEADER_NAMEREGISTER_INCLUDED_

#include <vector>
#include <string>

using std::vector;
using std::string;

class NameRegister {
public:
	NameRegister();

public:
	bool addToRegister(const string& name);
	bool deleteFromRegister(const string& name);

private:
	int isExisting(const string& name)const;

private:
	vector<string> registerName;
};

#endif
