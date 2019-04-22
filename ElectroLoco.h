//***************************************************************************
// ElectroLoco.H
// Class definition of Electrical Locomotive, derived from base class Vehicle
//***************************************************************************
#include "Vehicle.h"
#ifndef ElectroLocoH
#define ElectroLocoH
using namespace std;

class ElectricalLocomotive : public Vehicle
{
private:
	int maxSpeed;
	int effect;

public:
	//--------------------------------------Constructors
	ElectricalLocomotive() : Vehicle(), maxSpeed(0), effect(0) { }
	ElectricalLocomotive(int vID, int vType, int vMax, int vEff) : Vehicle(vID, vType), maxSpeed(vMax), effect(vEff) { }
	
	//--------------------------------------SET and GET
	void setMaxSpeed(int vMax) { maxSpeed = vMax; }
	void setEffect(int vEff) { effect = vEff; }
	int getMaxSpeed() const { return maxSpeed; }
	int getEffect() const { return effect; }

	//-------------------------Check if functions are relevant
	virtual bool hasMaxSpeed() { return true; }
	virtual bool hasConsumption() { return false; }
	virtual bool hasEffect() { return true; }
	virtual bool hasSeats() { return false; }
	virtual bool hasInternet() { return false; }
	virtual bool hasBeds() { return false; }
	virtual bool hasCapacity() { return false; }
	virtual bool hasSqrMeters() { return false; }
	virtual bool hasVolume() { return false; }

	//-------------------------Empty declarations
	virtual void setConsumption(int vCon) { ; }
	virtual void setInternet(int wInternet) { ; }
	virtual void setNrOfSeats(int WSeats) { ; }
	virtual void setNrOfBeds(int WSeats) { ; }
	virtual void setCapacity(int wCap) { ; }
	virtual void setSqrMeters(int wSqr) { ; }
	virtual void setVolume(int wVol) { ; }
	virtual int getConsumption() const { return 0; }
	virtual int getInternet() const { return 0; }
	virtual int getNrOfSeats() const { return 0; }
	virtual int getNrOfBeds() const { return 0; }
	virtual int getCapacity() const { return 0; }
	virtual int getSqrMeters() const { return 0; }
	virtual int getVolume() const { return 0; }
};

#endif
