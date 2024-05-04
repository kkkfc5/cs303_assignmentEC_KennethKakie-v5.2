#include "callQueue.h"


callQueue::callQueue() { head = nullptr; tail = nullptr; queueSize = 0; }



int callQueue::determineDistance(buttonPress targetFloor, int elevatorCurrentFloor) {


	// =========================================================================================================== //
	// Basically:                                                                                                  //
	// This works by going through the whole queue in a very similar way that the insertion does.                  //
	// Each node it passes, it sums up how far its already traveled.                                               //
	// It finds the position the button press would be inserted, and then it returns the distance to that point.   //
	// =========================================================================================================== //


	buttonPress* temp = head;
	int dist = 0, index = 0;


	if (isEmpty()) { return abs(elevatorCurrentFloor - targetFloor.floor); } // base case; it is the distance between the elevator and the target floor
	if (head == tail) { return abs(head->floor - elevatorCurrentFloor) + abs(head->floor - targetFloor.floor); } // return (dist between elevator's current floor and first node in list's) + (dist between first node's and target floor's)


	dist = abs(head->floor - elevatorCurrentFloor); // base case as mentioned above.

	// find if it is closer to the low or the high. 
	// loop through the queue (doing summation) until reached low/high, and then add the distance to the target to the summation.


	temp = head;

	   // ===============================================================================================================

	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============
	   // ============= THIS STATEMENT'S CODE IS LARGELY THE SAME AS THE "ADDNEWPRESS" FUNCTION BELOW. =============

	   // ===============================================================================================================

	   // go visit that code down there if you want. it'd probably be easier to read; this code here is going to be condensed

	   // ===============================================================================================================

	bool foundInsertionPoint = false;

	// initial case, need to check if it is between current floor and first node
	if ((elevatorCurrentFloor < head->floor) && (elevatorCurrentFloor < targetFloor.floor && targetFloor.floor < head->floor) && targetFloor.goingUp) { foundInsertionPoint = true; }// if going up && in between current floor and target floor && to add is also going up
	else if ((elevatorCurrentFloor > head->floor) && (elevatorCurrentFloor > targetFloor.floor && targetFloor.floor > head->floor) && !targetFloor.goingUp) { foundInsertionPoint = true; }// else if going down && in between current floor and target floor && is also going down

	if (foundInsertionPoint) { return (elevatorCurrentFloor - targetFloor.floor); }// if targetFloor is in between elevator current floor and floor elevator is headed to

	while (temp != tail && temp != nullptr && temp->next != nullptr) {
		if (temp->goingUp) {

			// inflection case
			if (!temp->next->goingUp) { // if next node is going down
				if (temp->floor > targetFloor.floor && targetFloor.floor > temp->next->floor) { foundInsertionPoint = true; break; }
				else { dist += abs(temp->floor - temp->next->floor); temp = temp->next; continue; }
			}

			// BETWEEN CASE
			//if floor to add is in between this node and the next, and floor to add is going in the same direction, and the elevator direction isn't going to change, add it
			else if ((temp->floor < targetFloor.floor && targetFloor.floor < temp->next->floor) && (targetFloor.goingUp)) {
				if (temp->goingUp == temp->next->goingUp) { foundInsertionPoint = true; break; } // if in between to floors going in the same direction
				else { dist += abs(temp->floor - temp->next->floor); temp = temp->next; continue; } // 
			}

		}
		else { // if going down
			// inflection case
			if (temp->next->goingUp) { // if next node is going down
				if (temp->floor < targetFloor.floor && targetFloor.floor < temp->next->floor) { foundInsertionPoint = true; break; }
				else { dist += abs(temp->floor - temp->next->floor); temp = temp->next; continue; }
			}

			// between case
			//if floor to add is in between this node and the next, and it is going in the same direction, add it
			else if ((temp->floor > targetFloor.floor && targetFloor.floor > temp->next->floor) && (!targetFloor.goingUp)) {
				if (temp->goingUp == temp->next->goingUp) { foundInsertionPoint = true; break; } // if in between to floors going in the same direction
				else { dist += abs(temp->floor - temp->next->floor); temp = temp->next; continue; } // if at inflection point, continue
			}
		}
		temp = temp->next;
	}

	if (foundInsertionPoint) { return dist + abs(temp->floor - targetFloor.floor); }

	// FIND DISTANCE AFTER TAIL
	return dist + abs(tail->floor - targetFloor.floor);

}





