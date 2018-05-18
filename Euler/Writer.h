#pragma once

#include <string>
#include <list>

using namespace std;

class Writer {
public:
	Writer(string name);
	~Writer();
private:
	string name;
};
