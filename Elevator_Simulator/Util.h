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

const int MAX_PASSENGERS = 400;				//Total number of passengers
const int NUMBER_OF_SIMULATION_RUNS = 10;	//Total number of simualtion runs


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