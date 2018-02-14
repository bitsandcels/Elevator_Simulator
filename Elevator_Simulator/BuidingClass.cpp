#include "BuildingClass.h"

BuildingClass::BuildingClass(int numElevators) : rnGenerator((unsigned int)time(0)), expDistArrival(MEAN_ARRIVAL_RATE), uid(0, 1)
{
	NUM_ELEVATORS = numElevators;
	Elevators = new ElevatorClass[NUM_ELEVATORS];
	SIMULATION_TIME = 0;
	CUSTOMERS_SERVED = 0;
}

BuildingClass::~BuildingClass()
{

}

void BuildingClass::SetFloors()
{
	for (int i = 0; i < MAX_PASSENGERS; i+=4) //Give each passenger a floor for every 4
	{
		HoldData.SetPassengerData(DESTFLOOR, i, Floors[0], 0);
		HoldData.SetPassengerData(DESTFLOOR, i + 1, Floors[1], 0);
		HoldData.SetPassengerData(DESTFLOOR, i + 2, Floors[2], 0);
		HoldData.SetPassengerData(DESTFLOOR, i + 3, Floors[3], 0);

		ShuffleFloors();	//Shuffle the array of floors 
	}
}

void BuildingClass::CreateEventList(bool doSeedRAND)
{
	if (doSeedRAND)
	{
		//Let's create our event list generate arrival times and desintation floors
		srand(time(0));
	}

	SetFloors();	//Assign Floors

	for (int i = 0; i < MAX_PASSENGERS; ++i)	//For all passengers
	{
		HoldData.SetPassengerData(CUSTOMERNUM, i, i + 1, 0);	//give their number

		HoldData.SetPassengerData(INTERARRIVAL, i, 0, (expDistArrival(rnGenerator) * 3600)); //Change to seconds

		HoldData.SetPassengerData(ARRIVAL, i, 0, 0);	//set arrival time

		Elevators[FindQueue()].AddPassenger(HoldData.GetPassenger(i));	//send them to a queue
	}
}

int BuildingClass::FindQueue()
{
	if (NUM_ELEVATORS == 1) //if there is only one elevator, leave
	{
		return 0;
	}

	int CurrentQueue = 0; 
	int SmallestQueueSize = Elevators[CurrentQueue].GetQueueSize();
	for (int i = 1; i < NUM_ELEVATORS; ++i) //search through elevator queues to find smallest line
	{
		if (SmallestQueueSize > Elevators[i].GetQueueSize())
		{
			SmallestQueueSize = Elevators[i].GetQueueSize();
			CurrentQueue = i; //Set to that queue and return it
		}
	}

	return CurrentQueue;
}

void BuildingClass::ShuffleFloors()
{
	std::shuffle(Floors.begin(), Floors.end(), rnGenerator); //Use std::shuffle to mix the array
}

void BuildingClass::RunSimulation()
{
	for (int S = 0; S < NUMBER_OF_SIMULATION_RUNS; ++S)
	{
		SIMULATION_TIME = 0;	//Reset time
		CUSTOMERS_SERVED = 0;	//Reset customer count

		std::cout << "On Simulation Run: " << S << "\n"; //Identify what simulation is being conducted

		CreateEventList(S == 0 ? true : false); //Create numbers
		int customerNum = 0; //Data holder when the elevator returns the customer number that was served
		bool running = true; //while-loop condition
		bool CustomerEntered = false; //Condition to update customers that were served

		while (running)
		{
			++SIMULATION_TIME;
			SIMULATION_TIME += uid(rnGenerator);	//Create decimal values

			if (CUSTOMERS_SERVED == MAX_PASSENGERS) //End simulation when all customers were served
			{
				running = false;
			}

			for (int i = 0; i < NUM_ELEVATORS; ++i)	//Update each elevator and update passengers
			{
				Elevators[i].Update(CustomerEntered, customerNum);
				if (CustomerEntered)
				{
					HoldData.SetPassengerData(SERVICESTART, customerNum, 0, SIMULATION_TIME); //Get service time
					CustomerEntered = false;
					++CUSTOMERS_SERVED;
				}
			}
		}

		if (S == 0)
		{
			HoldData.dumpToFile("eventList.csv"); //only print out one set of the simulation runs
		}

		HoldData.InsertStatistics(S);	//Send sim run data and store it
		HoldData.ResetPassengerData();	//Reset simulation

	}

	HoldData.writeStatistics("CourseProject_Scenario.csv"); //print out all of the simulation data

	std::cout << "Check eventList.csv to see one simulation run!\n";
	std::cout << "End of simulation, check CourseProject_Scenario.csv for accuracy!\n\n";
}