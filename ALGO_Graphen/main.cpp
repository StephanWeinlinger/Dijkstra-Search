#include <iostream>
#include "Controller.h"

int main(int arc, char** argv) {
	Controller controller;
	switch(arc) {
		case 4:
			controller.startTask(argv);
			break;
		default:
			std::cout << "Wrong parameter amount!" << std::endl;
	}
	return 0;
}