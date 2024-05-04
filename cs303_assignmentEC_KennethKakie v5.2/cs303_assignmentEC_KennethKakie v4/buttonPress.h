#pragma once


// ==================================================== V
//                                                      |
//  The nodes for a linked list/queue.                  |
//  Holds the direction and floor it wants to go to.    |
//                                                      |
// ==================================================== U


struct buttonPress {
public:
	int floor;
	bool goingUp;
	bool isInit = false;

	int floorsBeforeService;
	int stopsBeforeService;

	buttonPress* next = nullptr;
	buttonPress* prev = nullptr;
};