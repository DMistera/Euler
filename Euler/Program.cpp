//
// Created by dmist on 2018-05-17.
//

#include <iostream>
#include "Program.h"
#include "Graph.h"
#include <ctime>

using namespace std;

void Program::start() {

	int size = 3;
	long double time = 0;
	long double elapsedTime;
	clock_t start;
	clock_t end;
	while (time < 3000) {
		for (int i = 0; i < 2; i++) {
			float density = i == 0 ? 0.2f : 0.6f;
			Graph graph = Graph();
			graph.generate(size, density);
			int* eulerCycle;
			int*hamiltonCycle;
			int count = 0;

			start = clock();
			graph.findEuler(&eulerCycle);
			end = clock();
			elapsedTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;

			graph.findHamilton(&hamiltonCycle);
			graph.findAllHamiltons(&count);
			int max = (graph.getSize() * (graph.getSize() - 1)) / 2;
			int edges = graph.getEdgeCount();
		}
	}
}
