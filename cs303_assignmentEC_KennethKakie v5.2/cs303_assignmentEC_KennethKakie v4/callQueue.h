#pragma once

#include <iostream>
#include <iomanip>

#include "buttonPress.h"

using namespace std;

// ==================================================== V
//                                                      |
//  A queue each elevator will have.                    |
//  It holds many buttonPresses in the order the        |
//   elevator needs to get to them in.                  |
//                                                      |
// ==================================================== U



class callQueue {
private:
	buttonPress* head;
	buttonPress* tail;
	int queueSize;

public:

	callQueue();

	int determineDistance(buttonPress targetFloor, int elevatorCurrentFloor); // returns the length of the shortest-distance insertion point

	void addNewPress(buttonPress temp, int elevatorCurrentFloor);
	void updateWaitTime(int elevatorCurrentFloor);

	void pop();
	void print2();

	int peekFloor() { if (!isEmpty()) return head->floor; return -1; }
	int peekFloorsBeforeService() { return head->floorsBeforeService; };
	int peekStopsBeforeService() { return head->stopsBeforeService; };
	int size() { return queueSize; }

	bool peekDirection() { return head->goingUp; }
	bool isEmpty() { return head == nullptr; }
	bool isInit() { return (head->isInit); }


};



// TO FIND WHO IS CLOSEST: AFTER CHECKING IF THEY ARE GOING IN SAME DIR, CHECK THE FIRST NODE GOING IN OPPOSITE DIR IN EACH ELEVATOR'S QUEUE. ADD TO WHOMEVER IS CLOSEST
// need to hav func to do this (find closest) and have it return the future closest elevator's floor. Save that in a wrapper function that saves the closest value and also one that 
//		save's that elevator's index. Compare the int MIN, and then at end, add it to elevator[saved_i].


// secondart vect<int> to hold each elevator's distance
// or two integers, one with min dist and one with elevator index


// do summation yntil you get to the point of overshot