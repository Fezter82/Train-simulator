//************************************************************************
// ClosedCargo.H
// Class definition of ClosedCargo, derived from base class Wagons
//************************************************************************
#include "Vehicle.h"
#ifndef ClosedCargoH
#define ClosedCargoH
using namespace std;

class ClosedCargo : public Vehicle
{
private:
	int volume; //loading volume

public:
	//--------------------------------------Constructors
	ClosedCargo() : Vehicle(), volume(0) {}
	ClosedCargo(int wID, int wType, int wVol) : Vehicle(wID, wType), volume(wVol) {}

	//--------------------------------------SET and GET
	void setVolume(int wVol) { volume = wVol; }
	int getVolume() const { return volume; }

	//-------------------------Check if functions are relevant
	virtual bool hasSeats() { return false; }
	virtual bool hasInternet() { return false; }
	virtual bool hasBeds() { return false; }
	virtual bool hasCapacity() { return false; }
	virtual bool hasSqrMeters() { return false; }
	virtual bool hasVolume() { return true; }
	virtual bool hasMaxSpeed() { return false; }
	virtual bool hasConsumption() { return false; }
	virtual bool hasEffect() { return false; }

	//-------------------------Empty declarations
	virtual void setInternet(int wInternet) { ; }
	virtual void setNrOfSeats(int WSeats) { ; }
	virtual void setNrOfBeds(int WSeats) { ; }
	virtual void setCapacity(int wCap) { ; }
	virtual void setSqrMeters(int wSqr) { ; }
	virtual void setEffect(int vEff) { ; }
	virtual void setConsumption(int vCon) { ; }
	virtual void setMaxSpeed(int vMax) { ; }
	virtual int getInternet() const { return 0; }
	virtual int getNrOfSeats() const { return 0; }
	virtual int getNrOfBeds() const { return 0; }
	virtual int getCapacity() const { return 0; }
	virtual int getSqrMeters() const { return 0; }
	virtual int getEffect() const { return 0; }
	virtual int getConsumption() const { return 0; }
	virtual int getMaxSpeed() const { return 0; }


};

#endif

