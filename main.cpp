//****************************************************************
// Andreas Lind, anli1606@student.miun.se
// Project: Train
// Program simulates a day full of train traffic between a couple of
// stations. Wagons and locomotives are initially read from text files
// and stored at the different stations, and then 24 hours of simulation
// data follows where you can follow each vehicles journey
//****************************************************************
#include <iostream>
#include "Locomotive.h"
#include "DieselLoco.h"
#include "ElectroLoco.h"
#include "Vehicle.h"
#include "Sitwagon.h"
#include "Sleepwagon.h"
#include "OpenCargo.h"
#include "ClosedCargo.h"
#include "Station.h"
#include "TrainSimulator.h"
using namespace std;

int main()
{
	TrainSimulator mySim; //create simulation object
	try
	{
		mySim.main(); //run simulation program/menu
	}
	catch (string s)
	{
		cout << s << endl << "... exiting program!" << endl; //verbal info
	}

	cout << endl << "Press any key to quit...";
	cin.get();

}