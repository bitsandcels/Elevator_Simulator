#pragma once

/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

#include "Util.h"
#include <queue>
#include <functional>

enum ElevatorState
{
	IDLE,			// Elevator is not moving/waiting
	DOOR_OPEN,		// Elevator is letting people in
	DOOR_CLOSED,	// Elevator is no longer letting people in
	MOVING_UP,		// Elevator is moving up
	MOVING_DOWN		// Elevator is moving down
};

class ElevatorClass
{
private:
	ElevatorState Elevator_State;

	int elevator_timer_tracker; //tracks the current time of the elevator, restarts whenever the state is changed
	int current_floor;			//tracks the elevator's current floor

	std::priority_queue<Passenger_Info, std::vector<Passenger_Info>,		//Passengers will be in the form of a priority queue
		std::greater<std::vector<Passenger_Info>::value_type> > Passengers;		//where passengers get off in order of the floors

	std::queue<Passenger_Info> QueueLine;	//All the passengers waiting to get on the elevator

	void SearchAndRemovePassengers();			//Remove any passenger
	void ManageElevatorBehavior(bool&, int&);	//Update beavhior and send back customer that has been served

public:
	ElevatorClass();
	~ElevatorClass();

	void AddPassenger(Passenger_Info); //Add a passenger to the elevator

	int GetQueueSize();		//Return line queue size

	void Update(bool&, int&);	//update elevator's states
};