#pragma once

#include <string>
#include <list>

using namespace std;

class Writer {
public:
	Writer();
	~Writer();
	void add(int argument, long double value);
	void write(string filename);
private:
	struct Node {
		int argument;
		long double value;
	};
	list<Node> nodes;
};
