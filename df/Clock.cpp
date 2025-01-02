#include "Clock.h"
#include "logManager.h"
#include <Windows.h>


df::Clock::Clock()
{
	//set previous_time to the current time
	m_previous_time = getTimeNow();
}

//returns the current time as a long int. used by non const functions
long int df::Clock::getTimeNow()
{
	//store the current time
	SYSTEMTIME time_now;
	GetSystemTime(&time_now);

	//convert current time to a long
	long int long_time = (time_now.wDay * 24 * 60 * 60 * 1000)
		+ (time_now.wHour * 60 * 60 * 1000)
		+ (time_now.wMinute * 60 * 1000)
		+ (time_now.wSecond * 1000)
		+ (time_now.wMilliseconds);

	//return converted value
	return long_time;
}

//returns time between function calls, then sets previous_time to current time
long int df::Clock::delta()
{
	//store current time in new int long
	int long new_time = getTimeNow();

	//store difference between current time and previous time
	long int difference = new_time - m_previous_time;

	//set variable previous time to the current time (for future calls)
	m_previous_time = new_time;

	//return the difference in time
	return difference;

}

//
long int df::Clock::split() const
{
	//store the current time
	SYSTEMTIME time_now;
	GetSystemTime(&time_now);

	//convert current time to a long
	long int new_time = (time_now.wDay * 24 * 60 * 60 * 1000)
		+ (time_now.wHour * 60 * 60 * 1000)
		+ (time_now.wMinute * 60 * 1000)
		+ (time_now.wSecond * 1000)
		+ (time_now.wMilliseconds);

	//store difference between current time and previous time
	long int difference = new_time - m_previous_time;

	//note: previous_time unchanged

	//return the difference in time
	return difference;
}

