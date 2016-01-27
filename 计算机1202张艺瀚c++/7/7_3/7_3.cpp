#include <iostream>

using namespace std;

class vehicle
{
	public:
		vehicle(int v, int g);
		~vehicle();
		void Run();
		void Stop();
	private:
		int Maxspeed;
		int Weight;
};
vehicle::vehicle(int v, int g)
{
	Maxspeed = v;
	Weight = g;
	cout << "Vehicle's constructor called!" << endl;
}
vehicle::~vehicle()
{
	cout << "Vehicle's constructor called!" << endl;
}
void vehicle::Run()
{
	cout << "Begin to run!" << endl;
}
void vehicle::Stop()
{
	cout << "Stop!" << endl;
}

class bicycle: virtual public vehicle
{
	public:
		bicycle(int v, int g, int h);
		~bicycle();
	private:
		int Height;
};
bicycle::bicycle(int v, int g, int h): vehicle(v, g)
{
	Height = h;
	cout << "Bicycle's constructor called!" << endl;
}
bicycle::~bicycle()
{
	cout << "Bicycle's destructor called!" << endl;
}

class motorcar: virtual public vehicle
{
	public:
		motorcar(int v, int g, int n);
		~motorcar();
	private:
		int SeatNum;
};
motorcar::motorcar(int v, int g, int n): vehicle(v, g)
{
	SeatNum = n;
	cout << "Motorcar's constructor called!" << endl;
}
motorcar::~motorcar()
{
	cout << "Motorcar's destructor called!" << endl;
}

class motorcycle: public bicycle, public motorcar
{
	public:
		motorcycle(int v, int g, int h, int n);
		~motorcycle();
};
motorcycle::motorcycle(int v, int g, int h, int n): 
vehicle(v, g), bicycle(v, g, h), motorcar(v, g, n)
{
	cout << "Motorcycle's constructor called!" << endl;
}
motorcycle::~motorcycle()
{
	cout << "Motorcycle's destructor called!" << endl;
}

int main()
{
	motorcycle MC(1, 2, 3, 4);

	return 0;
}
