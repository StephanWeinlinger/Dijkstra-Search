#include "Graph.h"

bool compare(priorityEntry entry1, priorityEntry entry2) {
	if(entry1.m_weight == 0) {
		return false;
	}
	if(entry2.m_weight == 0) {
		return true;
	}
	return entry1.m_weight < entry2.m_weight;
}

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

// DONT FORGET TO SORT THE ADJACENT STATIONS!!!
void Graph::dijkstra(std::string startName, std::string endName) {
	pstationEntry start = nullptr;
	std::vector<priorityEntry> queue;
	std::vector<priorityEntry> processed;
	for(pstationEntry p = m_head; p != nullptr; p = p->m_next) {
		priorityEntry entry(p);
		if(!p->m_name.compare(startName)) {
			start = p;
			start->m_processed = true;
			entry.m_weight = 0;
			processed.push_back(entry);
		}
		else {
			queue.push_back(entry);
		}
	}
	std::sort(queue.begin(), queue.end(), compare);
	while(1) {
		for(auto adjEntry : start->m_adjStations) {
			if(adjEntry.m_entry->m_processed) { // skip already processed nodes (better than searching the whole processed vector)
				continue;
			}
			for(std::vector<priorityEntry>::iterator queueEntry = queue.begin(); queueEntry != queue.end(); ++queueEntry) {
				if(!adjEntry.m_entry->m_name.compare(queueEntry->m_entry->m_name)) {
					if(queueEntry->m_weight > processed.back().m_weight + adjEntry.m_weight) {
						queueEntry->m_weight = adjEntry.m_weight + processed.back().m_weight;
						queueEntry->m_parentEntry = start;
						queueEntry->m_parentType = adjEntry.m_type;
					}
					if(queueEntry->m_weight == 0) {
						queueEntry->m_weight = queueEntry->m_weight + adjEntry.m_weight + processed.back().m_weight;
						queueEntry->m_parentEntry = start;
						queueEntry->m_parentType = adjEntry.m_type;
					}
					break;
				}
			}
		}
		std::sort(queue.begin(), queue.end(), compare);
		if(!start->m_name.compare(endName)) {
			break;
		}
		start = queue[0].m_entry;
		start->m_processed = true;
		processed.push_back(queue[0]);
		queue.erase(queue.begin());
	}
	//printQueue(queue, processed);
	printRoute(processed);
}

void Graph::printQueue(std::vector<priorityEntry> queue, std::vector<priorityEntry> processed) {
	for(auto i : processed) {
		std::cout << i.m_entry->m_name << ": " << i.m_weight << " " << i.m_parentType << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
	for(auto i : queue) {
		if(i.m_weight != 0) {
			std::cout << i.m_entry->m_name << ": " << i.m_weight << " " << i.m_parentType << std::endl;
		}
	}
}

void Graph::printRoute(std::vector<priorityEntry> processed) {
	std::string next = processed.back().m_entry->m_name;
	for(std::vector<priorityEntry>::reverse_iterator entry = processed.rbegin(); entry != processed.rend(); ++entry) {
		if(!entry->m_entry->m_name.compare(next)) {
			if(entry->m_parentEntry == nullptr) {
				std::cout << entry->m_entry->m_name << std::endl;
				std::cout << "Cost: " << processed.back().m_weight << std::endl;
				break;
			}
			std::cout << entry->m_entry->m_name << " <- " << entry->m_parentType << " <- ";
			next = entry->m_parentEntry->m_name;
		}	
	}
}