#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Structs.h"

class Graph {
public:
	Graph();
	~Graph();
	pstationEntry m_head;
	void addStationEntry(std::string name);
	pstationEntry getStationEntry(std::string name);
	void dijkstra(std::string startName, std::string endName);
	void printRoute(std::vector<priorityEntry> processed);
	void calculateStats(std::vector<priorityEntry> &finalRoute);
};