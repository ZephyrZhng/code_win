#include <iostream>
using namespace std;

class Point
{
	public:
		Point(double x, double y);
		~Point(){}
		void ShowOrdinate();
		Point& operator ++();
		Point operator ++(int);
		Point& operator --();
		Point operator --(int);
	private:
		double _x;
		double _y;
};
Point::Point(double x, double y)
{
	_x = x;
	_y = y;
}
void Point::ShowOrdinate()
{
	cout << "(" << _x << ", " << _y << ")" << endl;
}
Point& Point::operator ++()
{
	_x += 1;
	_y += 1;

	return *this;
}
Point Point::operator ++(int)
{
	Point old = *this;
	++(*this);

	return old;
}
Point& Point::operator --()
{
	_x -= 1;
	_y -= 1;

	return *this;
}
Point Point::operator --(int)
{
	Point old = *this;
	--(*this);

	return old;
}

int main()
{
	Point p(1.2, 3.4);

	cout << "The initial ordinate: ";
	p.ShowOrdinate();
	cout << "Now _x++ _y++, output new ordinate: ";
	p++;
	p.ShowOrdinate();

	return 0;
}
