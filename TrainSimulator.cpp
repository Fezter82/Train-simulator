//--------------------------------------------------------------
//TrainSimulator.cpp
//Definition file of member functions for class TrainSimulator
//Andreas Lind, anli1606@student.miun.se
//--------------------------------------------------------------
#include "TrainSimulator.h"
#include "Time.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <ctype.h>
//***********************************************************************************************
// Default constructor
//***********************************************************************************************
TrainSimulator::TrainSimulator()
{
	currTime = Time(0, 0, 0);
	startTime = Time(0, 0, 0);
	endTime = Time(23, 59, 0);
	outFile = "Trainsim.log";
	interval = 10;

	//   add menuItems to menu-objects
	start = Menu("******    TRAIN SIMULATOR   ******");
	start.addItem("Change start time [00:00]", true);
	start.addItem("Change end time [23:59]", true);
	start.addItem("To simulation", true);
	start.addItem("Exit", true);

	simulation = Menu("****** SIMULATION ******");
	simulation.addItem("Change interval[00:10]", true);
	simulation.addItem("Run next interval", true);
	simulation.addItem("Next event", true);
	simulation.addItem("Finish", true);
	simulation.addItem("Print statistics", false);
	simulation.addItem("Train menu", true);
	simulation.addItem("Station menu", true);
	simulation.addItem("Vehicle menu", true);
	simulation.addItem("Return", true);

	train = Menu("****** TRAIN ******");
	train.addItem("Search train by number", true);
	train.addItem("Search train by vehicle id", true);
	train.addItem("Show all trains", true);
	train.addItem("Return", true);

	station = Menu("****** STATION ******");
	station.addItem("Show station names", true);
	station.addItem("Show station by name", true);
	station.addItem("Return", true);

	vehicle = Menu("****** VEHICLE ******");
	vehicle.addItem("Show vehicle by id", true);
	vehicle.addItem("Show all vehicles", true);
	vehicle.addItem("Change log level [LOW]", true);
	vehicle.addItem("Locate vehicle by ID", true);
	vehicle.addItem("Return", true);


}
//***********************************************************************************************
// Destructor
//***********************************************************************************************
TrainSimulator::~TrainSimulator()
{
	simLog.close();
}
//***********************************************************************************************
// main
// open essential text-files for simulation
// run start menu
//***********************************************************************************************
int TrainSimulator::main()
{
	try //check if all files are open
	{
		openFiles();
	}
	catch (const runtime_error &e)
	{
		cout << e.what() << endl; //verbal info
		throw(string("Crucial file missing. Simulation aborted!"));
		return 0;
	}

	bool again = true;

	try
	{
		do
		{
			start.printMenuItems(); //write start menu

			switch (start.getMenuChoice()) //read menu selection and check that it is a selectable option
			{
			case 1:
				try
				{
					setStartTime(); //if user wants to change start time
				}
				catch (string s)
				{
					cout << endl << s << endl;
				}

				runDarkPreSim(); //run part of simulation in background
				break;
			case 2:
				try
				{
					setEndTime(); //if user wants to change end time
				}
				catch (string s)
				{
					cout << endl << s << endl;
				}
				break;
			case 3:
				simMenu(); //simulations menu
				break;
			case 4:
				again = false;
			}

		} while (again == true);
	}
	catch (string s)
	{
		cout << endl << s << endl;
	}

	return 0;
}
//***********************************************************************************************
// simMenu
// simulations menu
//***********************************************************************************************
void TrainSimulator::simMenu()
{
	bool again = true;
	try
	{
		do
		{
			simulation.printMenuItems();

			switch (simulation.getMenuChoice())
			{
			case 1:
				try
				{
					setInterval(); //if user wants to change interval
				}
				catch (string s)
				{
					cout << endl << s << endl;
				}
				break;
			case 2:
				simulate(1); //step forward in simulation by one interval
				break;
			case 3:
				simulate(2); //step formward in simulation to next event
				break;
			case 4:
				simulate(3); //finish simulation
				break;
			case 5:
				showSimResult(); //show simulation result
				break;
			case 6:
				trainMenu(); //show train menu
				break;
			case 7:
				stationMenu(); // show stations menu
				break;
			case 8:
				vehicleMenu(); //show vehicle menu
				break;
			case 9:
				again = false;
			}

		} while (again == true);
	}
	catch (string s)
	{
		cout << endl << s << endl;
	}
}
//***********************************************************************************************
// trainMenu
// train menu
//***********************************************************************************************
void TrainSimulator::trainMenu()
{
	bool again = true;

	try
	{
		do
		{
			train.printMenuItems();

			switch (train.getMenuChoice())
			{
			case 1:
				trainByNum(); //find train by num(ID)
				break;
			case 2:
				trainByVehID(); //find train by vehicle ID attached to train
				break;
			case 3:
				showAllTrains(); //show all trains
				break;
			case 4:
				again = false;
			}

		} while (again == true);
	}
	catch (string s)
	{
		cout << endl << s << endl;
	}
}
//***********************************************************************************************
// stationMenu
// stations menu
//***********************************************************************************************
void TrainSimulator::stationMenu()
{
	bool again = true;

	try
	{
		do
		{
			station.printMenuItems();

			switch (station.getMenuChoice())
			{
			case 1:
				showStations(); //show all stations
				break;
			case 2:
				showStationByName(); //show station by user chosen name
				break;
			case 3:
				again = false;
			}

		} while (again == true);
	}
	catch (string s)
	{
		cout << endl << s << endl;
	}
}
//***********************************************************************************************
// vehicleMenu
// vehicles menu
//***********************************************************************************************
void TrainSimulator::vehicleMenu()
{
	bool again = true;

	try
	{
		do
		{
			vehicle.printMenuItems();

			switch (vehicle.getMenuChoice())
			{
			case 1:
				vehicleByNum(); //find vehicle by num(ID)
				break;
			case 2:
				try //maybe unnecessary but this is just a safety if user inputs a faulty value in function showAllVehicles()
				{
					showAllVehicles(); //show all vehicles, both attached to trains and in station storages
				}
				catch (string s)
				{
					cout << s << endl;
				}
				break;
			case 3:
				changeLogLevel(); //change the level of detailed information
				break;
			case 4:
				locateVehicle(); //find where vehicle is right now
				break;
			case 5:
				again = false;
			}

		} while (again == true);
	}
	catch (string s)
	{
		cout << endl << s << endl;
	}
}
//***********************************************************************************************
// locateVehicle
// find where vehicle is right now
//***********************************************************************************************
void TrainSimulator::locateVehicle()
{
	int tmp;
	cout << endl << "---- LOCATE VEHICLE BY ID ----" << endl;
	cout << "Enter vehicle ID: ";
	cin >> tmp;

	auto it = find_if(myTrains.begin(), myTrains.end(), [tmp](const Train &obj) {return obj.findVehicle(tmp) == true; });
	if (it != myTrains.end())
	{
		cout << endl << "[";
		showTime(currTime);
		cout << "]";
		cout << " Vehicle " << tmp << " is connected to train " << it->getTrainID() << endl;
	}
	else if (it == myTrains.end())
	{
		auto it2 = find_if(myStations.begin(), myStations.end(), [tmp](const Station &obj) {return obj.findVehicle(tmp) == true; });
		if (it2 != myStations.end())
		{
			cout << endl << "[";
			showTime(currTime);
			cout << "]";
			cout << " Vehicle " << tmp << " is located at train station " << it2->getStationName() << endl;
		}
	}
	else
		cout << endl << "Sorry! There is no vehicle with that ID." << endl;
}
//***********************************************************************************************
// changeLogLevel
// change the level on detail information 
//***********************************************************************************************
void TrainSimulator::changeLogLevel()
{
	if (vehicle.getMenuItemOption(2) == 1)
	{
		vehicle.editMenuItem(2, "Change log level [HIGH]", true); //edit menutItems menutext
		vehicle.setMenuItemOption(2, 2); //edit menuItems option
	}
	else
	{
		vehicle.editMenuItem(2, "Change log level [LOW]", true); //edit menutItems menutext
		vehicle.setMenuItemOption(2, 1); //edit menuItems option
	}
}
//***********************************************************************************************
// showAllVehicles
// show detailed information on vehicles or just short summary
//***********************************************************************************************
void TrainSimulator::showAllVehicles()
{
	int logLevelOption = vehicle.getMenuItemOption(2);

	if (logLevelOption == 2)
	{
		cout << endl << "*** WARNING! ***" << endl << "LOG-level is set to HIGH. Are you sure you want to display full history on all vehicles?" << endl
			<< "Press 'y' for full history" << endl
			<< "Press 'n' for short summary" << endl
			<< "Your choice: ";

		char c;
		cin >> c;
		c = toupper(c);

		cout << endl;

		if (c != 'Y' && c != 'N')
			throw(string("Wrong input! Choices were either 'y' or 'n'"));
		else if (c == 'N')
			logLevelOption = 1;
	}

	//scan through all trains
	for (auto e : myTrains)
	{
		if(e.getNrOfAttachedWagons() > 0)
			e.showVehicleInfo(0, logLevelOption);
	}
	//scan through all stations
	for (auto f : myStations)
	{
		if (f.getNrInStorage() > 0)
			f.showVehicleInfo(0, logLevelOption);
	}
}
//***********************************************************************************************
// vehicleByNum
// find vehicle by ID
//***********************************************************************************************
void TrainSimulator::vehicleByNum()
{
	int tmp;
	cout << endl << "---- SHOW VEHICLE INFO BY ID ----" << endl;
	cout << "Enter vehicle ID: ";	
	cin >> tmp;

	int logLevelOption;

	//check if vehicle is attached to any train
	auto it = find_if(myTrains.begin(), myTrains.end(), [tmp](const Train &obj) {return obj.findVehicle(tmp) == true; });
	if (it != myTrains.end())
	{
		logLevelOption = vehicle.getMenuItemOption(2);
		it->showVehicleInfo(tmp, logLevelOption);
	}
	//check if vehicle is stored at any station
	else if (it == myTrains.end())
	{
		auto it2 = find_if(myStations.begin(), myStations.end(), [tmp](const Station &obj) {return obj.findVehicle(tmp) == true; });
		if (it2 != myStations.end())
		{
			logLevelOption = vehicle.getMenuItemOption(2);
			it2->showVehicleInfo(tmp, logLevelOption);
		}
	}
	else
		cout << endl << "Sorry! There is no vehicle with that ID." << endl;

}
//***********************************************************************************************
// trainByNum
// find train by ID
//***********************************************************************************************
void TrainSimulator::trainByNum()
{
	int tmp;
	cout << endl << "---- FIND TRAIN BY ID ----" << endl;
	cout << "Enter train ID:  ";
	cin >> tmp;

	auto it = find_if(myTrains.begin(), myTrains.end(), [tmp](const Train &obj) {return obj.getTrainID() == tmp; });

	cout << endl << "**********************" << endl;
	cout << "Train information" << endl;
	cout << "**********************" << endl;

	cout << "Train ID: " << it->getTrainID();
	cout << endl << "Origin: " << it->getOrigin();
	cout << endl << "Destination: " << it->getDestination();
	cout << endl << "Departure: " << it->getDeparture();
	cout << endl << "Arrival: " << it->getArrival();
	cout << endl << "Max speed: " << it->getMaxSpeed() << " km/h";

	int count = 1;

	cout << endl << endl << "Train setup:" << endl;
	cout << "------------------------------------" << endl;
	for (auto e : it->getSpecs())
	{
		cout << count << ". ";
		switch (e)
		{
		case 0:
			cout << "Sitwagon" << endl;
			break;
		case 1:
			cout << "Sleepwagon" << endl;
			break;
		case 2:
			cout << "Open cargowagon" << endl;
			break;
		case 3:
			cout << "Closed cargowagon" << endl;
			break;
		case 4:
			cout << "Electrical locomotive" << endl;
			break;
		case 5:
			cout << "Diesel locomotive" << endl;
			break;
		}
		count++;
	}
}
//***********************************************************************************************
// trainByVehID
// find train a train based on attached vehicle(ID)
//***********************************************************************************************
void TrainSimulator::trainByVehID()
{
	int tmp;
	cout << endl << "---- FIND TRAIN BY VEHICLE ID ----" << endl;
	cout << "Enter vehicle ID: ";
	cin >> tmp;

	auto it = find_if(myTrains.begin(), myTrains.end(), [tmp](const Train &obj) {return obj.findVehicle(tmp) == true; });
	if (it != myTrains.end())
	{
		cout << endl << "**********************" << endl;
		cout << "Train information" << endl;
		cout << "**********************" << endl;

		cout << "Vehicle " << tmp << " is connected to: " << endl;

		cout << "Train ID: " << it->getTrainID();
		cout << endl << "Origin: " << it->getOrigin();
		cout << endl << "Destination: " << it->getOrigin();
		cout << endl << "Departure: " << it->getDeparture();
		cout << endl << "Arrival: " << it->getArrival();
		cout << endl << "Max speed: " << it->getMaxSpeed() << " km/h";

		int count = 1;

		cout << endl << "Train setup:" << endl;
		for (auto e : it->getSpecs())
		{
			cout << count << ". ";
			switch (e)
			{
			case 0:
				cout << "Sitwagon" << endl;
				break;
			case 1:
				cout << "Sleepwagon" << endl;
				break;
			case 2:
				cout << "Open cargowagon" << endl;
				break;
			case 3:
				cout << "Closed cargowagon" << endl;
				break;
			case 4:
				cout << "Electrical locomotive" << endl;
				break;
			case 5:
				cout << "Diesel locomotive" << endl;
				break;
			}
			count++;
		}
	}
	else
	{
		cout << endl << "Vehicle " << tmp << " is not connected to any train at the moment! " << endl;
	}

}
//***********************************************************************************************
// showStationByName
// show station by a user chosen name
//***********************************************************************************************
void TrainSimulator::showStationByName()
{
	string tmp;
	cout << endl << "---- FIND STATION ----" << endl;
	cout << "Enter name of station: ";
	cin >> tmp;

	auto it = find_if(myStations.begin(), myStations.end(), [tmp](const Station &obj){return obj.getStationName() == tmp;});

	if (it != myStations.end())
	{
		cout << endl << "**********************" << endl;
		cout << "Station name: " << it->getStationName() << endl;
		cout << "Nr of vehicles in storage: " << it->getNrInStorage();

		cout << endl << endl << "Do you want to display vehicles in storage? [y/n]" << endl;
		char c;
		cin >> c;

		if (c == 'Y' || c == 'y')
		{
			cout << endl << endl << "**********STORAGE**********" << endl;
			it->showStoredVehicles();
		}
	}
	else
		cout << endl << "Sorry, there is no station with that name!" << endl;
}
//***************************************************************************************************
// runDarkPreSim
// This function runs if user chooses start time later than 00:00.
// Simulation is run in background from 00:00 up to users choosen start time
//***************************************************************************************************
void TrainSimulator::runDarkPreSim()
{
	Time now = currTime;
	Time assemble(0, 30, 0);
	Time ready(0, 10, 0);
	Time arrived(0, 20, 0);
	auto it = myTrains.begin();
	int id = 0;
	int allFinished = 0;
	bool again = true;

	sortTimeTable();

	cout << endl << "*** RUNNING SIMULATION FROM TIME [00:00] to [";
	showTime(startTime);
	cout << "] IN BACKGROUND ***" << endl;

	do
	{
		it = myTrains.begin();
		while (it != myTrains.end())
		{
			it = find_if(it, myTrains.end(), [now, assemble, ready, arrived](const Train& obj)
			{	
						//return iterator if any of the following occurs
				return now + assemble > obj.getDeparture() || now + assemble == obj.getDeparture()
					|| now + ready > obj.getDeparture() || now + ready == obj.getDeparture()
					|| now > obj.getDeparture() || now == obj.getDeparture()
					|| now > obj.getArrival() + obj.getArrivalDelay() || now == obj.getArrival() + obj.getArrivalDelay()
					|| now + arrived > obj.getArrival() + obj.getArrivalDelay() || now + arrived == obj.getArrival() + obj.getArrivalDelay();
			});

			if (it != myTrains.end())
			{
				id = it->getTrainID(); //get ID of the train that has an event happening
				//if there is less than 30 minutes until train is supposed to depart
				if ((it->getState() == "NOT ASSEMBLED" || it->getState() == "INCOMPLETE") && (now + assemble > it->getDeparture() || now + assemble == it->getDeparture()))
				{
					if (now < (endTime - assemble))
					{
						assembleTrain(id); //attach vehicles(locomotives and wagons) to train
					}
				}
				//if there is less than 10 minutes until train is supposed to depart
				else if (it->getState() == "ASSEMBLED" && (now + ready > it->getDeparture() || now + ready == it->getDeparture()))
				{
					it->setState("READY");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						simLog << currTime << "Train nr " << it->getTrainID() << " is ready!" << endl;
					}
				}
				//if it is time for train to depart
				else if (it->getState() == "READY" && (now > it->getDeparture() || now == it->getDeparture()))
				{
					it->setState("RUNNING");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						simLog << currTime << "Train nr " << it->getTrainID() << " is running!" << endl;
					}

					try //if no route is found, simulation is corrupted
					{
						runTrain(id); //send the train on its way
					}
					catch (const runtime_error &e)
					{
						cout << e.what() << endl << endl << "... simulation failed!"; //verbal info
						cin.get();
					}
	
				}
				//if train has arrived
				else if (it->getState() == "RUNNING" && (now > (it->getArrival() + it->getArrivalDelay()) || now == (it->getArrival() + it->getArrivalDelay())))
				{
					it->setState("ARRIVED");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						simLog << currTime << "Train " << it->getTrainID() << " has arrived." << endl;
					}

				}
				//if train has arrived and 20 minutes has passed
				else if (it->getState() == "ARRIVED" && (now > (it->getArrival() + it->getArrivalDelay() + arrived) || now == (it->getArrival() + it->getArrivalDelay() + arrived)))
				{
					dismountTrain(id);
					it->setState("FINISHED");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						simLog << currTime << "Train " << it->getTrainID() << " has been dismounted." << endl;
					}

					allFinished++;
					if (allFinished == myTrains.size())
						again = false;
				}
				it++;
			}
		}

		now.ticMin();
		currTime.ticMin();

	} while (now < startTime && again);
}
//***************************************************************************************************
// runDarkPostSim
// if user chooses a different end time than 23:59, this function runs the remaining time of the day
// in the background
//***************************************************************************************************
void TrainSimulator::runDarkPostSim()
{
	Time now = currTime;
	Time assemble(0, 30, 0);
	Time ready(0, 10, 0);
	Time arrived(0, 20, 0);
	Time end(23, 59, 0);
	auto it = myTrains.begin();
	int id = 0;
	int allFinished = 0;
	bool again = true;

	while (again && !(currTime == end))
	{
		it = myTrains.begin();
		while (it != myTrains.end())
		{
			it = find_if(it, myTrains.end(), [now, assemble, ready, arrived](const Train& obj)
			{		//return iterator if any of the following occurs
				return now + assemble > obj.getDeparture() || now + assemble == obj.getDeparture()
					|| now + ready > obj.getDeparture() || now + ready == obj.getDeparture()
					|| now > obj.getDeparture() || now == obj.getDeparture()
					|| now > obj.getArrival() + obj.getArrivalDelay() || now == obj.getArrival() + obj.getArrivalDelay()
					|| now + arrived > obj.getArrival() + obj.getArrivalDelay() || now + arrived == obj.getArrival() + obj.getArrivalDelay();
			});

			if (it != myTrains.end())
			{
				id = it->getTrainID();//get ID of the train that has an event happening
				//if there is less than 30 minutes until train is supposed to depart
				if ((it->getState() == "NOT ASSEMBLED" || it->getState() == "INCOMPLETE") && (now + assemble > it->getDeparture() || now + assemble == it->getDeparture()))
				{
					if (now < (end - assemble))
					{
						assembleTrain(id); //attach vehicles to train
					}
				}
				//if there is less than 10 minutes until train is supposed to depart
				else if (it->getState() == "ASSEMBLED" && (now + ready > it->getDeparture() || now + ready == it->getDeparture()))
				{
					it->setState("READY");
					simLog << currTime << "Train nr " << it->getTrainID() << " is ready!" << endl;

				}
				//if it is time for train to depart
				else if (it->getState() == "READY" && (now > it->getDeparture() || now == it->getDeparture()))
				{
					it->setState("RUNNING");
					simLog << currTime << "Train nr " << it->getTrainID() << " is running!" << endl;

					try
					{
						runTrain(id); //send train on its way
					}
					catch (const runtime_error &e)
					{
						cout << e.what() << endl << endl << "... simulation failed!"; //verbal info
						cin.get();
					}
				}
				//if train has arrived
				else if (it->getState() == "RUNNING" && (now > (it->getArrival() + it->getArrivalDelay()) || now == (it->getArrival() + it->getArrivalDelay())))
				{
					it->setState("ARRIVED");
					simLog << currTime << "Train " << it->getTrainID() << " has arrived." << endl;
				
				}
				//if train has arrived and 20 minutes has passed
				else if (it->getState() == "ARRIVED" && (now > (it->getArrival() + it->getArrivalDelay() + arrived) || now == (it->getArrival() + it->getArrivalDelay() + arrived)))
				{
					dismountTrain(id);
					it->setState("FINISHED");

					simLog << currTime << "Train " << it->getTrainID() << " has been dismounted." << endl;

					allFinished++;
					if (allFinished == myTrains.size())
						again = false;
				}
				it++;
			}
		}

		now.ticMin();
		currTime.ticMin();

		if (currTime == end)
		{
			again = false;
		}

	}

	//run the check for day 2 to find if any trains are RUNNING or ARRIVED past 00:00
	Time newDay(24, 0, 0);
	now.ticMin();
	currTime.ticMin();

	//Check how many trains there are left out there
	int trainsLeft = 0;
	trainsLeft = count_if(myTrains.begin(), myTrains.end(), [](const Train& obj) { return obj.getState() == "RUNNING" || obj.getState() == "ARRIVED"; });
	again = true;

	while (now < end && again)
	{
		it = myTrains.begin();
		while (it != myTrains.end())
		{
			it = find_if(it, myTrains.end(), [now, assemble, newDay, arrived](const Train& obj)
			{		//return iterator if any of the following occurs
				return obj.getState() == "RUNNING" && (now + newDay >(obj.getArrival() + obj.getArrivalDelay()) || now + newDay == (obj.getArrival() + obj.getArrivalDelay()))
					|| obj.getState() == "ARRIVED" && (now + newDay > (obj.getArrival() + obj.getArrivalDelay() + arrived) || now + newDay == (obj.getArrival() + obj.getArrivalDelay() + arrived))
					; });

			if (it != myTrains.end())
			{
				id = it->getTrainID();
				//if train has arrived
				if (it->getState() == "RUNNING" && (now + newDay > (it->getArrival() + it->getArrivalDelay()) || now + newDay == (it->getArrival() + it->getArrivalDelay())))
				{
					it->setState("ARRIVED");
					simLog << currTime << "Train " << it->getTrainID() << " has arrived." << endl;

				}
				//if train has arrived and 20 minutes has passed
				else if (it->getState() == "ARRIVED" && (now + newDay > (it->getArrival() + it->getArrivalDelay() + arrived) || now + newDay == (it->getArrival() + it->getArrivalDelay() + arrived)))
				{
					dismountTrain(id);
					it->setState("FINISHED");

					simLog << currTime << "Train " << it->getTrainID() << " has been dismounted." << endl;
					trainsLeft--;
				}
				it++;
			}
		}

		now.ticMin();
		currTime = now;

		if (trainsLeft == 0)
		{
			again = false;

			//disable menuoptions that would make it possible for simulation to restart
			for (int i = 0; i < 3; i++)
				start.disable(i);
			for (int i = 0; i < 4; i++)
				simulation.disable(i);

			simulation.setAvailable(4);
			//showSimResult(); //when simulation is finished
		}
	}
}
//***************************************************************************************************
// simulate
// pOpt = 1 --> run next interval. pOpt = 2 --> run until next event, pOpt = 3 --> finish simulation
//***************************************************************************************************
int TrainSimulator::simulate(int pOpt)
{
	Time now = currTime;
	Time assemble(0, 30, 0);
	Time ready(0, 10, 0);
	Time arrived(0, 20, 0);
	auto it = myTrains.begin();
	int id = 0;
	int allFinished = 0;
	int tmpInterval = getInterval();
	bool again = true;
	bool runNewDay = true;

	sortTimeTable();

	do
	{
		it = myTrains.begin();
		while (it != myTrains.end())
		{
			it = find_if(it, myTrains.end(), [now, assemble, ready, arrived](const Train& obj)
			{		//return iterator if any of the following occurs
				return now + assemble > obj.getDeparture() || now + assemble == obj.getDeparture()
					|| now + ready > obj.getDeparture() || now + ready == obj.getDeparture()
					|| now > obj.getDeparture() || now == obj.getDeparture()
					|| now > obj.getArrival() + obj.getArrivalDelay() || now == obj.getArrival() + obj.getArrivalDelay()
					|| now + arrived > obj.getArrival() + obj.getArrivalDelay() || now + arrived == obj.getArrival() + obj.getArrivalDelay();
			});

			if (it != myTrains.end())
			{
				id = it->getTrainID(); //get ID of the train that has an event happening
				
				//if there is less than 30 minutes until train is supposed to depart
				if ((it->getState() == "NOT ASSEMBLED" || it->getState() == "INCOMPLETE") && (now + assemble > it->getDeparture() || now + assemble == it->getDeparture()))
				{
					if (now < (endTime-assemble))
					{
						assembleTrain(id); //attach vehicles to train
						if (pOpt == 2)
							return 0;
					}
				}
				//if there is less than 10 minutes until train is supposed to depart
				else if (it->getState() == "ASSEMBLED" && (now + ready > it->getDeparture() || now + ready == it->getDeparture()))
				{
					it->setState("READY");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						cout << "[";
						showTime(currTime);
						cout << "]";
						cout << " - Train nr " << it->getTrainID() << " is ready!" << endl;
						simLog << currTime << "Train nr " << it->getTrainID() << " is ready!" << endl;
					}
					if (pOpt == 2)
						return 0;
				}
				//if it is time for train to depart
				else if (it->getState() == "READY" && (now > it->getDeparture() || now == it->getDeparture()))
				{
					it->setState("RUNNING");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						cout << "[";
						showTime(currTime);
						cout << "]";
						cout << " - Train nr " << it->getTrainID() << " is running!" << endl;
						simLog << currTime << "Train nr " << it->getTrainID() << " is running!" << endl;
					}

					try
					{
						runTrain(id); //send train on its way
					}
					catch (const runtime_error &e)
					{
						cout << e.what() << endl << endl << "... simulation failed!"; //verbal info
						cin.get();
					}
					if (pOpt == 2)
						return 0;
				}
				//if train has arrived
				else if (it->getState() == "RUNNING" && (now > (it->getArrival() + it->getArrivalDelay()) || now == (it->getArrival() + it->getArrivalDelay())))
				{
					it->setState("ARRIVED");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						cout << "[";
						showTime(currTime);
						cout << "]";
						cout << " - Train " << it->getTrainID() << " has arrived." << endl;
						simLog << currTime << "Train " << it->getTrainID() << " has arrived." << endl;
					}
					if (pOpt == 2)
						return 0;

				}
				//if train has arrived and 20 minutes has passed
				else if (it->getState() == "ARRIVED" && (now > (it->getArrival() + it->getArrivalDelay() + arrived) || now == (it->getArrival() + it->getArrivalDelay() + arrived)))
				{
					dismountTrain(id);
					it->setState("FINISHED");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						cout << "[";
						showTime(currTime);
						cout << "]";
						cout << " - Train " << it->getTrainID() << " has been dismounted." << endl;
						simLog << currTime << "Train " << it->getTrainID() << " has been dismounted." << endl;
					}

					if (pOpt == 2)
						return 0;

					allFinished++;
				}
				it++;
			}
		}

		now.ticMin();
		currTime.ticMin();


			if (pOpt == 1)
			{
				tmpInterval--;
				if (tmpInterval == 0)
				{						//print what time it is right now
					cout << "--------------------------------";
					cout << endl << "Time is now: ";
					showTime(currTime);
					cout << endl << "--------------------------------";
					return 0;
				}
			}
			//runs checks to see if its time to stop looping
			if (allFinished == myTrains.size()) //if all trains are finished
			{
				again = false;
				for (int i = 0; i < 3; i++)
					start.disable(i);
				for (int i = 0; i < 4; i++)
					simulation.disable(i);

				simulation.setAvailable(4);
			}
			if (currTime == endTime) //if endtime of simulation is reached
			{
				Time tmp(23, 59, 0);
				if (endTime < tmp)
				{
					runDarkPostSim(); //run rest of day in background if user wants an earlier stop time than standard 23:59
					runNewDay = false;
				}
				again = false;
				//disable menuoptions that would make it possible for simulation to restart
				for (int i = 0; i < 3; i++)
					start.disable(i);
				for (int i = 0; i < 4; i++)
					simulation.disable(i);

				simulation.setAvailable(4);
			}

	} while (now < endTime && again);


	//************************************************************************************
	//run the same check for day 2 to find if any trains are RUNNING or ARRIVED past 00:00
	//************************************************************************************

	Time newDay(24, 0, 0);
	now.ticMin();
	startTime.setHour(0);
	startTime.setMinute(0);
	currTime.ticMin();
	tmpInterval = getInterval();

	//Check how many trains there are left out there
	int trainsLeft = 0;
	trainsLeft = count_if(myTrains.begin(), myTrains.end(),[](const Train& obj){ return obj.getState() == "RUNNING" || obj.getState() == "ARRIVED";});

	again = true;

	while (now < endTime && runNewDay && again && trainsLeft > 0)
	{
		it = myTrains.begin();
		while (it != myTrains.end())
		{
			it = find_if(it, myTrains.end(), [now, assemble, newDay, arrived](const Train& obj)
			{
				return obj.getState() == "RUNNING" && (now + newDay > (obj.getArrival() + obj.getArrivalDelay()) || now + newDay == (obj.getArrival() + obj.getArrivalDelay()))
					|| obj.getState() == "ARRIVED" && (now + newDay > (obj.getArrival() + obj.getArrivalDelay() + arrived) || now + newDay == (obj.getArrival() + obj.getArrivalDelay() + arrived))
			;});

			if (it != myTrains.end())
			{
				id = it->getTrainID();

				if (it->getState() == "RUNNING" && (now + newDay > (it->getArrival() + it->getArrivalDelay()) || now + newDay == (it->getArrival() + it->getArrivalDelay())))
				{
					it->setState("ARRIVED");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						cout << "[";
						showTime(currTime);
						cout << "]";
						cout << " - Train " << it->getTrainID() << " has arrived." << endl;
						simLog << currTime << "Train " << it->getTrainID() << " has arrived." << endl;
					}

					if (pOpt == 2)
						return 0;
		
				}
				else if (it->getState() == "ARRIVED" && (now + newDay > (it->getArrival() + it->getArrivalDelay() + arrived) || now + newDay == (it->getArrival() + it->getArrivalDelay() + arrived)))
				{
					dismountTrain(id);
					it->setState("FINISHED");

					if ((now > startTime || now == startTime) && (now < endTime || now == endTime))
					{
						cout << "[";
						showTime(currTime);
						cout << "]";
						cout << " - Train " << it->getTrainID() << " has been dismounted." << endl;
						simLog << currTime << "Train " << it->getTrainID() << " has been dismounted." << endl;
						trainsLeft--;
					}

					if (pOpt == 2)
						return 0;

				}
				it++;
			}
		}

		now.ticMin();
		currTime = now;

		if (trainsLeft == 0)
		{
			again = false;

			//disable menuoptions that would make it possible for simulation to restart
			for (int i = 0; i < 3; i++)
				start.disable(i);
			for (int i = 0; i < 4; i++)
				simulation.disable(i);

			simulation.setAvailable(4);
		}

		if (pOpt == 1)
		{
			tmpInterval--;
			if (tmpInterval == 0)
			{
				cout << "--------------------------------";
				cout << endl << "Time is now: ";
				showTime(currTime);
				cout << endl << "--------------------------------";
				return 0;
			}
		}
	} 

	showSimResult(); //when simulation is finished
	return 0;
}
//***********************************************************************************************
// showSimResult
//***********************************************************************************************
void TrainSimulator::showSimResult()
{
	cout << endl << endl << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "           FINAL SIMULATION RESULTS" << endl;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;

	cout << "****************************************" << endl;
	cout << "Trains arrived:" << endl;
	cout << "****************************************" << endl;
	for (auto idx : myTrains)
	{
		if (idx.getState() == "FINISHED")
		{
			cout << endl << "Train " << idx.getTrainID() << endl;
			cout << "Departed: ";
			showTime(idx.getDeparture());
			cout << " ("; 
			showTime(idx.getDeparture() - idx.getDelay());
			cout << ")";
			cout << endl << "Arrived: ";
			showTime(idx.getArrival() + idx.getArrivalDelay());
			cout << " (";
			showTime(idx.getArrival());
			cout << ")";
			if (idx.getDelay().getHour() > 0 || idx.getDelay().getMinute() > 0)
			{
				cout << endl << "Delay on departure: ";
				showTime(idx.getDelay());
			}
			else
			{
				cout << endl << "Train departed on time!";
			}
			if (idx.getArrivalDelay().getHour() > 0 || idx.getArrivalDelay().getMinute() > 0)
			{
				cout << endl << "Delay on arrival: ";
				showTime(idx.getArrivalDelay());
			}
			else
			{
				cout << endl << "Train arrived on time!";
			}
			cout << endl;
			cout << "Average speed: ";
			
			int distance = 0;
			auto mapIdx = trainMap.find(idx.getDestination() + idx.getOrigin());

			if (mapIdx != trainMap.end())
			{
				distance = mapIdx->second;
			}
			Time tmp = (idx.getArrival() + idx.getArrivalDelay()) - idx.getDeparture();
			int hours = tmp.getHour();
			double mins = double(tmp.getMinute()) / 60;
			cout << int(distance / double(hours + mins)) << " km/h" << endl;

		}
	}

	cout << endl << "****************************************" << endl;
	cout << "Trains that never left the station:" << endl;
	cout << "****************************************" << endl;
	for (auto idx : myTrains)
	{
		if (idx.getState() == "INCOMPLETE")
		{
			cout << "-------------------------------------------";
			cout << endl << "Train " << idx.getTrainID() << " from " << idx.getOrigin() << " to " << idx.getDestination() << endl;
			cout << "-------------------------------------------" << endl;
			cout << "    *** ATTACHED VEHICLES ***   " << endl << endl;
			idx.showVehicleInfo(0, 1);
			cout << "    *** MISSING VEHICLES ***    " << endl << endl;

			int i = idx.getNrOfAttachedWagons();
			vector<int> tmp = idx.getSpecs();

			for (i; i < tmp.size(); i++)
			{
				switch (tmp[i])
				{
				case 0:
					cout << "Sitwagon" << endl;
					break;
				case 1:
					cout << "Sleepwagon" << endl;
					break;
				case 2:
					cout << "Open cargowagon" << endl;
					break;
				case 3:
					cout << "Closed cargowagon" << endl;
					break;
				case 4:
					cout << "Electrical locomotive" << endl;
					break;
				case 5:
					cout << "Diesel locomotive" << endl;
					break;
				}
			}
			cout << endl;
		}
	}

	//create a couple of Time objects to help calculate results
	Time test;
	Time totalDepDelay;
	Time totalArrDelay;

	cout << endl << "****************************************" << endl;
	cout << "Trains delayed:" << endl;
	cout << "****************************************" << endl;
	for (auto idx : myTrains)
	{
		if (idx.getState() == "FINISHED")
		{
			if (idx.getArrivalDelay() > test || idx.getDelay() > test)
			{
				cout << "Train " << idx.getTrainID();
				cout << endl << "Delay on departure: ";
				showTime(idx.getDelay());
				cout << endl << "Delay on arrival: ";
				showTime(idx.getArrivalDelay());
				cout << endl;
				cout << "------------------------------" << endl;
				totalDepDelay = totalDepDelay + idx.getDelay();
				totalArrDelay = totalArrDelay + idx.getArrivalDelay();
			}
		}
	}
	cout << endl << "****************************************" << endl;
	cout << "TOTAL DELAYS" << endl;
	cout << "****************************************" << endl;
	cout << "Delay on departures: "; 
	cout << totalDepDelay.getHour() << " hours " << totalDepDelay.getMinute() << " minutes";
	cout << endl << "Delay on arrivals: ";
	cout << totalArrDelay.getHour() << " hours " << totalArrDelay.getMinute() << " minutes";
	cout << endl << "****************************************" << endl;
}
//***********************************************************************************************
// sortTimeTable
// Sort timetable by earliest departure
//***********************************************************************************************
void TrainSimulator::sortTimeTable()
{
	sort(myTrains.begin(), myTrains.end(), [](Train &a, Train &b) {return a.getDeparture() < b.getDeparture(); });
}

