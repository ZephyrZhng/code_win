//complex
//一元二次方程在复数域内求根
#include <iostream>
#include <cmath>
using namespace std;

class complex
{
public:
	complex(double R = 0.0, double I = 0.0): real(R), imaginary(I) {}
	complex(const complex& Z);
	~complex() {}
	double GetReal();
	double GetImaginary();
	friend complex operator +(double x, const complex& Z);
	friend complex operator +(const complex &Z, double x);
	friend complex operator +(const complex& Z_1, const complex& Z_2);
	friend complex operator -(const complex& z);
	friend complex operator -(double x, const complex& Z);
	friend complex operator -(const complex &Z, double x);
	friend complex operator -(const complex& Z_1, const complex& Z_2);
	friend complex operator *(double x, const complex& Z);
	friend complex operator *(const complex& Z, double x);
	friend complex operator *(const complex& Z_1, const complex& Z_2);
	friend int judge_Z_0(const complex& Z);
	friend complex operator /(double x, const complex& Z);
	friend complex operator /(const complex& Z, double x);
	friend complex operator /(const complex& Z_1, const complex& Z_2);
	friend ostream& operator <<(ostream& output, const complex& Z);

private:
	double real;
	double imaginary;
};

complex::complex(const complex& Z)
{
	real = Z.real;
	imaginary = Z.imaginary;
}

inline double complex::GetReal()
{
	return real;
}

inline double complex::GetImaginary()
{
	return imaginary;
}

complex operator +(double x, const complex& Z)
{
	return complex(Z.real + x, Z.imaginary);
}

complex operator +(const complex& Z, double x)
{
	return complex(Z.real + x, Z.imaginary);
}

complex operator +(const complex& Z_1, const complex& Z_2)
{
	return complex(Z_1.real + Z_2.real, Z_1.imaginary + Z_2.imaginary);
}

complex operator -(const complex& Z)
{
	return complex(-1 * Z.real, -1 * Z.imaginary);
}

complex operator -(double x, const complex& Z)
{
	return complex(x - Z.real, -1 * Z.imaginary);
}

complex operator -(const complex& Z, double x)
{
	return complex(Z.real - x, Z.imaginary);
}

complex operator -(const complex& Z_1, const complex& Z_2)
{
	return complex(Z_1.real - Z_2.real, Z_1.imaginary - Z_2.imaginary);
}

complex operator *(double x, const complex& Z)
{
	return complex(x * Z.real, x * Z.imaginary);
}

complex operator *(const complex& Z, double x)
{
	return complex(x * Z.real, x * Z.imaginary);
}

complex operator *(const complex& Z_1, const complex& Z_2)
{
	int NewReal, NewImaginary;
	NewReal = Z_1.real * Z_2.real - Z_1.imaginary * Z_2.imaginary;
	NewImaginary = Z_1.real * Z_2.imaginary + Z_1.imaginary * Z_1.real;
	return complex(NewReal, NewImaginary);
}

int judge_x_0(double x)
{
	if(x == 0)
	{
		cout << "ERROR: Denominator cannot be 0!" << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

int judge_Z_0(const complex& Z)
{
	if(Z.real == 0 && Z.imaginary == 0)
	{
		cout << "ERROR: Denominator cannot be 0!" << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

complex operator /(double x, const complex& Z)
{
	if(judge_Z_0(Z))
	{
		double coefficient;

		coefficient = x / (Z.real * Z.real + Z.imaginary * Z.imaginary);
		return complex(coefficient * Z.real, -1 * coefficient * Z.imaginary);
	}
}

complex operator /(const complex& Z, double x)
{
	if(judge_x_0(x))
	{
		return complex(Z.real / x, Z.imaginary / x);
	}	
}

complex operator /(const complex& Z_1, const complex& Z_2)
{
	if(judge_Z_0(Z_2))
	{
		complex Z_temp(Z_2.real, -Z_2.imaginary);
		double coefficient = 1 / (Z_2.real * Z_2.real + Z_2.imaginary * Z_2.imaginary);

		return coefficient * (Z_1 * Z_temp);
	}
}

ostream& operator <<(ostream& output, const complex& Z)
{
	output << Z.real << " + " << Z.imaginary << "i";
	return output;
}

struct coefficient
{
	double a;
	double b;
	double c;
}a_b_c;

void input_coefficient(struct coefficient& a_b_c)
{
	cout << "Please input coefficient for x ^ 2: ";
	cin >> a_b_c.a;
	cout << "Please input coefficient for x: ";
	cin >> a_b_c.b;
	cout << "Please input constant term: ";
	cin >> a_b_c.c;
}

void root(const struct coefficient& a_b_c)
{
	double delta;
	double real_1, real_2;
	double imaginary_1, imaginary_2;

	delta = sqrt(fabs(a_b_c.b * a_b_c.b - 4 * a_b_c.a * a_b_c.c));
	if((a_b_c.b * a_b_c.b - 4 * a_b_c.a * a_b_c.c) >= 0)
	{
		real_1 = (-a_b_c.b + delta) / 2 / a_b_c.a;
		real_2 = (-a_b_c.b - delta) / 2 / a_b_c.a;
		complex root_1(real_1, 0);
		complex root_2(real_2, 0);
		cout << "x1 = " << root_1 << endl;
		cout << "x2 = " << root_2 << endl;
	}
	else
	{
		real_1 = (-a_b_c.b / 2 / a_b_c.a);
		imaginary_1 = delta / 2 / a_b_c.a;
		imaginary_2 = -delta / 2 / a_b_c.a;
		complex root_1(real_1, imaginary_1);
		complex root_2(real_1, imaginary_2);
		cout << "x1 = " << root_1 << endl;
		cout << "x2 = " << root_2 << endl;
	}
}

int main()
{
	cout << "一元二次方程在复数域内求根测试……" << endl;
	input_coefficient(a_b_c);
	root(a_b_c);

	return 0;
}
