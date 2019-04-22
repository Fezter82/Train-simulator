//***********************************************************
// Vehicle.H
// Base class for all types of Vehicles
//***********************************************************
#ifndef VehicleH
#define VehicleH
#include <vector>
#include <string>
using namespace std;

class Vehicle
{
private:
	int ID;
	int type;
	vector<string> history;
public:
	//--------------------------------------Constructors
	Vehicle(): ID(0), type(0){}
	Vehicle(int vID, int vType) : ID(vID), type(vType) {	}
	virtual ~Vehicle() {}

	//--------------------------------------Set & Get-functions
	int getID() const { return ID; }
	void setID(int wID) { ID = wID; }
	int getType() const { return type; }
	void setType(int wType) { type = wType; }
	void addHistory(string event) { history.push_back(event); }
	vector<string> getHistory() const { return history; } //save strings of information of each event regarding vehicle

	//--------------------------------------Virtual functions
	// HAS
	virtual bool hasSeats() = 0;
	virtual bool hasBeds() = 0;
	virtual bool hasInternet() = 0;
	virtual bool hasCapacity() = 0;
	virtual bool hasSqrMeters() = 0;
	virtual bool hasVolume() = 0;
	virtual bool hasMaxSpeed() = 0;
	virtual bool hasConsumption() = 0;
	virtual bool hasEffect() = 0;
	// GET
	virtual int getNrOfSeats() const = 0;
	virtual int getNrOfBeds() const = 0;
	virtual int getInternet() const = 0;
	virtual int getCapacity() const = 0;
	virtual int getSqrMeters() const = 0;
	virtual int getMaxSpeed() const = 0;
	virtual int getConsumption() const = 0;
	virtual int getEffect() const = 0;
	virtual int getVolume() const = 0;
	// SET
	virtual void setNrOfSeats(int WSeats) = 0;
	virtual void setNrOfBeds(int WSeats) = 0;
	virtual void setInternet(int wInternet) = 0;
	virtual void setCapacity(int wCap) = 0;
	virtual void setSqrMeters(int wSqr) = 0;
	virtual void setVolume(int wVol) = 0;
	virtual void setMaxSpeed(int vMax) = 0;
	virtual void setConsumption(int vCon) = 0;
	virtual void setEffect(int vEff) = 0;

};


#endif