//***********************************************************************************************
// assembleTrain
// attach vehicles to train
//***********************************************************************************************
void TrainSimulator::assembleTrain(int id) 
{
	auto it = myTrains.begin();
	it = find_if(myTrains.begin(), myTrains.end(), [id](const Train& obj) {return obj.getTrainID() == id; }); //find the train with ID = id

	vector<int> Specs; 
	Specs = it->getSpecs(); //get train specification ie which types of vehicles should be attached
	int nrOfWagons = Specs.size(); //get how many vehicles that should be attached to train
	int wagonsAttached = it->getNrOfAttachedWagons(); //get how many vehicles that are attached to train

	string station = it->getOrigin(); //find out which station the train is travelling from

	auto it2 = myStations.begin();
	it2 = find_if(myStations.begin(), myStations.end(), [station](const Station& obj) {return obj.getStationName() == station; }); //set iterator to that station
	it2->sortStorage(); //sort stored vehicles in storage based by vehicle ID
	
	shared_ptr<Vehicle> tmpPtr; //create shared_ptr to soon point to new vehicle to be attached to train
	bool again = true;

	do
	{
		tmpPtr.reset(); //reset pointer
		if (it2->releaseVehicle(Specs[wagonsAttached], tmpPtr)) //if vehicle was found in station
		{
				//print information on what is occuring. This code is unnecessary duplicated which I realized while commenting afterwards, but it still works
			if ((currTime > startTime || currTime == startTime) && (currTime < endTime || currTime == endTime))
			{
				cout << "[";
				showTime(currTime);
				cout << "]";
				cout << " - Wagon " << tmpPtr->getID();
				switch (tmpPtr->getType())
				{
				case 0:
					cout << "[Sitwagon] ";
					break;
				case 1:
					cout << "[Sleepwagon] ";
					break;
				case 2:
					cout << "[Open Cargowagon] ";
					break;
				case 3:
					cout << "[Closed Cargowagon] ";
					break;
				case 4:
					cout << "[E-locomotive] ";
					break;
				case 5:
					cout << "[D-locomotive] ";
					break;
				}
				cout << "was disconnected from train pool at station " << it2->getStationName() << endl;
				tmpPtr->addHistory("[" + to_string(currTime.getHour()) + ":" + to_string(currTime.getMinute()) + "]" + " " + "Disconnected from train pool at station " + it2->getStationName());
				
				simLog << currTime << "Wagon " << tmpPtr->getID();
				switch (tmpPtr->getType())
				{
				case 0:
					simLog << "[Sitwagon] ";
					break;
				case 1:
					simLog << "[Sleepwagon] ";
					break;
				case 2:
					simLog << "[Open Cargowagon] ";
					break;
				case 3:
					simLog << "[Closed Cargowagon] ";
					break;
				case 4:
					simLog << "[E-locomotive] ";
					break;
				case 5:
					simLog << "[D-locomotive] ";
					break;
				}
				simLog << "was disconnected from train pool at station " << it2->getStationName() << endl;
			}


			if (it->addVehicle(tmpPtr)) //if vehicle could be attached to train
			{
				if ((currTime > startTime || currTime == startTime) && (currTime < endTime || currTime == endTime))
				{
					cout << "[";
					showTime(currTime);
					cout << "]";
					cout << " - Wagon " << tmpPtr->getID();
					switch (tmpPtr->getType())
					{
					case 0:
						cout << "[Sitwagon] ";
						break;
					case 1:
						cout << "[Sleepwagon] ";
						break;
					case 2:
						cout << "[Open Cargowagon] ";
						break;
					case 3:
						cout << "[Closed Cargowagon] ";
						break;
					case 4:
						cout << "[E-locomotive] ";
						break;
					case 5:
						cout << "[D-locomotive] ";
						break;
					}
					cout << "was connected to " << "train " << it->getTrainID() << endl;

					simLog << currTime << "Wagon ";
					switch (tmpPtr->getType())
					{
					case 0:
						simLog << "[Sitwagon] ";
						break;
					case 1:
						simLog << "[Sleepwagon] ";
						break;
					case 2:
						simLog << "[Open Cargowagon] ";
						break;
					case 3:
						simLog << "[Closed Cargowagon] ";
						break;
					case 4:
						simLog << "[E-locomotive] ";
						break;
					case 5:
						simLog << "[D-locomotive] ";
						break;
					}
					simLog << tmpPtr->getID() << "was connected to " << "train " << it->getTrainID() << endl;
					tmpPtr->addHistory("[" + to_string(currTime.getHour()) + ":" + to_string(currTime.getMinute()) + "]" + " " + "Connected to train " + to_string(it->getTrainID()));
				}

				wagonsAttached++; //add nr of attached vehicles to train
			}
			else
				again = false;
		}
		else
			again = false;

	} while ((wagonsAttached < nrOfWagons && again));

	if (wagonsAttached == nrOfWagons) //if true, all vehicles have been succesfullt added to train
	{
		it->setState("ASSEMBLED");
		if ((currTime > startTime || currTime == startTime) && (currTime < endTime || currTime == endTime))
		{
			cout << "[";
			showTime(currTime);
			cout << "]";
			cout << " - Train nr " << it->getTrainID() << " was assembled!" << endl;
			simLog << currTime << "Train nr " << it->getTrainID() << " was assembled!" << endl;
		}
		
	}

	else if (wagonsAttached < nrOfWagons) //if true, all vehicles could not be added to train so train is delayed
	{
		if ((currTime > startTime || currTime == startTime) && (currTime < endTime || currTime == endTime))
		{
			cout << "[";
			showTime(currTime);
			cout << "]";
			cout << " - Train nr " << it->getTrainID() << " has been delayed" << endl;
			simLog << currTime << "Train nr " << it->getTrainID() << " was delayed" << endl;
		}
		it->setState("INCOMPLETE");
		it->delayDeparture();
	}

}
//***********************************************************************************************
// runTrain
// simulates train running from origin to destination
//***********************************************************************************************
void TrainSimulator::runTrain(int id)
{
	auto it = myTrains.begin();
	it = find_if(myTrains.begin(), myTrains.end(), [id](const Train& obj) {return obj.getTrainID() == id; });

	int distance = 0;
	auto mapIdx = trainMap.find(it->getDestination() + it->getOrigin()); //find if string destination+origin exists in trainMap

	if (mapIdx != trainMap.end())
	{
		distance = mapIdx->second; //set associated value to distance
	}
	else
		throw runtime_error("Route was not found in TrainMap"); //if route could not be found, simulation is corrupted

	int speedCheck = it->getMaxSpeed(); //get maxspeed of train(route)

	//check if attached locomotives can reach maximum speed of train route
	if (it->returnHighLocoSpeed() < speedCheck)
		speedCheck = it->returnHighLocoSpeed(); //if not, max speed is set to fastest locomotive in train set

	double tmpTime = 0.0;
	tmpTime = (double)distance / (double)speedCheck; //calculate how long time travel will take
	
	Time travelTime;
	travelTime.setTimeFromDouble(tmpTime);

	if (it->getDeparture() + travelTime > it->getArrival()) //if departure + traveltime will pass expected arrival time means that train is delayed on arrival
	{
		//set arrivalDelay
		Time tmp = (it->getDeparture() + travelTime) - it->getArrival();
		it->setArrivalDelay(tmp);
	}
}
//***********************************************************************************************
// dismountTrain
// release vehicles from train and put in storage at destination station
//***********************************************************************************************
void TrainSimulator::dismountTrain(int id)
{
	auto it = myTrains.begin();
	it = find_if(myTrains.begin(), myTrains.end(), [id](const Train& obj) {return obj.getTrainID() == id; });

	int nrOfWagons = it->getNrOfAttachedWagons();

	string station = it->getDestination(); //find out which station the train is travelling to

	auto it2 = myStations.begin();
	it2 = find_if(myStations.begin(), myStations.end(), [station](const Station& obj) {return obj.getStationName() == station; }); //set iterator to that station
	it2->sortStorage();

	shared_ptr<Vehicle> tmpPtr; //create shared_ptr to soon point to new vehicle to be stored
	bool again = true;

	for (int i = 0; i < nrOfWagons; i++)
	{
		tmpPtr.reset(); //reset pointer

		if (it->releaseVehicle(tmpPtr)) //if vehicle could be released from train
		{
			if ((currTime > startTime || currTime == startTime) && (currTime < endTime || currTime == endTime))
			{
				cout << "[";
				showTime(currTime);
				cout << "]";
				cout << " - Wagon " << tmpPtr->getID();
				switch (tmpPtr->getType())
				{
				case 0:
					cout << "[Sitwagon] ";
					break;
				case 1:
					cout << "[Sleepwagon] ";
					break;
				case 2:
					cout << "[Open Cargowagon] ";
					break;
				case 3:
					cout << "[Closed Cargowagon] ";
					break;
				case 4:
					cout << "[E-locomotive] ";
					break;
				case 5:
					cout << "[D-locomotive] ";
					break;
				}
				cout << "was disconnected from train " << it->getTrainID();
				tmpPtr->addHistory("[" + to_string(currTime.getHour()) + ":" + to_string(currTime.getMinute()) + "]" + " " + "Disconnected from train " + to_string(it->getTrainID()));
				
				simLog << currTime << "Wagon " << tmpPtr->getID();
				switch (tmpPtr->getType())
				{
				case 0:
					simLog << "[Sitwagon] ";
					break;
				case 1:
					simLog << "[Sleepwagon] ";
					break;
				case 2:
					simLog << "[Open Cargowagon] ";
					break;
				case 3:
					simLog << "[Closed Cargowagon] ";
					break;
				case 4:
					simLog << "[E-locomotive] ";
					break;
				case 5:
					simLog << "[D-locomotive] ";
					break;
				}
				simLog << "was disconnected from train " << it->getTrainID();
			}
		}
		if (it2->addVehicle(tmpPtr)) //if vehicle could be stored at station
		{
			if ((currTime > startTime || currTime == startTime) && (currTime < endTime || currTime == endTime))
			{
				cout << " and put in storage at " << it2->getStationName() << "-station." << endl;
				tmpPtr->addHistory("[" + to_string(currTime.getHour()) + ":" + to_string(currTime.getMinute()) + "]" + " " + "Connected to station pool at " + it2->getStationName());
				simLog << currTime << " and put in storage at " << it2->getStationName() << "-station." << endl;
			}
		}
	}
	

}
//***********************************************************************************************
// openFiles
// open out- and in files neccessary for simulation
//***********************************************************************************************
bool TrainSimulator::openFiles()
{
	simLog.open(outFile); //open logfile
	if (!simLog.is_open())
	{
		throw runtime_error("Could not create logfile");
		return false;
	}
	if (!readStationsFile("TrainStations.txt")) //read all stations
	{
		throw runtime_error("Could not open TrainStations.txt");
		return false;
	}
	if (!readTrainsFile("Trains.txt")) //read all trains
	{
		throw runtime_error("Could not open Trains.txt");
		return false;
	}
	if (!readMapFile("TrainMap.txt")) //read all routes and distances
	{
		throw runtime_error("Could not open TrainMap.txt");
		return false;
	}

	return true;
}
//***********************************************************************************************
// readStationsFile
// read all stations
//***********************************************************************************************
bool TrainSimulator::readStationsFile(string pFile)
{
	ifstream inFile(pFile, ios::in);

	Station tmpStation;

	if (!inFile.is_open())
		return false;

	while (inFile >> tmpStation)
	{
		myStations.push_back(tmpStation);
	}

	myStations.push_back(tmpStation);
	inFile.close();
	
	return true;
}
//***********************************************************************************************
// readTrainsFile
// read all trains
//***********************************************************************************************
bool TrainSimulator::readTrainsFile(string pFile)
{
	fstream inFile(pFile, ios::in);

	Train tmpTrain;

	if (!inFile.is_open())
		return false;

	while (!inFile.eof())
	{
		inFile >> tmpTrain;
		myTrains.push_back(tmpTrain);
	}
	inFile.close();
	
	return true;
}
//***********************************************************************************************
// readMapFile
// read all routes and distances
//***********************************************************************************************
bool TrainSimulator::readMapFile(string pFile)
{
	fstream inFile(pFile, ios::in);

	if (!inFile.is_open())
		return false;

	string tmp1, tmp2;
	int distance = 0;

	while (!inFile.eof())
	{
		getline(inFile, tmp1, ' ');
		getline(inFile, tmp2, ' ');
		inFile >> distance;
		inFile.get();
		trainMap[tmp1 + tmp2] = distance;
		trainMap[tmp2 + tmp1] = distance;

	}
	inFile.close();

	return true;
}
//***********************************************************************************************
// showAllTrains
//***********************************************************************************************
void TrainSimulator::showAllTrains()
{
	for (auto e : myTrains)
	{
		cout << "Train: " << e.getTrainID() << endl;
		cout << e.getOrigin() << " to " << e.getDestination() << endl;
		cout << "Departure: "; 
		showTime(e.getDeparture()); 
		cout << endl << "Arrival: ";
		showTime(e.getArrival());
		cout << endl << "----------------------------------------------------" << endl;
	}
}
//***********************************************************************************************
// showStations
//***********************************************************************************************
void TrainSimulator::showStations()
{
	cout << "*******************************" << endl;
	for (auto e : myStations)
	{
		cout << "Station: " << e.getStationName() << endl;
		cout << "-------------------------------------" << endl;
		//e.showStoredVehicles();
	}
}
//***********************************************************************************************
// setStartTime
// if user wants to change start time for simulation
//***********************************************************************************************
void TrainSimulator::setStartTime()
{
	int hour = 0, min = 0;

	cout << "Set starting hour: ";
	cin >> hour;
	cout << "Set starting minute: ";
	cin >> min;

	if (hour < 0 || hour > 23 || min < -1 || min > 60)
		throw(string("The specified time was incorrect!!"));

	startTime.setHour(hour);
	startTime.setMinute(min);
}
//***********************************************************************************************
// setEndTime
// if user wants to change end time for simulation
//***********************************************************************************************
void TrainSimulator::setEndTime()
{
	int hour = 0, min = 0;

	cout << "Set ending hour: ";
	cin >> hour;
	cout << "Set ending minute: ";
	cin >> min;

	if (hour < 0 || hour > 23 || min < -1 || min > 60)
		throw(string("The specified time was incorrect!!"));

	endTime.setHour(hour);
	endTime.setMinute(min);
}
//***********************************************************************************************
// setInterval
// if user wants to change duration of the intervals of simulation
//***********************************************************************************************
void TrainSimulator::setInterval()
{
	int temp = 0;

	cout << "Set interval [min]: ";
	cin >> temp;

	if (temp > 60)
		throw(string("Interval can maximum be 60 minutes!!"));

	simulation.editMenuItem(0, "Change interval[00:"+to_string(temp)+"]", true);

	interval = temp;
}