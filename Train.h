//************************************************************************
// Train.H
// Class definition of Train
// Train class simulates an actual train. Spceifications decides which types
// of vehicles it should consist of. A train is assembled at station of origin,
// run to destination and then dismounted.
//************************************************************************
#ifndef TrainH
#define TrainH
#include "Vehicle.h"
#include "Time.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Train
{
private:
	int trainID;
	string origin;
	string destination;
	Time departure;
	Time arrival;
	string state; //State of train: NOT ASSEMBLED, ASSEMBLED, READY, RUNNING etc.
	vector<int> trainSpecs; //specifications of which types of vehicles the train should consist of
	vector<shared_ptr<Vehicle>> trainSet; //the actual train set with locomotives and wagons
	Time departureDelay; //delay on departure
	Time arrivalDelay; //delay on arrival
	int maxSpeed;
public:
	//------------------------------------------Constructors
	Train(): trainID(-1), origin(""), destination(""), departure(Time()), arrival(Time()), state("NOT ASSEMBLED"), departureDelay(Time()), arrivalDelay(Time()), maxSpeed(-1) {}
	Train(int tID, string tOrig, string tDest, Time tDep, Time tArr, string tState, Time tDelay, Time aDelay, int max);

	//------------------------------------------GET
	int getTrainID() const { return trainID; }
	string getOrigin() const { return origin; }
	string getDestination() const { return destination; }
	Time getDeparture() const { return departure; }
	Time getArrival() const { return arrival; }
	string getState() const { return state; }
	int getMaxSpeed() const { return maxSpeed; }
	vector<int> getSpecs() { return trainSpecs; } //return vector with specifications of which types of vehicles the train should consist of
	int getNrOfAttachedWagons() const { return trainSet.size(); } //return how many vehicles that are attached to train
	Time getDelay() const { return departureDelay; }
	Time getArrivalDelay() const { return arrivalDelay; }
	
	//------------------------------------------SET
	void setTrainID(int tID) { trainID = tID; }
	void setOrigin(string tOrig) { origin = tOrig; }
	void setDestination(string tDest) { destination = tDest; }
	void setDeparture(int pHour, int pMin) { departure = Time(pHour, pMin, 0); }
	void setArrival(int pHour, int pMin) { arrival = Time(pHour, pMin, 0); }
	void setState(string tState) { state = tState; }
	void setTrainSpecs(int tType) { trainSpecs.push_back(tType); }
	void setMaxSpeed(int tSpeed) { maxSpeed = tSpeed; }
	void setArrivalDelay(Time aDelay);

	//------------------------------------------Various
	void clearSpecs() { trainSpecs.clear(); }
	bool addVehicle(shared_ptr<Vehicle> &tVeh); //attach vehicle to train from storage
	bool releaseVehicle(shared_ptr<Vehicle> &tmp); //dismount vehicle from train to be put in storage at station
	void delayDeparture(); //delay departure with 10 minutes
	int showVehicleInfo(int id, int opt);
	int returnHighLocoSpeed(); //returns highest speed on attached locomotives (might be more than 1 on a train)
	bool findVehicle(int id) const;
};
ostream &operator<<(ostream &os, const Train &train);
istream &operator >> (istream &is, Train &train);
#endif
