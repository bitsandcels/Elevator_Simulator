# Elevator_Simulator
An elevator simulator that devlivers 400 pasengers in a 5 story building.


The user is asked to input the number of elevators they wish to use (between 1 and 50) and the simulation runs.
It outputs the current number of the simulation it is currently working on. 
The user will be given two .cvs containing the following data: the information for one simulation run and
the average data for each simulation run. The elevators can only load passengers from the first floor and
deleliver passangers at their destination floors. 

The project uses a random number generator to assign arrival times for each passenger as well as an array
shuffle to assign each passenger a destination floor. The elevator uses two queues, one to add passengers 
to the elevator and one to form the elevator's line. 
