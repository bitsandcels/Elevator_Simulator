/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

#include "ElevatorClass.h"

ElevatorClass::ElevatorClass()
{
	current_floor = 1;
	elevator_timer_tracker = 0;
	Elevator_State = IDLE;
}

ElevatorClass::~ElevatorClass()
{

}

void ElevatorClass::SearchAndRemovePassengers()
{
	if (Passengers.empty()) //Leave if there are no passengers
	{
		return;
	}
	else
	{
		Passengers.pop();
	}
}

void ElevatorClass::ManageElevatorBehavior(bool &CustomerEntered, int &CustomerNum)
{

	if (current_floor > 1 && current_floor < 6)
	{
		SearchAndRemovePassengers();
	}

	switch (Elevator_State)
	{
	case IDLE:
		if (current_floor > 1)
		{
			if (elevator_timer_tracker == MAX_WAIT_TIME)
			{
				elevator_timer_tracker = 0;
				Elevator_State = MOVING_DOWN;
			}
			else
			{
				++elevator_timer_tracker;
			}
		}
		if (current_floor == 1)
		{
			if (Passengers.size() == MAX_NUM_PASSENGERS)// || elevator_timer_tracker == MAX_WAIT_TIME)
			{
				elevator_timer_tracker = 0;
				Elevator_State = DOOR_CLOSED;
			}
			else
			{
				if (!QueueLine.empty())
				{
					Passengers.push(QueueLine.front());
					CustomerEntered = true;
					CustomerNum = QueueLine.front().customerNum - 1;
					QueueLine.pop();
				}
				
				++elevator_timer_tracker;
			}
		}
		break;

	case DOOR_OPEN:
		if (elevator_timer_tracker == MAX_LOAD_UNLOAD_TIME)
		{
			elevator_timer_tracker = 0;
			Elevator_State = DOOR_CLOSED;
		}
		else
		{
			++elevator_timer_tracker;
		}
		break;

	case DOOR_CLOSED:
		if (elevator_timer_tracker == MAX_LOAD_UNLOAD_TIME)
		{
			elevator_timer_tracker = 0;
			if (!Passengers.empty() && current_floor < 6) //if there are still passengers, move up
			{
				Elevator_State = MOVING_UP;
			}
			if (Passengers.empty())
			{
				Elevator_State = IDLE;
			}
		}
		else
		{
			++elevator_timer_tracker;
		}
		break;

	case MOVING_UP:
		if (elevator_timer_tracker == MAX_TRAVEL_TIME)
		{
			elevator_timer_tracker = 0;
			++current_floor;
			Elevator_State = DOOR_OPEN;
		}
		else
		{
			++elevator_timer_tracker;
		}
		break;

	case MOVING_DOWN:
		if (elevator_timer_tracker == MAX_TRAVEL_TIME)	//If the max time has been reached,
		{
			elevator_timer_tracker = 0;					//Restart timer
			if (current_floor == 1)						//Change state if we are on the first floor
			{
				Elevator_State = IDLE;					//Prevent elevator from moving
			}
			else
			{
				--current_floor;						//Keep going down until lobby floor is reached
			}	
		}
		else
		{
			++elevator_timer_tracker;					//Add to timer
		}
		break;

	default:
		break;
	}
}

void ElevatorClass::AddPassenger(Passenger_Info Customer)	
{
	QueueLine.push(Customer);	//Add customer to elevator's queue line
}

int ElevatorClass::GetQueueSize()
{
	return QueueLine.size();	//Return elevator's queue size
}

void ElevatorClass::Update(bool &CustomerEntered, int &CustomerNum)
{
	if (Passengers.empty() && QueueLine.empty())	//If the elevator is completely empty
	{
		return;										//Leave
	}
	else
	{
		ManageElevatorBehavior(CustomerEntered, CustomerNum);	//Continue updating
	}
}