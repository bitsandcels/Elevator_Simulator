/*
		Created by Celeste Miranda
		Github: bitsandcels

		-The user inputs the number of elevators for a 5 story building. 
		-The simulation will run 10 times.
		-At the end, the results of the simulation will be printed in a cvs file
*/

#include "BuildingClass.h"


int main()
{
	bool DoSeedRAND = true;
	int NumElevators = 0;
	bool validInput = false;
	while (!validInput)
	{
		std::cout << "How many elevators would you like? Between 1 and 50: ";
		std::cin >> NumElevators;
		if (std::cin.fail())
		{
			std::cin.clear(); //This corrects the stream.
			std::cin.ignore(); //This skips the left over stream data.
			std::cout << "\nPlease enter an Integer only.\n";
			validInput = false; //The cin was not an integer so try again
		}
		if (NumElevators > 0 && NumElevators < 51)
		{
			validInput = true;
		}
		else
		{
			std::cout << "\nPlease enter a value between 1 and 50.\n";
		}
	}
	
	BuildingClass Bubilding(NumElevators);
	std::cout << "\n\nRunning Simulation...\n";
	Bubilding.RunSimulation();

	std::cin.get();
	return 0;
}