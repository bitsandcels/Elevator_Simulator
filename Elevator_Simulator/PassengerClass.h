#pragma once

class PassengerClass
{
private:
	int		customerNumber;		//Passenger's number
	double	interArrivalTime;	//inter arrival time
	double	arrivalTime;		//arrival time (what time they came)
	double	serviceStartTime;	//what time they got on the elevator
	double	timeInQueue;		//how long they waited
	int		destinationFloor;	//what floor they are going to

public:
	PassengerClass();
	~PassengerClass();

	void Set_CustomerNumber(int);					//Set the customer number
	void Set_interArrivalTime(double);				//Set the inter arrival time
	void Set_ArrivalTime(double);					//Set the arrival time
	void Set_ServiceStartAndQueueTime(double);		//Set the service and queue time
	void Set_DestinationFloor(int);					//Set the destination floor
		
	int Get_CustomerNumber();						//Return the customer number
	double Get_interArrivalTime();					//Return the inter arrival time
	double Get_ArrivalTime();						//Return the arrival time
	double Get_ServiceStartTime();					//Return the service time
	double Get_TimeInQueue();						//Return the time in queue
	int Get_DestinationFloor();						//Return the destination floor

	void Reset();									//Restart data 
};