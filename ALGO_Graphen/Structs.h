#pragma once

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
		: m_name(name), m_next(next), m_processed(false) {}
	std::string m_name;
	std::vector<adjEntry> m_adjStations;
	stationEntry* m_next;
	bool m_processed;
} stationEntry;
typedef stationEntry* pstationEntry;

typedef struct priorityEntry {
	priorityEntry(pstationEntry entry)
		: m_entry(entry), m_weight(0), m_parentEntry(nullptr), m_parentType("NA") {}
	pstationEntry m_entry;
	int m_weight;
	pstationEntry m_parentEntry;
	std::string m_parentType;
} priorityEntry;