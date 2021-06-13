#include "Controller.h"

void Controller::startTask(char** argv) {
	//readGraph(argv[1]);
	readGraph("input.txt");
	if(m_graph.m_head != nullptr) {
		m_graph.dijkstra("Heiligenstadt", "Beethovengang");
	}
	else {
		std::cout << "File is empty!" << std::endl;
	}
}

void Controller::readGraph(std::string filename) {
	std::string line;
	std::ifstream source(filename);
	if(source.is_open()) {
		while(getline(source, line)) {
			processLine(line);
		}
		source.close();
	}
	else {
		std::cout << "File is opened or not existent!" << std::endl;
	}
}

void Controller::processLine(std::string line) {
	std::string type = line.substr(0, line.find(":"));
	line.erase(0, type.length() + 2); // removes type and ": " for clean data
	// start of station insertion
	std::string name = "";
	pstationEntry entry = nullptr;
	int weight = 0;
	std::string name_before = "";
	pstationEntry entry_before = nullptr;
	int weight_before = 0;
	while(!line.empty()) {
		if(entry != nullptr) {
			name_before = name;
			entry_before = entry;
			weight_before = weight;
		}
		name = line.substr(1, line.find("\"", 1) - 1);
		line.erase(0, name.length() + 3);
		entry = m_graph.getStationEntry(name);
		if(entry == nullptr) {
			m_graph.addStationEntry(name);
			entry = m_graph.m_head; // since new entries get inserted in front
		}

		// add to adjStations
		if(entry_before != nullptr) {
			if(!checkDuplicate(entry_before, entry)) {
				adjEntry adjStation1(weight_before, entry, type);
				entry_before->m_adjStations.push_back(adjStation1);
				adjEntry adjStation2(weight_before, entry_before, type);
				entry->m_adjStations.push_back(adjStation2);
			}
		}

		if(line.empty()) {
			break;
		}
		weight = (int) line[0] - '0';
		line.erase(0, 2);
	}
	
}

bool Controller::checkDuplicate(pstationEntry entry1, pstationEntry entry2) {
	if(!REMOVE_DUPLICATES) {
		return false;
	}
	bool check = false;
	for(auto i : entry1->m_adjStations) {
		if(!i.m_entry->m_name.compare(entry2->m_name)) {
			check = true;
		}
	}
	return check;
}

void Controller::printCompleteGraph() {
	for(pstationEntry p = m_graph.m_head; p != nullptr; p = p->m_next) {
		std::cout << "[" << p->m_name << "]" << ": ";
		for(auto i : p->m_adjStations) {
			std::cout << i.m_entry->m_name << "*" << i.m_weight << "*" << i.m_type << " ||| ";
		}
		std::cout << std::endl;
	}
}