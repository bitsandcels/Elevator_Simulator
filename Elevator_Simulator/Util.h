#pragma once

/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

/*
	- Utilities and structs to be used
	- by other classes

*/

/* SIMULATION CONSTANTS */
const int MAX_PASSENGERS = 400;				//Total number of passengers
const int NUMBER_OF_SIMULATION_RUNS = 10;	//Total number of simualtion runs


/* ELEVATOR CONSTANTS */
const int TOP_FLOOR = 5;				//The highest floor of the building
const int BOTTOM_FLOOR = 1;				//The lobby floor (only floor to load and unload)
const int MAX_LOAD_UNLOAD_TIME = 3;		//Max time the eleveator can spend loading and unloading
const int MAX_TRAVEL_TIME = 15;			//Max time the elevator can travel between floors
const int MAX_WAIT_TIME = 10;			//Max time the elevator can wait at a single floor
const int MAX_NUM_PASSENGERS = 8;		//Max number of passangers that can board the elevator

/*
* This struct is to hold the only data information
* utilized by the elevator
*
*/
struct Passenger_Info
{
	int		customerNum;
	int		destFloor;
	double	arrivalTime;

	friend bool operator>(const Passenger_Info& cust1, const Passenger_Info& cust2)
	{
		return cust1.destFloor < cust2.destFloor;
	}
};