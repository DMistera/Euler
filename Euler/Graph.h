//
// Created by dmist on 2018-05-17.
//

#ifndef EULER_GRAPH_H
#define EULER_GRAPH_H

#include <list>
#include <iostream>

using namespace std;

class Graph {
public:
    Graph();
    void generate(int size, float density);
	bool findEuler(int** result); //Result is one Euler cycle, returns false if haven't found any
    bool findHamilton(int **result); //Result is one Hamilton cycle
    bool findAllHamiltons(int* result); //Result is the number of Hamilton cycles
    list<int>* vertices;
    int getEdgeCount();
    int getSize();
	void print();
private:
    int size;
	int edgeCount;
    void join(int v1, int v2);
	bool joined(int v1, int v2);
	void removeEdge(list<int>* vertices, int v1, int v2);
    bool hamilton(int start, list<int> visited, int current, int* result, bool one);
	bool euler(list<int>* vertices, int current, int*result, int* count);
	template < typename T > 
	void shuffle(std::list<T>& lst);
};


#endif //EULER_GRAPH_H
