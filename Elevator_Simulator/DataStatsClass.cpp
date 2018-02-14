/*
	Created by Celeste Miranda
	Github: bitsandcels

	-The user inputs the number of elevators for a 5 story building.
	-The simulation will run 10 times.
	-At the end, the results of the simulation will be printed in a cvs file
*/

#include "DataStatsClass.h"

DataStatsClass::DataStatsClass()
{
	Passengers = new PassengerClass[MAX_PASSENGERS];
	SimulationStats = new EventStatistics[NUMBER_OF_SIMULATION_RUNS];
}

DataStatsClass::~DataStatsClass()
{

}

/*
	- Use Data to define what to set
	- use CustNum to determine which customer to access
	- Use num to set elevator ID, customer number or destination floor
	- Use time to set inter arrival and service start

	- Set num or time to 0 when it is not being used
*/
void DataStatsClass::SetPassengerData(SetDataBy Data, int CustNum, int num, double time)
{
	switch(Data)
	{
	case EMPTY:			
		break;

	case CUSTOMERNUM:	
		Passengers[CustNum].Set_CustomerNumber(num);
		break;

	case INTERARRIVAL:	
		Passengers[CustNum].Set_interArrivalTime(time);
		break;

	case ARRIVAL:		
		if (CustNum == 0)
		{
			Passengers[CustNum].Set_ArrivalTime(0);
		}
		else
		{
			Passengers[CustNum].Set_ArrivalTime(Passengers[CustNum-1].Get_ArrivalTime());
		}
		break;

	case SERVICESTART:	
		Passengers[CustNum].Set_ServiceStartAndQueueTime(time);
		break;

	case DESTFLOOR:		
		Passengers[CustNum].Set_DestinationFloor(num);
		break;

	default:
		break;
	}
}

double DataStatsClass::GetPassengerArrival(int CustNum)
{
	return Passengers[CustNum].Get_ArrivalTime();
}

void DataStatsClass::ResetPassengerData()	//Reset everything passenger related
{
	for (int i = 0; i < MAX_PASSENGERS; ++i)
	{
		Passengers[i].Reset();
	}
}

Passenger_Info DataStatsClass::GetPassenger(int num)	//Return a passenger to get information for the elevator
{
	Passenger_Info temp;
	temp.arrivalTime = Passengers[num].Get_ArrivalTime();
	temp.customerNum = Passengers[num].Get_CustomerNumber();
	temp.destFloor = Passengers[num].Get_DestinationFloor();

	return temp;
}

void DataStatsClass::dumpToFile(std::string fileName)
{
	std::ofstream outFile;
	outFile.open(fileName);
	if (!outFile.is_open())
	{
		std::cout << "ERROR OPENING YOUR OUTPUT FILE\n";
	}

	//write 1st row of header data
	outFile << "Passenger" << ","
		<< "Inter-Arrival" << ","
		<< "Arrival" << ","
		<< "Destination" << ","
		<< "Service Start" << ","
		<< "Time Waiting" << "\n";
	//write 2nd row of header data
	outFile << "Number" << ","
		<< "Time(secs)" << ","
		<< "Time(secs)" << ","
		<< "Floor" << ","
		<< "Time(secs)" << ","
		<< "in Queue(secs)" << "\n";

	//write out the data from each row of events in the array
	for (int i = 0; i < MAX_PASSENGERS; ++i)
	{
		outFile << Passengers[i].Get_CustomerNumber() << ","
			<< Passengers[i].Get_interArrivalTime() << ","
			<< Passengers[i].Get_ArrivalTime() << ","
			<< Passengers[i].Get_DestinationFloor() << ","
			<< Passengers[i].Get_ServiceStartTime() << ","
			<< Passengers[i].Get_TimeInQueue() << "\n";
	}

	outFile.close();
}

//***************************************************************************
//Statistical Function Definitions
//***************************************************************************

//Calculate the waiting time for each Passanger and 
//updates the event list

//Find the MINIMUM waiting time
double DataStatsClass::findMinimumWait()
{
	double minimum = Passengers[0].Get_TimeInQueue();

	for (int i = 1; i < MAX_PASSENGERS; ++i)
	{
		if (Passengers[i].Get_TimeInQueue() < minimum && Passengers[i].Get_TimeInQueue() >= 0)
		{
			minimum = Passengers[i].Get_TimeInQueue();
		}
	}

	if (minimum < 0)
	{
		return 0;
	}

	return minimum;
}

//Find the MAXIMUM waiting time
double DataStatsClass::findMaximumWait()
{
	double maximum = Passengers[0].Get_TimeInQueue();

	for (int i = 1; i <= MAX_PASSENGERS; ++i)
	{
		if (Passengers[i].Get_TimeInQueue() > maximum)
		{
			maximum = Passengers[i].Get_TimeInQueue();
		}
	}

	return maximum;
}

//Calculate the AVERAGE wait time
double DataStatsClass::CalcAverageWait()
{
	double average = 0;

	for (int i = 0; i < MAX_PASSENGERS; ++i)
	{
		average += Passengers[i].Get_TimeInQueue();
	}

	average /= MAX_PASSENGERS;

	return average; //sum of all / total
}

//Calculate the percentage of waiting times below 1 minute (60 secs)
double DataStatsClass::percentageBelow60Secs()
{
	double percentBelow60 = 0;

	for (int i = 0; i < MAX_PASSENGERS; ++i)
	{
		if (Passengers[i].Get_TimeInQueue() < 60)
		{
			percentBelow60++;
		}
	}

	percentBelow60 /= MAX_PASSENGERS;
	percentBelow60 *= 100;

	return percentBelow60; // return calculated percentage
}

//Write calcualted statistics out to scenario file
void DataStatsClass::writeStatistics(std::string fileName)
{
	std::ofstream outFile;
	outFile.open(fileName);
	if (!outFile.is_open())
	{
		std::cout << "ERROR OPENING YOUR STATISTICS FILE\n";
	}

	//write 1st row of header data
	outFile << "Simulation" << ","
		<< "Average Queue" << ","
		<< "Minimum Queue" << ","
		<< "Maximum Queue" << ","
		<< "Percent Serviced in" << "\n";
	//write 2nd row of header data
	outFile << "Run Number" << ","
		<< "Time (sec)" << ","
		<< "Time(sec)" << ","
		<< "Time(sec)" << ","
		<< "1 minute" << "\n";

	//write out the data from each row of events in the array
	for (int i = 0; i < NUMBER_OF_SIMULATION_RUNS; ++i)
	{
		outFile << i + 1 << ","
			<< SimulationStats[i].avgWait << ","
			<< SimulationStats[i].MinWait << ","
			<< SimulationStats[i].MaxWait << ","
			<< SimulationStats[i].percentBelow60 << "\n";
	}

	outFile.close();
}

void DataStatsClass::InsertStatistics(int place)	//Set and save stat information
{
	SimulationStats[place].avgWait = CalcAverageWait();
	SimulationStats[place].MinWait = findMinimumWait();
	SimulationStats[place].MaxWait = findMaximumWait();
	SimulationStats[place].percentBelow60 = percentageBelow60Secs();
}