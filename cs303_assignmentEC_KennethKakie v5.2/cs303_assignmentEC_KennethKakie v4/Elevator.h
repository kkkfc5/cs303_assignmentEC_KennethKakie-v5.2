#pragma once
#include "callQueue.h"


class Elevator {
private:
	callQueue queue;
	bool goingUpwards;
	int currentFloor;
public:
	Elevator(int x); // elevaor must be initialized at a floor

	void move(); // move elevator, or if at target floor it will generate an "echo" (see line 16) 
	void stop(int totalFloors);

	buttonPress generateEcho(int totalFloors); // generates an internal ("echo") button press. i.e. once someone gets in an elevator, they then press a button.

	int determineDistance(buttonPress targetFloor) { return queue.determineDistance(targetFloor, currentFloor); } // returns the length of the shortest-distance insertion point
	bool hasArrived() { return (currentFloor == queue.peekFloor()); } // return true if elevator's current floor == target floor
	int peekTargetFloor() { return queue.peekFloor(); } // peeks the first floor in the queue
	int getCurrentFloor() { return currentFloor; }; // returns elevator's current floor

	void updateWaitTime() { queue.updateWaitTime(currentFloor); };
	void addPress(buttonPress x) { queue.addNewPress(x, currentFloor); }
	void print2() { queue.print2(); }

};
