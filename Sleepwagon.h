//************************************************************************
// Sleepwagon.H
// Class definition of Sleepwagon, derived from base class Vehicle
//************************************************************************
#include "Vehicle.h"
#ifndef SleepwagonH
#define SleepwagonH
using namespace std;

class Sleepwagon : public Vehicle
{
private:
	int nrOfBeds;

public:
	//--------------------------------------Constructors
	Sleepwagon() : Vehicle(), nrOfBeds(-1) {}
	Sleepwagon(int wID, int wType, int wBeds) : Vehicle(wID, wType), nrOfBeds(wBeds) { }

	//--------------------------------------SET and GET
	int getNrOfBeds() const { return nrOfBeds; }
	void setNrOfBeds(int wBeds) { nrOfBeds = wBeds; }

	//-------------------------Check if functions are relevant
	virtual bool hasSeats() { return false; }
	virtual bool hasInternet() { return false; }
	virtual bool hasBeds() { return true; }
	virtual bool hasCapacity() { return false; }
	virtual bool hasSqrMeters() { return false; }
	virtual bool hasVolume() { return false; }
	virtual bool hasMaxSpeed() { return false; }
	virtual bool hasConsumption() { return false; }
	virtual bool hasEffect() { return false; }

	//-------------------------Empty declarations
	virtual void setInternet(int wInternet) { ; }
	virtual void setNrOfSeats(int WSeats) { ; }
	virtual void setCapacity(int wCap) { ; }
	virtual void setSqrMeters(int wSqr) { ; }
	virtual void setVolume(int wVol) { ; }
	virtual void setEffect(int vEff) { ; }
	virtual void setConsumption(int vCon) { ; }
	virtual void setMaxSpeed(int vMax) { ; }
	virtual int getInternet() const { return 0; }
	virtual int getNrOfSeats() const { return 0; }
	virtual int getCapacity() const { return 0; }
	virtual int getSqrMeters() const { return 0; }
	virtual int getVolume() const { return 0; }
	virtual int getEffect() const { return 0; }
	virtual int getConsumption() const { return 0; }
	virtual int getMaxSpeed() const { return 0; }

};

#endif
