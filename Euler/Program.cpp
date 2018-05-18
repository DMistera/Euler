//
// Created by dmist on 2018-05-17.
//

#include <iostream>
#include "Program.h"
#include "Graph.h"
#include <ctime>
#include "Writer.h"

using namespace std;

void Program::start() {

	int size = 3;
	long double totalTime = 0;
	long double elapsedTime = 0;
	clock_t start;
	clock_t end;

	Writer te[2];
	Writer th1[2];
	Writer tha[2];
	Writer ch[2];

	double long HATime = 0;
	bool skipHA = false;
	while (!skipHA || (skipHA && (totalTime < 30 * 1000))) {
		totalTime = 0;
		for (int i = 0; i < 2; i++) {
			float density = i == 0 ? 0.2f : 0.6f;
			Graph graph = Graph();
			graph.generate(size, density);
			int* eulerCycle;
			int*hamiltonCycle;

			start = clock();
			graph.findEuler(&eulerCycle);
			end = clock();
			elapsedTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
			totalTime += elapsedTime;
			te[i].add(size, elapsedTime);

			start = clock();
			graph.findHamilton(&hamiltonCycle);
			end = clock();
			elapsedTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
			totalTime += elapsedTime;
			th1[i].add(size, elapsedTime);



			if (!skipHA) {
				int count = 0;
				start = clock();
				graph.findAllHamiltons(&count);
				end = clock();
				elapsedTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
				HATime = elapsedTime;
				tha[i].add(size, elapsedTime);
				ch[i].add(size, count);
				if (elapsedTime > 30* 1000) {
					skipHA = true;
				}
			}
		}
		cout << "Finished for n = " << size << endl;
		cout << "Total time: " << totalTime + HATime << endl;
		if (skipHA) {
			size += 30;
		}
		else {
			size++;
		}
	}

	for (int i = 0; i < 2; i++) {
		float density = i == 0 ? 0.2f : 0.6f;
		te[i].write("Euler Time" + to_string(density));
		th1[i].write("One Hamilton Time" + to_string(density));
		tha[i].write("All Hamiltons Time" + to_string(density));
		ch[i].write("Hamilton Count" + to_string(density));
	}
}
