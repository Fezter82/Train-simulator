//************************************************************************
// Sitwagon.H
// Class definition of Sitwagon, derived from base class Vehicle
//************************************************************************
#include "Vehicle.h"
#ifndef SitwagonH
#define SitwagonH
using namespace std;

class Sitwagon : public Vehicle
{
private:
	int nrOfSeats;
	int internet; // 1 = true, 0 = false

public:
	//--------------------------------------Constructors
	Sitwagon(): Vehicle(), nrOfSeats(-1), internet(-1) { }
	Sitwagon(int wID, int wType, int wSeats, int wInternet): Vehicle(wID, wType = 0), nrOfSeats(wSeats), internet(wInternet) { }

	//--------------------------------------SET and GET
	void setNrOfSeats(int wSeats) { nrOfSeats = wSeats; }
	void setInternet(int vInternet) { internet = vInternet; }
	int getNrOfSeats() const { return nrOfSeats; }
	int getInternet() const { return internet; }

	//-------------------------Check if functions are relevant
	virtual bool hasSeats() { return true; }
	virtual bool hasBeds() { return false; }
	virtual bool hasInternet() { return true; }
	virtual bool hasCapacity() { return false; }
	virtual bool hasSqrMeters() { return false; }
	virtual bool hasVolume() { return false; }
	virtual bool hasMaxSpeed() { return false; }
	virtual bool hasConsumption() { return false; }
	virtual bool hasEffect() { return false; }

	//-------------------------Empty declarations
	virtual void setNrOfBeds(int wBeds) { ; }
	virtual void setCapacity(int wCap) { ; }
	virtual void setVolume(int wVol) { ; }
	virtual void setSqrMeters(int wSqr) { ; }
	virtual void setEffect(int vEff) { ; }
	virtual void setConsumption(int vCon) { ; }
	virtual void setMaxSpeed(int vMax) { ; }
	virtual int getNrOfBeds() const { return 0; }
	virtual int getCapacity() const { return 0; }
	virtual int getSqrMeters() const { return 0; }
	virtual int getVolume() const { return 0; }
	virtual int getEffect() const { return 0; }
	virtual int getConsumption() const { return 0; }
	virtual int getMaxSpeed() const { return 0; }

};

#endif
