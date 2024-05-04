#pragma once
#include <iostream>

#include <chrono>
#include <thread>

#include "callQueue.h"
#include "Building.h"

using namespace std;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
// how i learned to wait for realtime:
// https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
//   ^  only used on line 51. 

int main() {

	Building test5;
	test5.addElevator();


	test5.generate(); // ititialize 3 external button presses
	test5.generate();
	test5.generate();


	for (int i = 0; i < 15; i++) { test5.tick(); } // tick 15 times.

	test5.addElevator(); // add two elevators to the system
	test5.addElevator();

	test5.generate(); // initialize 3 more external button presses
	test5.generate();
	test5.generate();


	cout << "\nV================================================================================V";
	cout << "\n|Press any button to view 15 ticks for 5 seconds each.                           |"
		 << "\n|Watch as the elevators (O) start at a random floor and move to their target (X).|" 
		 << "\n|Above the building visualization is a list of every elevator and it's queue;    |"
		 << "\n|you will need to scroll to see it.                                              |";
	cout << "\nU================================================================================U\n";

	system("pause");


	for (int i = 0; i < 15; i++) { // in real time, tick
		test5.tick();
		sleep_for(seconds(5));
	}





	cout << "\n\n\n\n\n";
	system("pause");
	return 0;
}



// TO DO:
// ASK USER IF THEY WANT TO MANUALLY DO DETAILS OR AUTOMATICALLY RUN IT

// MY CODE THAT I HAVE NOW AUTOMATICALLY RUNS IT, BUT WE CAN MAKE A NEUTERED VERS FOR USERS