#include "Graph.h"

Graph::Graph() {
	m_head = nullptr;
}

Graph::~Graph() {
	while(m_head != nullptr) {
		pstationEntry tmp = m_head;
		m_head = m_head->m_next;
		delete tmp;
	}
}

void Graph::addStationEntry(std::string name) {
	pstationEntry newentry = new stationEntry(name, m_head);
	m_head = newentry;
}

pstationEntry Graph::getStationEntry(std::string name) {
	for(pstationEntry p = m_head; p != nullptr; p = p->m_next) {
		if(!p->m_name.compare(name)) { // compare returns 0 if strings match
			return p;
		}
	}
	return nullptr;
}