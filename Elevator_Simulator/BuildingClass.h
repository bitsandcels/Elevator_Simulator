#pragma once

/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

#include <time.h>
#include <random>
#include <algorithm>
#include <vector>
#include <array>
#include "ElevatorClass.h"
#include "DataStatsClass.h"

class BuildingClass
{
private:
	const int MEAN_ARRIVAL_RATE = 9000;		//mean arrival rate is 800 customer per hour (formally 5)
	int NUM_ELEVATORS;						//Number of floors
	double SIMULATION_TIME;					//Simulation Time
	double CUSTOMERS_SERVED;					//Number of customers served

	std::array<int, 4> Floors { 2, 3, 4, 5 };			//Array of floor numebrs

	ElevatorClass* Elevators;				//Dynamic array to handle all the elevators

	DataStatsClass HoldData;				//Holds all of the data for the simulations

	//Engines
	std::mt19937 rnGenerator;
	std::exponential_distribution<double> expDistArrival;
	std::uniform_int_distribution<int> uid;

	void CreateEventList(bool);	//Create the scenario
	void ShuffleFloors();		//Assign each passenger a floor between 2 and 5 using shuffle
	int FindQueue();			//Find a queue for the passenger to go to 
	void SetFloors();			//Use std::shuffle to uniformly assign floors

public:
	BuildingClass(int);		//Set building with a number of elevators
	~BuildingClass();		//Destructor

	void RunSimulation();	//Run the simulation 10 times
};