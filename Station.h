//************************************************************************
// Station.H
// Class definition of Station
// Class represents a train station that can store vehicles
//************************************************************************
#ifndef StationH
#define StationH
#include <vector>
#include <memory>
#include <string>
#include "DieselLoco.h"
#include "ElectroLoco.h"
#include "Vehicle.h"
#include "Sitwagon.h"
#include "Sleepwagon.h"
#include "OpenCargo.h"
#include "ClosedCargo.h"
using namespace std;

class Station
{
private:
	string stationName;
	vector<shared_ptr<Vehicle>> storedVehicles;

public:
	//--------------------------------------Constructors
	Station(): stationName(""){ }
	Station(string sName): stationName(sName){ }

	void setName(string sName) { stationName = sName; }
	string getStationName() const { return stationName; }

	void storeVehicle(int sID, int sType, int sParam1, int sParam2); //add vehicle object to storage(vector)
	void sortStorage(); //sort vehicles in storage by vehicle ID
	void showStoredVehicles(); //print all vehicles in storage
	void clearStorage() { storedVehicles.clear(); }
	bool releaseVehicle(int vType, shared_ptr<Vehicle> &tmp); //when vehicle docks to train, it is released from storage
	bool addVehicle(shared_ptr<Vehicle> &tVeh); //when vehicle is released from train and put in storage at station
	int getNrInStorage() const { return storedVehicles.size(); }
	bool findVehicle(int id) const;
	int showVehicleInfo(int id, int opt); //print function. Opt gives different types of outputs
};
ostream &operator<<(ostream &os, const Station &station);
istream &operator >> (istream &is, Station &station);

bool sortById(const std::shared_ptr<Vehicle>& a, const std::shared_ptr<Vehicle>& b); //Callable function for sorting vehicles by ID
#endif

