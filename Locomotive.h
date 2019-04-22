//***********************************************************
// Locomotive.H
// Base class for all types of Locomotives
//***********************************************************
#ifndef LocomotiveH
#define LocomotiveH
using namespace std;

class Locomotive
{
private:
	int locoID;
	int type;

public:
	//--------------------------------------Constructors
	Locomotive() : locoID(-1), type(-1) {}
	Locomotive(int vID, int vType) : locoID(vID), type(vType) {}
	virtual ~Locomotive() {}

	//--------------------------------------Set & Get-functions
	int getID() const { return locoID; }
	void setID(int vID) { locoID = vID; }
	int getType() const { return type; }
	void setType(int vType) { type = vType; }

	//--------------------------------------Virtual functions
	// HAS
	virtual bool hasMaxSpeed() = 0;
	virtual bool hasConsumption() = 0;
	virtual bool hasEffect() = 0;
	// GET
	virtual int getMaxSpeed() const = 0;
	virtual int getConsumption() const = 0;
	virtual int getEffect() const = 0;
	// SET
	virtual void setMaxSpeed(int vMax) = 0;
	virtual void setConsumption(int vCon) = 0;
	virtual void setEffect(int vEff) = 0;
};


#endif

