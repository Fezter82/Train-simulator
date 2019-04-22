//************************************************************************
// TrainSimulator.H
// TrainSimulator class creates an object holding all types of objects and 
// functions necessary for simulation
//************************************************************************
#ifndef TrainSimulatorH
#define TrainSimulatorH
#include "Station.h"
#include "Train.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <map>
#include "Time.h"
#include "Menu.h"

using namespace std;

class TrainSimulator
{
private:
	vector<Station> myStations; //all train stations in simulation
	vector<Train> myTrains; //all trains in simulation
	map<string, int> trainMap; //store distances between stations
	Menu start, train, station, vehicle, simulation;
	Time currTime, startTime, endTime;
	int interval; //used when simulation should stop at certain intervals
	ofstream simLog; //save all events regarding vehicles
	string outFile;

public:
	//--------------------------------------Constructor
	TrainSimulator();
	//--------------------------------------Destructor
	~TrainSimulator();

	int main(); //open files, run start menu

	//--------------------------------------Menus
	void simMenu();
	void trainMenu();
	void stationMenu();
	void vehicleMenu();

	//-----------------------------------------------------------Miscellaneous
	int simulate(int pOpt); //runs main simulation process
	void runDarkPreSim(); //if starting time is set later than 00:00, runDarkPreSim runs in the background before main simulation
	void runDarkPostSim(); //if ending time is set earlier than 23:59, runDarkPostSim runs in the background after main simulation
	void sortTimeTable(); //sort time table so that train with earliest departure comes first
	void assembleTrain(int id); //attach vehicles to trains
	void runTrain(int id); //runs train
	void dismountTrain(int id); //dismount train, store vehicles at station
	void changeLogLevel(); //sets level of detailed information

	//--------------------------------------Set functions
	void setStartTime();
	void setEndTime();
	void setInterval();

	//--------------------------------------Get functions
	Time getTime() const { return currTime; }
	Time getStartTime() const { return startTime; }
	Time getEndTime() const { return endTime; }
	int getInterval() const { return interval; }

	//--------------------------------------File functions
	bool openFiles(); //runs the following three file functions
	bool readStationsFile(string pFile);
	bool readTrainsFile(string pFile);
	bool readMapFile(string pFile);
	
	//--------------------------------------Find functions
	void trainByNum();
	void trainByVehID();
	void vehicleByNum();
	void locateVehicle();

	//--------------------------------------Show functions
	void showSimResult();
	void showAllTrains();
	void showAllVehicles();
	void showStations();
	void showStationByName();

};


#endif

