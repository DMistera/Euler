//
// Created by dmist on 2018-05-17.
//

#include "Graph.h"
#include <time.h>
#include<iostream>
#include<algorithm>
#include<random>
#include<list>
#include<vector>
#include<chrono>

Graph::Graph() {

}

void Graph::generate(int size, float density) {
	vertices = new list<int>[size];
	this->size = size;

	//Old method
	/*if(size >= 2) {
		join(0, 1);
	}
	srand(time(0));
	for(int i = 2; i < size; i++) {
		int v1 = rand()%i;
		int v2 = v1;
		while(v2 == v1) {
			v2 = rand()%i;
		}
		join(i, v1);
		join(i, v2);
	}*/


	//Guaranteed at least one Hamilton
	for (int i = 0; i < size - 1; i++) {
		join(i, i + 1);
	}
	join(0, size - 1);
	if (size > 5) {
		int desiredNumber = (int)(density * (float)(size*(size - 1)))/2;
		int currentNumber = size;
		while (currentNumber < desiredNumber) {
			//Look for triangles
			int v1 = rand() % size;
			int v2 = v1;
			while (v2 == v1) {
				v2 = rand() % size;
			}
			int v3 = v1;
			while (v3 == v1 || v3 == v2) {
				v3 = rand() % size;
			}
			if (!joined(v1, v2) && !joined(v2, v3) && !joined(v3, v1)) {
				join(v1, v2);
				join(v2, v3);
				join(v3, v1);
				currentNumber += 3;
			}
		}
	}

	//Calculate number of edges
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += vertices[i].size();
	}
	edgeCount = sum / 2;

	//Shuffle for better result on Hamilton cycle
	for (int i = 0; i < size; i++) {
		shuffle(vertices[i]);
	}

}

//From stackoverflow
template < typename T > void Graph::shuffle(std::list<T>& lst) // shuffle contents of a list
{
	// create a vector of (wrapped) references to elements in the list
	std::vector< std::reference_wrapper< const T > > vec(lst.begin(), lst.end());

	// shuffle (the references in) the vector
	std::shuffle(vec.begin(), vec.end(), std::mt19937{ std::random_device{}() });

	// copy the shuffled sequence into a new list
	std::list<T> shuffled_list{ vec.begin(), vec.end() };

	// swap the old list with the shuffled list
	lst.swap(shuffled_list);
}


void Graph::join(int v1, int v2) {
	vertices[v1].push_back(v2);
	vertices[v2].push_back(v1);
}

bool Graph::joined(int v1, int v2) {
	for (int v : vertices[v1]) {
		if (v == v2) {
			return true;
		}
	}
	return false;
}

void Graph::removeEdge(list<int>* vertices, int v1, int v2) {
	vertices[v1].remove(v2);
	vertices[v2].remove(v1);
}

int Graph::getEdgeCount() {
	return edgeCount;
}

int Graph::getSize() {
	return size;
}

void Graph::print() {
	for (int i = 0; i < size; i++) {
		cout << i << ": ";
		for (int vertex : vertices[i]) {
			cout << vertex << " ";
		}
		cout << endl;
	}
}

bool Graph::findHamilton(int **result) {
	(*result) = new int[size];
	return hamilton(0, list<int>(), 0, (*result), true);
}

bool Graph::findEuler(int** result) {
	(*result) = new int[edgeCount];
	list<int>* copy = new list<int>[size];
	for (int i = 0; i < size; i++) {
		copy[i] = vertices[i];
	}
	return euler(copy, 0, (*result), new int());
}

bool Graph::euler(list<int>* vertices, int current, int*result, int* count) {
	while (vertices[current].size() > 0) {
		int vertex = vertices[current].front();
		removeEdge(vertices, current, vertex);
		euler(vertices, vertex, result, count);
	}
	result[(*count)] = current;
	(*count)++;
	return true;
}

bool Graph::hamilton(int start, list<int> visited, int current, int *result, bool one) {
	bool any = false;
	for (int vertex : vertices[current]) {
		if (vertex == start) {
			if (visited.size() == size - 1) {
				if (one) {
					int i = 0;
					for (int v : visited) {
						result[i] = v;
						i++;
					}
					result[size - 1] = current;
				}
				else {
					(*result)++;
				}
				return true;
			}
		}
		bool add = true;
		for (int v : visited) {
			if (vertex == v) {
				add = false;
			}
		}
		if (add) {
			list<int> copy = visited;
			copy.push_back(current);
			bool r = hamilton(start, copy, vertex, result, one);
			if (r) {
				if (one) {
					return true;
				}
				else {
					any = true;
				}
			}
		}
	}
	return one ? false : any;
}

bool Graph::findAllHamiltons(int *result) {
	(*result) = 0;
	return hamilton(0, list<int>(), 0, result, false);
}
