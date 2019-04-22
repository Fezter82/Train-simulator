//------------------------------------------------------
//Station.cpp
//Definition file of member functions for class Station
//Andreas Lind, anli1606@student.miun.se
//------------------------------------------------------
#include "Station.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

//***********************************************************************************************
// Overloading of operator << for printing to file
//***********************************************************************************************
ostream &operator<<(ostream &os, const Station &station)
{
	return os;
}
//***********************************************************************************************
// Overloading of operator >> for reading from file
//***********************************************************************************************
istream &operator >> (istream &is, Station &station)
{
	station.clearStorage(); //clear storage so it doesn't keep building up every new time the function is run
	char c;

	if (is.peek() == '\n')
		c = is.get();

	string tmpName;
	getline(is, tmpName, ' ');
	station.setName(tmpName);

	int tmpID = 0, tmpType = 0, tmpParam1 = 0, tmpParam2 = 0;
	int count = 0;

	is >> ws;


	while (is.peek() != '\n' && is.peek() != EOF) //check to see that next data item to read is not a new line or end of file
	{
		if (is.peek() == '(')
		{
			is >> c;
		}
		else if (is.peek() == ')')
		{
			is >> c;
			station.storeVehicle(tmpID, tmpType, tmpParam1, tmpParam2); //store vehicle in station storage
			count = 0;
			if (is.peek() == ' ')
				is >> c;
			else if (is.peek() == EOF)
				return is;
		}
		else
		{
			switch (count)
			{
			case 0:
				is >> tmpID;
				count++;
				break;
			case 1:
				is >> tmpType;
				count++;
				break;
			case 2:
				is >> tmpParam1;
				count++;
				break;
			case 3:
				is >> tmpParam2;
				count++;
				break;
			}
		}

	}

	return is;
}

//***********************************************************************************************
// storeVehicle
// Store vehicles on station based on type
//***********************************************************************************************
void Station::storeVehicle(int sID, int sType, int sParam1, int sParam2 = 0)
{
	switch (sType)
	{
	case 0:
		storedVehicles.push_back(shared_ptr<Vehicle>(new Sitwagon(sID, sType, sParam1, sParam2)));
		break;
	case 1:
		storedVehicles.push_back(shared_ptr<Vehicle>(new Sleepwagon(sID, sType, sParam1)));
		break;
	case 2:
		storedVehicles.push_back(shared_ptr<Vehicle>(new OpenCargo(sID, sType, sParam1, sParam2)));
		break;
	case 3:
		storedVehicles.push_back(shared_ptr<Vehicle>(new ClosedCargo(sID, sType, sParam1)));
		break;
	case 4:
		storedVehicles.push_back(shared_ptr<Vehicle>(new ElectricalLocomotive(sID, sType, sParam1, sParam2)));
		break;
	case 5:
		storedVehicles.push_back(shared_ptr<Vehicle>(new DieselLocomotive(sID, sType, sParam1, sParam2)));
		break;
	}
}
//***********************************************************************************************
// sortStorage
// sort storage based on lowest ID first
//***********************************************************************************************
void Station::sortStorage()
{
	sort(storedVehicles.begin(), storedVehicles.end(), sortById);
}
//***********************************************************************************************
// showStoredVehicles
// show all stored vehicles
//***********************************************************************************************
void Station::showStoredVehicles()
{
	for (auto idx : storedVehicles)
	{
		cout << "Vehicle ID:" << idx->getID() << endl;

		switch (idx->getType()) //see what type of vehicle idx points to
		{
		case 0:
			cout << "Type: Sitwagon" << endl;
			cout << "Nr of Seats: " << idx->getNrOfSeats();
			cout << endl << "Internet: ";
				if (idx->getInternet() == 1)
					cout << "Yes";
				else
					cout << "No";
			cout << endl;
			break;

		case 1:
			cout << "Type: Sleepwagon" << endl;
			cout << "Nr of beds: " << idx->getNrOfBeds() << endl;
			break;

		case 2:
			cout << "Type: Open Cargowagon" << endl;
			cout << "Loading capacity: " << idx->getCapacity() << " tons" << endl;
			cout << "Loading area: " << idx->getSqrMeters() << endl;
			break;
		case 3:
			cout << "Type: Closed Cargowagon" << endl;
			cout << "Loading volume: " << idx->getVolume() << "m3" << endl;
			break;
		case 4:
			cout << "Type: Electrical Locomotive" << endl;
			cout << "Max speed: " << idx->getMaxSpeed() << "km/h" << endl;
			cout << "Effect: " << idx->getEffect() << "kw" << endl;
			break;
		case 5:
			cout << "Type: Diesel Locomotive" << endl;
			cout << "Max speed: " << idx->getMaxSpeed() << "km/h" << endl;
			cout << "Consumption: " << idx->getConsumption() << " liters/h" << endl;
			break;
		}
		
		cout << "----------------------" << endl;
	}
}
//***********************************************************************************************
// releaseVehicle
// releases vehicle from station storage for attaching to train
//***********************************************************************************************
bool Station::releaseVehicle(int vType, shared_ptr<Vehicle> &tmp)
{
	auto it = storedVehicles.begin();

	it = find_if(storedVehicles.begin(), storedVehicles.end(), [vType](std::shared_ptr<Vehicle> const& a) {return a->getType() == vType; }); //look for the right type of vehicle

	if (it != storedVehicles.end())
	{
		tmp = std::move(*it); //assign pointer to object to tmp 
		storedVehicles[it - storedVehicles.begin()].reset(); //reset old pointer to object
		storedVehicles.erase(it); //delete old pointer
		return true;
	}
	else
		return false;
}
//***********************************************************************************************
// addVehicle
// add vehicle to station storage
//***********************************************************************************************
bool Station::addVehicle(shared_ptr<Vehicle> &tVeh)
{
	storedVehicles.push_back(tVeh);
	return true;
}
//***********************************************************************************************
// findVehicle
// find vehicle in storage by ID
//***********************************************************************************************
bool Station::findVehicle(int id) const
{
	bool found = false;

	for (auto e : storedVehicles)
		if (e->getID() == id)
			found = true;

	return found;
}
//***********************************************************************************************
// showVehicleInfo
// show information on vehicle
// opt decides what type of information is displayed and how detailed
//***********************************************************************************************
int Station::showVehicleInfo(int id, int opt)
{
	for (auto e : storedVehicles)
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

			if (id > 0)
				return 0;
		}
	}
	return 0;
}
//***********************************************************************************************
// sortById
// callable function to help sorting vehicles based on lowest ID fiirst
//***********************************************************************************************
bool sortById(const std::shared_ptr<Vehicle>& a, const std::shared_ptr<Vehicle>& b)
{
	return a->getID() < b->getID();
}