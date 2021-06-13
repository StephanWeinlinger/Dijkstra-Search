#include "Compare.h"

bool Compare::operator()(priorityEntry entry1, priorityEntry entry2) {
	return entry1.m_weight > entry2.m_weight;
}