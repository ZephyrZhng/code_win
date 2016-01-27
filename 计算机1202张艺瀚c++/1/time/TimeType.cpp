//"TimeType.cpp"
#include "timetype.h"
#include <iostream.h>
void TimeType::Set(int hours, int minutes, int seconds)
{
	hrs = hours;
	mins = minutes;
	secs = seconds;
}

void TimeType::Increment()
{
	secs++;
	if (secs>59) {
		secs=0;
		mins++;
		if (mins>59) {
			mins=0;
			hrs++;
			if (hrs>23) hrs=0;
		}
	}
}

void TimeType::Write() const
{
	if (hrs<10) cout << '0';
	cout << hrs << ':';
	if (mins<10) cout <<'0';
	cout << mins << ':';
	if (secs<10) cout <<'0';
	cout << secs;
}

bool TimeType::Equal(TimeType otherTime) const
{
	return (hrs==otherTime.hrs && mins==otherTime.mins && secs==otherTime.secs);
}
bool TimeType::LessThan(TimeType otherTime) const
{
	return (hrs<otherTime.hrs||hrs==otherTime.hrs && mins<otherTime.mins||hrs==otherTime.hrs && mins==otherTime.mins && secs<otherTime.secs);
}
