//************************************************************************
// DieselLoco.H
// Class definition of Diesel Locomotive, derived from base class Vehicle
//************************************************************************
#include "Vehicle.h"
#ifndef DieselLocoH
#define DieselLocoH
using namespace std;

class DieselLocomotive: public Vehicle
{
private:
	int maxSpeed;
	int consumption;

public:
	//--------------------------------------Constructors
	DieselLocomotive(): Vehicle(), maxSpeed(0), consumption(0) { }
	DieselLocomotive(int vID, int vType, int vMax, int vCon) : Vehicle(vID, vType), maxSpeed(vMax), consumption(vCon) { }
	
	//--------------------------------------SET and GET
	void setMaxSpeed(int vMax) { maxSpeed = vMax; }
	void setConsumption(int vCon) { consumption = vCon; }
	int getMaxSpeed() const { return maxSpeed; }
	int getConsumption() const { return consumption; }

	//-------------------------Check if functions are relevant
	virtual bool hasMaxSpeed() { return true; }
	virtual bool hasConsumption() { return true; }
	virtual bool hasEffect() { return false; }
	virtual bool hasSeats() { return false; }
	virtual bool hasInternet() { return false; }
	virtual bool hasBeds() { return false; }
	virtual bool hasCapacity() { return false; }
	virtual bool hasSqrMeters() { return false; }
	virtual bool hasVolume() { return false; }

	//-------------------------Empty declarations
	virtual void setEffect(int vEff) { ; }
	virtual void setInternet(int wInternet) { ; }
	virtual void setNrOfSeats(int WSeats) { ; }
	virtual void setNrOfBeds(int WSeats) { ; }
	virtual void setCapacity(int wCap) { ; }
	virtual void setSqrMeters(int wSqr) { ; }
	virtual void setVolume(int wVol) { ; }
	virtual int getEffect() const { return 0; }
	virtual int getInternet() const { return 0; }
	virtual int getNrOfSeats() const { return 0; }
	virtual int getNrOfBeds() const { return 0; }
	virtual int getCapacity() const { return 0; }
	virtual int getSqrMeters() const { return 0; }
	virtual int getVolume() const { return 0; }
};

#endif