#pragma once

#include "Structs.h"

class Compare {
public:
	bool operator()(priorityEntry entry1, priorityEntry entry2);
};