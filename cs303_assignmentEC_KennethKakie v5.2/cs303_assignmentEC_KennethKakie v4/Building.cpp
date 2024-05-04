#include "Building.h"

Building::Building() {
	totalFloors = 10;
	addElevator();
}

Building::Building(int floors) {
	totalFloors = floors;
	addElevator();
}

void Building::tick() {

	cout << "\n\n\n\n\f";

	
	for (int i = 0; i < elevatorList.size(); i++) {

		elevatorList[i].updateWaitTime(); // update the time that each node has to wait

		if (elevatorList[i].hasArrived()) { elevatorList[i].stop(totalFloors); } // if elevator has arrived, trigger it to stop
		else { elevatorList[i].move(); } // otherwise, move the elevator

		bool addNew = (rand() % 7 == 0); // 1/7th chance 
		if (addNew) { generate(); } // if 1/3rd chance == true, a new user has arrived outside an elevator

		elevatorList[i].updateWaitTime(); // update the time that each node has to wait
		print2(); 

	}
	


}

void Building::generate() { // this function exists because it originally was meant to house both types of floor call. I am not deleting it out of laziness.
	buttonPress init = generateInit(); // generate an external ("initial") button press
	
	cout << "\nSomeone is calling an elevator to the floor: " << init.floor << "\n";
	init.isInit = true;
	addPress(init);
}


buttonPress Building::generateInit() {
	int randFloor = (rand() % totalFloors) + 1; // rand number between 1 and total building floors 
	bool randDir = (rand() % 1000) % 2 == 0; // if random number is even, then it is going up

	buttonPress temp;
	temp.floor = randFloor;

	if (temp.floor == totalFloors) { randDir = false; }// if at top, only direction to go is down
	else if (temp.floor == 1) { randDir = true; } // if at bottom, only direction to go is up
	temp.goingUp = randDir;

	return temp;
}

void Building::addPress(buttonPress init) {
	int minDist = 999; // ideally, the queue is less than 999 floors long.
	int minDistElev = 0; // index of min elevator
	int temp;

	for (int i = 0; i < elevatorList.size(); i++) { // for every elevator
		temp = elevatorList[i].determineDistance(init);
		if (temp < minDist) { // if the distance to the target floor is less than the previous minimum distance
			minDist = temp; // replace the minimum distance
			minDistElev = i; // replace the index val for the closest elevator
		}
	}
	
	elevatorList[minDistElev].addPress(init); // add the press to the closest elevator
}

/*
void Building::hasArrived() { // checks every elevator in the vector to see if it has arrived. If so, then calls stop.
	for (int i = 0; i < elevatorList.size(); i++) { // for every elevator
		if (elevatorList[i].hasArrived()) {
			elevatorList[i].stop(totalFloors);
		}
	}
}*/




void Building::print2() {

	// PRINT EACH ELEVATOR'S QUEUE

	cout << "\n\n\n\n";
	for (int i = 0; i < elevatorList.size(); i++) {
		cout << "Elevator " << i + 1 << " Queue :\n";
		cout << "V=======V=====V================V\n";
		cout << "| Press |     | Before Service |\n";
		cout << "| Floor | Dir | Floors | Stops |\n";
		elevatorList[i].updateWaitTime();
		elevatorList[i].print2();
		cout << "U=======U=====U========U=======U\n\n\n";
	}

	// ====================================================
	// ====================================================
	// ====================================================

	// PRINT THE BUILDING

	cout << "\n X is the Target Floor.\nO is the Current Floor. \n";

	cout << "\n     Building's";
	cout << "\n     Elevators:     \n";
	for (int i = 0; i < elevatorList.size(); i++) { cout << setw(4) << i+1; }

	cout << "\nU=";
	for (int i = 0; i < elevatorList.size(); i++) { cout << "===="; }
	cout << "U\n";

	for (int x = 0; x < totalFloors; x++) {
		cout << "| ";
		for (int y = 0; y < elevatorList.size(); y++) {
			cout << "[";
			if (elevatorList[y].getCurrentFloor() == (totalFloors - (x))) { cout << "O"; }
			else if (elevatorList[y].peekTargetFloor() == (totalFloors - (x))) { cout << "X"; }
			else cout << " ";
			cout << "] ";
		}
		cout << "| " << (totalFloors - (x)) << "\n";
	}
	cout << "#=";
	for (int i = 0; i < elevatorList.size(); i++) { cout << "===="; }
	cout << "#\n\n";
}


