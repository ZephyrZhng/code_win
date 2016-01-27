//Diary.cpp
#include <iostream.h>
#include "TimeType.h"
int main()
{
	TimeType time;
	int hours;
	int minutes;
	int seconds;
	cout<<"Enter a time (use hours < 0 to quit): ";
	cin>>hours>>minutes>>seconds;
	while(hours>=0)
	{
		time.Set(hours, minutes, seconds);
		time.Increment();
		cout<<"Incremented time is ";
		time.Write();
		cout<<endl;
		cout<<"Enter a time (use hours < 0 to quit): ";
		cin>>hours>>minutes>>seconds;
	}
	return 0;
}
