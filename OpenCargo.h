//************************************************************************
// OpenCargo.H
// Class definition of OpenCargo, derived from base class Vehicle
//************************************************************************
#include "Vehicle.h"
#ifndef OpenCargoH
#define OpenCargoH
using namespace std;

class OpenCargo : public Vehicle
{
private:
	int weightCapacity;
	int sqrMeters;

public:
	//--------------------------------------Constructors
	OpenCargo() : Vehicle(), weightCapacity(0), sqrMeters(0) {}
	OpenCargo(int wID, int wType, int wCap, int wSqr) : Vehicle(wID, wType), weightCapacity(wCap), sqrMeters(wSqr) {}

	//--------------------------------------SET and GET
	void setCapacity(int wCap) { weightCapacity = wCap; }
	int getCapacity() const { return weightCapacity; }
	void setSqrMeters(int wSqr) { sqrMeters = wSqr; }
	int getSqrMeters() const { return sqrMeters; }

	//-------------------------Check if functions are relevant
	virtual bool hasSeats() { return false; }
	virtual bool hasInternet() { return false; }
	virtual bool hasBeds() { return false; }
	virtual bool hasCapacity() { return true; }
	virtual bool hasSqrMeters() { return true; }
	virtual bool hasVolume() { return false; }
	virtual bool hasMaxSpeed() { return false; }
	virtual bool hasConsumption() { return false; }
	virtual bool hasEffect() { return false; }

	//-------------------------Empty declarations
	virtual void setInternet(int wInternet) { ; }
	virtual void setNrOfSeats(int WSeats) { ; }
	virtual void setNrOfBeds(int WSeats) { ; }
	virtual void setVolume(int wVol) { ; }
	virtual void setEffect(int vEff) { ; }
	virtual void setConsumption(int vCon) { ; }
	virtual void setMaxSpeed(int vMax) { ; }
	virtual int getInternet() const { return 0; }
	virtual int getNrOfSeats() const { return 0; }
	virtual int getNrOfBeds() const { return 0; }
	virtual int getVolume() const { return 0; }
	virtual int getEffect() const { return 0; }
	virtual int getConsumption() const { return 0; }
	virtual int getMaxSpeed() const { return 0; }


};

#endif
