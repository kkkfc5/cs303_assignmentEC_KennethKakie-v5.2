#pragma once
#include <vector>

#include "Elevator.h"

class Building {
private:
	int totalFloors;

public:

	vector<Elevator> elevatorList;

	Building();
	Building(int floors);

	void generate(); // houses below function
	buttonPress generateInit(); // generate an external button press

	void tick(); // HOLDS ALL FUNCTIONS THAT NEED TO RUN ONCE PER... TICK


	void addPress(buttonPress init);

	void addElevator() { Elevator e(totalFloors); elevatorList.push_back(e); }

	void print2();
};
