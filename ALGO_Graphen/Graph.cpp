#include "Graph.h"

bool compareWeight(priorityEntry entry1, priorityEntry entry2) {
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

void Graph::dijkstra(std::string startName, std::string endName) {
	auto startTimer = std::chrono::high_resolution_clock::now();
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
		std::sort(queue.begin(), queue.end(), compareWeight);
		if(!start->m_name.compare(endName)) {
			break;
		}
		start = queue[0].m_entry;
		start->m_processed = true;
		processed.push_back(queue[0]);
		queue.erase(queue.begin());
	}
	auto stopTimer = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTimer - startTimer);
	printRoute(processed, duration.count());
}

void Graph::printRoute(std::vector<priorityEntry> processed, int duration) {
	std::string next = processed.back().m_entry->m_name;
	std::vector<priorityEntry> printList;
	for(std::vector<priorityEntry>::reverse_iterator entry = processed.rbegin(); entry != processed.rend(); ++entry) {
		if(!entry->m_entry->m_name.compare(next)) {
			if(entry->m_parentEntry == nullptr) {
				printList.push_back(*entry);
				break;
			}
			printList.push_back(*entry);
			next = entry->m_parentEntry->m_name;
		}	
	}

	for (std::vector<priorityEntry>::reverse_iterator entry = printList.rbegin(); entry != printList.rend(); ++entry) {
		if (entry->m_parentEntry == nullptr) {
			std::cout << "[START]: " << entry->m_entry->m_name;
		}
		else {
			std::cout << " -> " << "[" << entry->m_parentType << "]" << " -> "  << entry->m_entry->m_name;
		}
	}
	std::cout << std::endl << std::endl << "STATS ==========================================" << std::endl;
	std::cout << " - Calculation Time: " << duration << "ms" << std::endl;
	std::cout << " - Cost: " << processed.back().m_weight << std::endl;
	calculateStats(printList);
}

void Graph::calculateStats(std::vector<priorityEntry> & finalRoute){
	std::string lastTransport = "";
	unsigned int numberOfChanges = 0;
	unsigned int numberOfStations = 0;
	std::vector<std::string> transportList;

	for (std::vector<priorityEntry>::reverse_iterator entry = finalRoute.rbegin(); entry != finalRoute.rend(); ++entry) {
		if (entry->m_parentEntry == nullptr) {
			
		}
		else {
			if (lastTransport.compare(entry->m_parentType) != 0) {
				if (lastTransport != "") {
					numberOfChanges++;
				}
				transportList.push_back(entry->m_parentType);
			}
			lastTransport = entry->m_parentType;
			numberOfStations++;
		}
	}
	std::cout << " - Number of stations: " << numberOfStations << std::endl;
	std::cout << " - Changes: " << numberOfChanges << std::endl;
	std::cout << " - Used Transports: ";
	this->printTransport(0, transportList.size(), transportList);
	
	std::cout << std::endl;
}

int Graph::printTransport(int index, int size, std::vector<std::string> &transportList) {
	std::cout << transportList[index] << ", ";
	index++;
	if (index != size) {
		this->printTransport(index, size, transportList);
	}
	else {
		return 0;
	}
	
}