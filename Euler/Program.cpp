//
// Created by dmist on 2018-05-17.
//

#include <iostream>
#include "Program.h"
#include "Graph.h"
#include <ctime>
#include "Writer.h"
#include <chrono>

using namespace std;

void Program::start() {

	int size = 3;
	long double elapsedTime = 0;
	chrono::system_clock::time_point start;
	chrono::system_clock::time_point end;

	Writer te[2];
	Writer th1[2];
	Writer tha[2];
	Writer ch[2];

	long double ETime = 0;
	long double H1Time = 0;
	long double HATime = 0;
	bool skipHA = false;
	bool skipH1 = false;

	while (ETime < 5000*1000) {
		ETime = 0;
		for (int i = 0; i < 2; i++) {
			float density = i == 0 ? 0.2f : 0.6f;
			Graph graph = Graph();
			graph.generate(size, density);
			int* eulerCycle;
			int*hamiltonCycle;

			start = chrono::system_clock::now();
			graph.findEuler(&eulerCycle);
			end = chrono::system_clock::now();
			ETime = (long double)chrono::duration_cast<chrono::microseconds>(end - start).count();
			te[i].add(size, ETime);

			if (!skipH1 || i == 1) {
				start = chrono::system_clock::now();
				graph.findHamilton(&hamiltonCycle);
				end = chrono::system_clock::now();
				H1Time = (long double)chrono::duration_cast<chrono::microseconds>(end - start).count();
				th1[i].add(size, H1Time);
				if (H1Time > 2 * 1000 * 1000 && i == 0) {
					skipH1 = true;
				}
			}


			if (!skipHA) {
				int count = 0;
				start = chrono::system_clock::now();
				graph.findAllHamiltons(&count);
				end = chrono::system_clock::now();
				elapsedTime = (long double)chrono::duration_cast<chrono::microseconds>(end - start).count();
				HATime = elapsedTime;
				tha[i].add(size, elapsedTime);
				ch[i].add(size, count);
				if (elapsedTime > 3* 1000 * 1000) {
					skipHA = true;
				}
			}
		}
		cout << "Finished for n = " << size << endl;
		if (skipH1) {
			size += 20;
		}
		else if (skipHA) {
			size += 2;
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
