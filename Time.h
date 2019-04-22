//--------------------------------------
//Time.h
//Headerfile for class Time
//Andreas Lind, anli1606@student.miun.se
//--------------------------------------
#ifndef TimeH
#define TimeH
#include <iostream>
using namespace std;

class Time
{
private:
	int hour;
	int minute;
	int second;

public:
	//-----------------------Constructors
	Time();
	Time(int pHour, int pMin, int pSec);

	//-----------------------Set and Get
	void setHour(int pHour);
	void setMinute(int pMin);
	void setSecond(int pSec);
	int getHour() const { return hour; }
	int getMinute() const { return minute; }
	int getSecond() const { return second; }
	void ticSec();
	void ticMin();
	void ticTenMin();
	void ticXMin(int x);
	void setTimeFromDouble(double pHour);

	//-----------------------Overloading
	bool operator<(const Time &time) const;
	bool operator>(const Time &time) const;
	bool operator==(const Time &time) const;
	Time operator+(const Time &time) const;
	Time operator-(const Time &time) const;

};
//Print functions
void showTime(Time const &time);
ostream &operator<<(ostream &os, const Time &time);
istream &operator >> (istream &is, Time &time);

#endif
