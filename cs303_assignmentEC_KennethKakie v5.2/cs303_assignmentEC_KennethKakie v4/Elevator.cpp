#include "Elevator.h"


Elevator::Elevator(int totalFloors) {
	goingUpwards = true;
	currentFloor = rand() % totalFloors + 1;
}



void Elevator::move() {
	if (!queue.isEmpty()) { // if the elevator has a destination
		if (currentFloor < queue.peekFloor()) { currentFloor++; goingUpwards = true; } // if needing to move upwards
		else if (currentFloor > queue.peekFloor()) { currentFloor--; goingUpwards = false; } // if needing to move downwards
	}
}


void Elevator::stop(int totalFloors) { // when stopping at a init call, generate some echos

	bool isInit = queue.isInit();
	queue.pop(); // if we've arrived, delete the front of the queue
	
	if (isInit) { // if it is an exterior button press (people are getting on the elevator)
		queue.addNewPress(generateEcho(totalFloors), currentFloor); // someone will press a button upon entering elevator
	}
}


buttonPress Elevator::generateEcho(int totalFloors) {
	int randFloor = (rand() % totalFloors) + 1;
	bool randDir = rand() % 2 == 0 ? true : false; // if random number is even, then it wants to go up

	buttonPress temp;
	temp.floor = randFloor;
	temp.isInit = false; // saying this floor stop is an echo

	if (randFloor == 1) { randDir = true; } // if at the bottom, only direction to go is up
	else if (randFloor == totalFloors) { randDir = false; } // if at top, only direction to go is down
	temp.goingUp = randDir;

	cout << "\nSomeone inside the elevator pressed the button for floor: " << temp.floor << "\n";

	return temp;
}



