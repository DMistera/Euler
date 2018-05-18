#include "Writer.h"
#include <fstream>


Writer::Writer() {
}


Writer::~Writer() {
}

void Writer::add(int argument, long double value) {
	Node n;
	n.argument = argument;
	n.value = value;
	nodes.push_back(n);
}

void Writer::write(string filename) {
	ofstream file;
	file.open(filename + ".txt");
	for (Node n : nodes) {
		file << n.argument << ":" << n.value << ";" << endl;
	}
	file.close();
}