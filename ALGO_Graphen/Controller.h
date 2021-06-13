#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Graph.h"

#define REMOVE_DUPLICATES 1

class Controller {
public:
	void startTask(char** argv);
private:
	Graph m_graph;
	void readGraph(std::string filename);
	void processLine(std::string line);
	void sortAdjacent();
	bool checkDuplicate(pstationEntry entry1, pstationEntry entry2);
	void printCompleteGraph();
};
