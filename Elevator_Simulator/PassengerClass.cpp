/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

#include "PassengerClass.h"

PassengerClass::PassengerClass()  //Set everything to zero
{
	customerNumber = 0;
	interArrivalTime = 0;
	arrivalTime = 0;
	serviceStartTime = 0;
	timeInQueue = 0;
	destinationFloor = 0;
}

PassengerClass::~PassengerClass()
{

}

void PassengerClass::Reset()
{
	customerNumber = 0;
	interArrivalTime = 0;
	arrivalTime = 0;
	serviceStartTime = 0;
	timeInQueue = 0;
	destinationFloor = 0;
}

void PassengerClass::Set_CustomerNumber(int num)
{
	customerNumber = num;
}

void PassengerClass::Set_interArrivalTime(double time)
{
	interArrivalTime = time;
}

void PassengerClass::Set_ArrivalTime(double time)
{
	arrivalTime = interArrivalTime + time;
}

void PassengerClass::Set_ServiceStartAndQueueTime(double time)
{
	serviceStartTime = time;			//Set the service start time to the current time
	timeInQueue = serviceStartTime - arrivalTime;	//Set time in queue
	if (timeInQueue < 0)
	{
		timeInQueue = 0;
	}
}

void PassengerClass::Set_DestinationFloor(int num)
{
	destinationFloor = num;
}

int PassengerClass::Get_CustomerNumber()
{
	return customerNumber;
}

double PassengerClass::Get_interArrivalTime()
{
	return interArrivalTime;
}

double PassengerClass::Get_ArrivalTime()
{
	return arrivalTime;
}

double PassengerClass::Get_ServiceStartTime()
{
	return serviceStartTime;
}

double PassengerClass::Get_TimeInQueue()
{
	return timeInQueue;
}

int PassengerClass::Get_DestinationFloor()
{
	return destinationFloor;
}