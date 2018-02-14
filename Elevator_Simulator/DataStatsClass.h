#pragma once

/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

#include "PassengerClass.h"
#include "Util.h"
#include <fstream>
#include <math.h>
#include <iomanip>
#include <iostream>

enum SetDataBy
{
	EMPTY,			//Define nothing
	CUSTOMERNUM,	//Define customer number
	INTERARRIVAL,	//Define inter arrival time
	ARRIVAL,		//Define arrival time
	SERVICESTART,	//Define service start time
	DESTFLOOR,		//Define destination floor
};

struct EventStatistics
{
	double avgWait;
	double MinWait;
	double MaxWait;
	double percentBelow60;
};


/*
	- This class will handle and hold all of the data used
*/
class DataStatsClass
{
private:
	PassengerClass* Passengers;			//The passengers/events themselves
	EventStatistics* SimulationStats;	//Holds the stats for 10 simulation runs

	double findMinimumWait();			//find minimum wait time
	double findMaximumWait();			//find maximum wait time
	double CalcAverageWait();			//find average wait time
	double percentageBelow60Secs();		//find custumers served in under a minute
	

public:
	DataStatsClass();
	~DataStatsClass();

	void SetPassengerData(SetDataBy, int, int, double);	//Sets any data
	double GetPassengerArrival(int);					//Only returns customer's arrival time

	Passenger_Info GetPassenger(int);					//Get the data for a certain passenger

	void ResetPassengerData();
	void dumpToFile(std::string);
	void InsertStatistics(int);		//Insert average wait, min wait, max wait
									//and percentage below 1
	void writeStatistics(std::string);	//Writes all simulation stats

};