void callQueue::addNewPress(buttonPress temp, int elevatorCurrentFloor) {
	buttonPress* toAdd = new buttonPress;
	toAdd->floor = temp.floor;
	toAdd->goingUp = temp.goingUp;
	toAdd->isInit = temp.isInit;


	if (isEmpty()) { head = toAdd; tail = toAdd; queueSize++; return; }
	else if (head == tail) {  // if there's only one object in the queue
		
		// if going up && in between current floor and target floor && to add is also going up
		if (((elevatorCurrentFloor < head->floor) && (elevatorCurrentFloor < toAdd->floor && toAdd->floor < head->floor) && toAdd->goingUp) 
			// or if going down && in between current floor and target floor && to add is also going down
			|| ((elevatorCurrentFloor > head->floor) && (elevatorCurrentFloor > toAdd->floor && toAdd->floor > head->floor) && !toAdd->goingUp)) {
			toAdd->next = head; //  ]
			head->prev = toAdd; //  ] -> add new button press to beginning of queue
			head = toAdd; //        ]
		}
		else {
			toAdd->prev = head; //  ]
			head->next = toAdd; //  ] -> add new button press to end of queue 
			tail = toAdd; //        ]
		}
		queueSize++;
		return;
	}
	else { // need to sort

		bool goodToAdd = false;

		// initial case, need to check if it is between current floor and first node

		// if going up && in between current floor and target floor && to add is also going up
		if ((elevatorCurrentFloor < head->floor) && (elevatorCurrentFloor < toAdd->floor && toAdd->floor < head->floor) && toAdd->goingUp) { goodToAdd = true; }
		// else if going down && in between current floor and target floor && is also going down
		else if ((elevatorCurrentFloor > head->floor) && (elevatorCurrentFloor > toAdd->floor && toAdd->floor > head->floor) && !toAdd->goingUp) { goodToAdd = true; }

		if (goodToAdd) {
			toAdd->next = head;
			toAdd->prev = head->prev; // <- ought to be redundant, but just in case
			head->prev = toAdd;
			head = toAdd;
			queueSize++; return;
		}

		buttonPress* temp = head;

		while (temp != tail) {
			if (temp->goingUp) {
				
				// inflection case
				if (!temp->next->goingUp) { // if next node is going down
					if (temp->floor > toAdd->floor && toAdd->floor > temp->next->floor) { goodToAdd = true; break; }
					else{ temp = temp->next; continue; }
				}
				
				// BETWEEN CASE
				//if floor to add is in between this node and the next, and floor to add is going in the same direction, and the elevator direction isn't going to change, add it
				else if ((temp->floor < toAdd->floor && toAdd->floor < temp->next->floor) && (toAdd->goingUp)) {
					if (temp->goingUp == temp->next->goingUp) { goodToAdd = true; break; } // if in between to floors going in the same direction
					else { temp = temp->next; continue; } // 
				}
				
			}
			else { // if going down
				// inflection case
				if (temp->next->goingUp) { // if next node is going down
					if (temp->floor < toAdd->floor && toAdd->floor < temp->next->floor) { goodToAdd = true; break; }
					else { temp = temp->next; continue; }
				}

				// between case
				//if floor to add is in between this node and the next, and it is going in the same direction, add it
				else if ((temp->floor > toAdd->floor && toAdd->floor > temp->next->floor) && (!toAdd->goingUp)) { // ------------- PROBLEM IS HERERERE
					if (temp->goingUp == temp->next->goingUp) { goodToAdd = true; break; } // if in between to floors going in the same direction
					// need to cheeck inlfection case
					else { temp = temp->next; continue; } // if at inflection point, continue
				}
			}
			temp = temp->next;
		}

		if (goodToAdd) {
			toAdd->next = temp->next;
			toAdd->prev = temp;
			temp->next->prev = toAdd;
			temp->next = toAdd;
			queueSize++; return;
		}


		// final case, if gotten to this point, add after tail
		toAdd->prev = tail;
		tail->next = toAdd;
		tail = toAdd;

		queueSize++; return;


	}
}


void callQueue::pop() { // remove the first item in the queue

	if (isEmpty()) { cout << "\nQueue is empty.\n\n"; return; }

	buttonPress* del = head;

	head = head->next;
	if (head == nullptr) { tail = nullptr; } // if only one item in the list and we are deleting it, then set tail to be null as well
	else { head->prev = nullptr; } // if there is more than one element in the list

	delete del;

	queueSize--;
}




void callQueue::updateWaitTime(int elevatorCurrentFloor) {
	if (isEmpty()) { return; }

	int tempDist = abs(elevatorCurrentFloor - head->floor);
	head->floorsBeforeService = tempDist;
	head->stopsBeforeService = abs(elevatorCurrentFloor - head->floor);

	if (head == tail) { return; }

	buttonPress* temp = head->next;

	while (temp != nullptr) {
		tempDist += abs(temp->floor - temp->prev->floor); // distance = distance between current node and it's previous
		// - - - - - - - - - - - - - - - - - - -
		temp->floorsBeforeService = tempDist;
		temp->stopsBeforeService = temp->prev->stopsBeforeService + 1; // for each node in queue, add one to total nodes needing to stop at before user is serviced
		// - - - - - - - - - - - - - - - - - - -
		temp = temp->next;
	}
}



void callQueue::print2() {
	buttonPress* temp = head;
	bool first = true;
	while (temp != nullptr) {
		string dir = temp->goingUp ? "^" : "v"; 
		if (!temp->isInit) { dir = " "; }
		cout << "|" << setw(4) << temp->floor << setw(3) << " " // gap of 7
			 << "|  " << dir << "  "
			 << "|" << setw(4) << temp->floorsBeforeService << setw(4) << " " // gap of 15 
			 << "|" << setw(4) << temp->stopsBeforeService << setw(4) << "|"; // gap of 14
		if (first) { cout << " <- TARGET FLOOR"; first = false; }
		cout << "\n";
		temp = temp->next;
		
	}
}