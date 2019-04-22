//------------------------------------------------------
//Train.cpp
//Definition file of member functions for class Train
//Andreas Lind, anli1606@student.miun.se
//------------------------------------------------------
#include "Train.h"
#include <iostream>
#include <algorithm>
using namespace std;

//***********************************************************************************************
// Initializing constructor
//***********************************************************************************************
Train::Train(int tID, string tOrig, string tDest, Time tDep, Time tArr, string tState, Time tDelay, Time aDelay, int max)
{
	trainID = tID;
	origin = tOrig;
	destination = tDest;
	departure = tDep;
	arrival = tArr;
	state = tState;
	maxSpeed = max;
	departureDelay = tDelay;
	arrivalDelay = aDelay;
}
//***********************************************************************************************
//  Overloading of operator << for writing to file
//***********************************************************************************************
ostream &operator<<(ostream &os, const Train &train)
{
	return os;
}
//***********************************************************************************************
//  Overloading of operator >> for reading from file
//***********************************************************************************************
istream &operator >> (istream &is, Train &train)
{
	if (is.peek() == EOF)
		return is;

	train.clearSpecs();

	int tmpID;
	is >> tmpID;
	is.get();
	train.setTrainID(tmpID);

	string tmp1, tmp2;
	getline(is, tmp1, ' ');
	train.setOrigin(tmp1);

	getline(is, tmp2, ' ');
	train.setDestination(tmp2);

	Time time1, time2;
	is >> time1 >> time2;

	train.setDeparture(time1.getHour(), time1.getMinute());
	train.setArrival(time2.getHour(), time2.getMinute());

	int tmpSpeed = 0;

	is >> tmpSpeed;
	train.setMaxSpeed(tmpSpeed);

	int tmp;
	bool again = true;

	do
	{	
		is >> tmp;

		if(tmp != ' ')
			train.setTrainSpecs(tmp);

		if (is.peek() == '\n' || is.peek() == EOF)
			again = false;

	} while (again);

	return is;

}
//***********************************************************************************************
// addVehicle
// attach vehicle to train
//***********************************************************************************************
bool Train::addVehicle(shared_ptr<Vehicle> &tVeh)
{
	trainSet.push_back(tVeh); //push shared_ptr into vector
	return true;
}
//***********************************************************************************************
// releaseVehicle
// release vehicle from train to be put in station storage
//***********************************************************************************************
bool Train::releaseVehicle(shared_ptr<Vehicle> &tmp)
{

	tmp = std::move(trainSet[0]);		//assign pointer to object to tmp 
	trainSet[0].reset();				//reset old pointer to object
	trainSet.erase(trainSet.begin());	//delete old pointer
	return true;
}
//***********************************************************************************************
// delayDeparture
// add ten minutes to departure time, and add ten minutes to departure delay 
//***********************************************************************************************
void Train::delayDeparture()
{ 
	departure.ticTenMin();
	departureDelay.ticTenMin();
}
//***********************************************************************************************
// setArrivalDelay
// set arrivalDelay to value of aDelay
//***********************************************************************************************
void Train::setArrivalDelay(Time aDelay)
{
	arrivalDelay = aDelay;
}
//***********************************************************************************************
// findVehicle
// find if vehicle is attached to train
//***********************************************************************************************
bool Train::findVehicle(int id) const
{
	bool found = false;

	for (auto e : trainSet)
		if (e->getID() == id)
			found = true;

	return found;
}
//***********************************************************************************************
// showVehicleInfo
// show information on vehicle
// opt decides what type of information is displayed and how detailed
//***********************************************************************************************
int Train::showVehicleInfo(int id, int opt)
{

	for (auto e : trainSet)
	{
		if (e->getID() == id || id == 0)
		{
			cout << "Vehicle ID: " << e->getID() << endl;

			switch (e->getType())
			{
			case 0:
				cout << "Type: Sitwagon" << endl;
				cout << "Nr of Seats: " << e->getNrOfSeats();
				cout << endl << "Internet: ";
				if (e->getInternet() == 1)
					cout << "Yes";
				else
					cout << "No";
				cout << endl;
				break;

			case 1:
				cout << "Type: Sleepwagon" << endl;
				cout << "Nr of beds: " << e->getNrOfBeds() << endl;
				break;

			case 2:
				cout << "Type: Open Cargowagon" << endl;
				cout << "Loading capacity: " << e->getCapacity() << " tons" << endl;
				cout << "Loading area: " << e->getSqrMeters() << "m2" << endl;
				break;
			case 3:
				cout << "Type: Closed Cargowagon" << endl;
				cout << "Loading volume: " << e->getVolume() << "m3" << endl;
				break;
			case 4:
				cout << "Type: Electrical Locomotive" << endl;
				cout << "Max speed: " << e->getMaxSpeed() << "km/h" << endl;
				cout << "Effect: " << e->getEffect() << "kw" << endl;
				break;
			case 5:
				cout << "Type: Diesel Locomotive" << endl;
				cout << "Max speed: " << e->getMaxSpeed() << "km/h" << endl;
				cout << "Consumption: " << e->getConsumption() << " liters/h" << endl;
				break;
			}

			cout << "----------------------" << endl;
			
			//Show full history on vehicle
			if (opt == 2)
			{
				cout << "Full history on vehicle:";
				for (auto it : e->getHistory())
					cout << endl << it;

				if (e->getHistory().size() == 0)
					cout << endl << "-- Not used during simulation --";

				cout << endl << endl;
			}

			if(id > 0)
				return 0;
		}
	}
	return 0;
}
//***********************************************************************************************
// returnHighLocoSpeed
// find fastest vehicle(locomotive) attached to train
// and return maxspeed of that vehicle
//***********************************************************************************************
int Train::returnHighLocoSpeed()
{
	int speed = 0;

	for (auto e : trainSet)
	{
		if (e->hasMaxSpeed())
		{
			if (e->getMaxSpeed() > speed)
				speed = e->getMaxSpeed();
		}
	}

	return speed;
}