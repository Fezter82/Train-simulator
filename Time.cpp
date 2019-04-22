//------------------------------------------------------
//Time.cpp
//Definitionsfil av medlemsfunktioner till klassen Time
//Andreas Lind, anli1606@student.miun.se
//------------------------------------------------------
#include "Time.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
//-------------------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------------------
Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}
//-------------------------------------------------------------------------------------------
// Initializing constructor
//-------------------------------------------------------------------------------------------
Time::Time(int pHour, int pMin, int pSec)
{
	hour = pHour;
	minute = pMin;
	second = pSec;
}
//-------------------------------------------------------------------------------------------
// setHour
// set data member hour to value of pHour
//-------------------------------------------------------------------------------------------
void Time::setHour(int pHour)
{
	hour = pHour;
}
//-------------------------------------------------------------------------------------------
// setMinute
// set data member minute to value of pMin
//-------------------------------------------------------------------------------------------
void Time::setMinute(int pMin)
{
	minute = pMin;
}
//-------------------------------------------------------------------------------------------
// setSecond
// set data member second to value of pSec
//-------------------------------------------------------------------------------------------
void Time::setSecond(int pSec)
{
	second = pSec;
}
//-------------------------------------------------------------------------------------------
// ticSec
// add one second
//-------------------------------------------------------------------------------------------
void Time::ticSec()
{
	second++;

	if (second % 60 == 0)
	{
		second = 0;
		minute++;
		if (minute % 60 == 0)
		{
			minute = 0;
			hour++;
			if (hour % 24 == 0)
				hour = 0;
		}
	}
}
//-------------------------------------------------------------------------------------------
// ticMin
// add one minute
//-------------------------------------------------------------------------------------------
void Time::ticMin()
{
	minute++;
	if (minute % 60 == 0)
	{
		minute = 0;
		hour++;
		if (hour % 24 == 0)
			hour = 0;
	}
}
//-------------------------------------------------------------------------------------------
// ticTenMin
// add ten minutes
//-------------------------------------------------------------------------------------------
void Time::ticTenMin()
{
	int count = 0;
	while (count < 10)
	{
		minute++;
		if (minute % 60 == 0)
		{
			minute = 0;
			hour++;
			if (hour % 24 == 0)
				hour = 0;
		}
		count++;
	} 

}

//-------------------------------------------------------------------------------------------
// ticXMin
// add 'x' minutes
//-------------------------------------------------------------------------------------------
void Time::ticXMin(int x)
{
	int count = 0;
	while (count < x)
	{
		minute++;
		if (minute % 60 == 0)
		{
			minute = 0;
			hour++;
			if (hour % 24 == 0)
				hour = 0;
		}
		count++;
	}
}
//-------------------------------------------------------------------------------------------
// setTimeFromDouble
// example: pHour = 7,25 --> 7 hours and 15 minutes
//-------------------------------------------------------------------------------------------
void Time::setTimeFromDouble(double pHour)
{
	pHour *= 3600;

	while (pHour >= 3600)
	{
		hour++;
		pHour -= 3600;
	}
	while (pHour >= 60)
	{
		minute++;
		pHour -= 60;
	}
		second = (int)pHour;

}
//-------------------------------------------------------------------------------------------
// overloading "less than"
//-------------------------------------------------------------------------------------------
bool Time::operator<(const Time &time) const
{
	return (getHour() * 3600 + getMinute() * 60 + getSecond()) < (time.getHour() * 3600 + time.getMinute() * 60 + time.getSecond()); //omvandla allt till sekunder för jämförelse
}
//-------------------------------------------------------------------------------------------
// overloading "bigger than"
//-------------------------------------------------------------------------------------------
bool Time::operator>(const Time &time) const
{
	return (getHour() * 3600 + getMinute() * 60 + getSecond()) > (time.getHour() * 3600 + time.getMinute() * 60 + time.getSecond()); //omvandla allt till sekunder för jämförelse
}
//-------------------------------------------------------------------------------------------
// overloading "equals to"
//-------------------------------------------------------------------------------------------
bool Time::operator==(const Time &time) const
{
	return (getHour() * 3600 + getMinute() * 60 + getSecond()) == (time.getHour() * 3600 + time.getMinute() * 60 + time.getSecond()); //omvandla allt till sekunder för jämförelse
}
//-------------------------------------------------------------------------------------------
// overloading operator +
//-------------------------------------------------------------------------------------------
Time Time::operator+(const Time &time) const
{
	int tmp1, tmp2, tot;
	tmp1 = getHour() * 3600 + getMinute() * 60 + getSecond(); //convert everything to seconds for comparison
	tmp2 = time.getHour() * 3600 + time.getMinute() * 60 + time.getSecond();
	tot = tmp1 + tmp2; //add totals


	Time tmp;

	// If the number of seconds exceeds 3600 ie one hour
	if (tot < 3600)
	{
		tmp.second = tot % 60;
		tmp.minute = (tot - tmp.getSecond()) / 60;
	}
	else
	{
		tmp.second = tot % 60;
		tmp.minute = ((tot % 3600) - tmp.getSecond()) / 60;
		tmp.hour = (tot / 3600);
	}

	return tmp;
}
//-------------------------------------------------------------------------------------------
// overloading operator -
//-------------------------------------------------------------------------------------------
Time Time::operator-(const Time &time) const
{
	int tmp1, tmp2, tot;
	tmp1 = getHour() * 3600 + getMinute() * 60 + getSecond(); //convert everything to seconds for comparison
	tmp2 = time.getHour() * 3600 + time.getMinute() * 60 + time.getSecond();
	tot = tmp1 - tmp2;

	Time tmp;

	//If the number of seconds is less than 3600 ie one hour
	if (tot < 3600)
	{
		tmp.second = tot % 60;
		tmp.minute = (tot - tmp.getSecond()) / 60;
	}
	else
	{
		tmp.second = tot % 60;
		tmp.minute = ((tot % 3600) - tmp.getSecond()) / 60;
		tmp.hour = (tot / 3600);
	}

	return tmp;
}
//-------------------------------------------------------------------------------------------
//  Overloading of operator << for writing to file
//-------------------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const Time &time)
{
	//os << (time.getHour() * 3600 + time.getMinute()) * 60 + time.getSecond();
	os << "[" << setw(2) << setfill('0') << time.getHour() << ":";
	os << setw(2) << setfill('0') << time.getMinute() << "] ";

	return os;
}
//-------------------------------------------------------------------------------------------
//  Overloading of operator >> for reading from file
//-------------------------------------------------------------------------------------------
istream &operator >> (istream &is, Time &time)
{
	int tmpHour = 0, tmpMin = 0, tmpSec = 0;
	char colon;

	is >> tmpHour >> colon >> tmpMin;

	//set Time objects data members
	time.setSecond(tmpSec);
	time.setMinute(tmpMin);
	time.setHour(tmpHour);

	return is;

}
//-------------------------------------------------------------------------------------------
// showTime
// write Time object on screen
//-------------------------------------------------------------------------------------------
void showTime(Time const &time)
{
	int hour = 0, min = 0;
	hour = time.getHour();
	min = time.getMinute();

	if (hour > 23)
		hour %= 24;

		cout << setw(2) << setfill('0') << hour;
		cout << ":" << setw(2) << setfill('0') << min;
		//cout << ":" << setw(2) << setfill('0') << time.getSecond();
}