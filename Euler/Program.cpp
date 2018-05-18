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
	long double elapsedTime = 0;
	clock_t start;
	clock_t end;

	Writer te[2];
	Writer th1[2];
	Writer tha[2];
	Writer ch[2];

	long double ETime = 0;
	long double H1Time = 0;
	long double HATime = 0;
	bool skipHA = false;

	while (!skipHA || (skipHA && (ETime < 1000))) {
		ETime = 0;
		for (int i = 0; i < 2; i++) {
			float density = i == 0 ? 0.2f : 0.6f;
			Graph graph = Graph();
			graph.generate(size, density);
			int* eulerCycle;
			int*hamiltonCycle;

			start = clock();
			graph.findEuler(&eulerCycle);
			end = clock();
			ETime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
			te[i].add(size, ETime);

			if (H1Time < 30 * 1000) {
				start = clock();
				graph.findHamilton(&hamiltonCycle);
				end = clock();
				H1Time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
				th1[i].add(size, H1Time);
			}


			if (!skipHA) {
				int count = 0;
				start = clock();
				graph.findAllHamiltons(&count);
				end = clock();
				elapsedTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
				HATime = elapsedTime;
				tha[i].add(size, elapsedTime);
				ch[i].add(size, count);
				if (elapsedTime > 3* 1000) {
					skipHA = true;
				}
			}
		}
		cout << "Finished for n = " << size << endl;
		if (skipHA) {
			size += 5;
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
