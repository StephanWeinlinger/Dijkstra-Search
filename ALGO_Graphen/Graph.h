#pragma once

#include <iostream>
#include <string>
#include <vector>

struct stationEntry; // forward declaration since it's used in adjEntry, but not defined yet

typedef struct adjEntry {
	adjEntry(int weight, stationEntry* entry, std::string type)
		: m_weight(weight), m_entry(entry), m_type(type) {}
	int m_weight;
	stationEntry* m_entry;
	std::string m_type;
} adjEntry;

typedef struct stationEntry {
	stationEntry(std::string name, stationEntry* next)
		: m_name(name), m_next(next) {}
	std::string m_name;
	std::vector<adjEntry> m_adjStations;
	stationEntry* m_next;
} stationEntry;
typedef stationEntry* pstationEntry;

class Graph {
public:
	Graph();
	~Graph();
	pstationEntry m_head;
	void addStationEntry(std::string name);
	pstationEntry getStationEntry(std::string name);
};