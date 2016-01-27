#include <iostream>

using namespace std;

class vehicle
{
	public:
		vehicle();
		~vehicle();
		virtual void Run();
		virtual void Stop();
};
vehicle::vehicle()
{
	cout << "Vehicle's constructor called!" << endl;
}
vehicle::~vehicle()
{
	cout << "Vehicle's constructor called!" << endl;
}
void vehicle::Run()
{
	cout << "This vehicle begins to run!" << endl;
}
void vehicle::Stop()
{
	cout << "This vehicle stops!" << endl;
}

class bicycle: virtual public vehicle
{
	public:
		bicycle();
		~bicycle();
		virtual void Run();
		virtual void Stop();
};
bicycle::bicycle()
{
	cout << "Bicycle's constructor called!" << endl;
}
bicycle::~bicycle()
{
	cout << "Bicycle's destructor called!" << endl;
}
void bicycle::Run()
{
	cout << "This bicycle begins to run!" << endl;
}
void bicycle::Stop()
{
	cout << "This bicycle stops!" << endl;
}

class motorcar: virtual public vehicle
{
	public:
		motorcar();
		~motorcar();
		virtual void Run();
		virtual void Stop();
};
motorcar::motorcar()
{
	cout << "Motorcar's constructor called!" << endl;
}
motorcar::~motorcar()
{
	cout << "Motorcar's destructor called!" << endl;
}
void motorcar::Run()
{
	cout << "This motorcar begins to run!" << endl;
}
void motorcar::Stop()
{
	cout << "This motorcar stops!" << endl;
}

class motorcycle: public bicycle, public motorcar
{
	public:
		motorcycle();
		~motorcycle();
		virtual void Run();
		virtual void Stop();
};
motorcycle::motorcycle()
{
	cout << "Motorcycle's constructor called!" << endl;
}
motorcycle::~motorcycle()
{
	cout << "Motorcycle's destructor called!" << endl;
}
void motorcycle::Run()
{
	cout << "This motorcycle begins to run!" << endl; 
}
void motorcycle::Stop()
{
	cout << "This motorcycle stops!" << endl;
}

int main()
{
	vehicle V;
	bicycle B;
	motorcar MB;
	motorcycle MC;
	
	cout << endl;
	V.Run();
	V.Stop();
	B.Run();
	B.Stop();
	MB.Run();
	MB.Stop();
	MC.Run();
	MC.Stop();
	cout << endl;

	vehicle *p;

	cout << "Now we call functions of objects by vehicle pointer:" << endl;
	p = &V;
	p->Run();
	p->Stop();
	p = &B;
	p->Run();
	p->Stop();
	p = &MB;
	p->Run();
	p->Stop();
	p = &MC;
	p->Run();
	p->Stop();
	cout << endl;

	return 0;
}
