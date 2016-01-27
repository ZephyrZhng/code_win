#include <iostream>
using namespace std;

const double DeductionCoefficient = 0.01;
const int WorkAgeSalary = 35;

class Employee
{
public:
	
	Employee(int a);
	~Employee() {}
	virtual double salary() = 0;
	int WorkAge;
};
Employee::Employee(int a)
{
	WorkAge = a;
}

//工龄工资就是雇员在该公司工作的工龄每增加1年，月工资就增加35元

class Worker: public Employee
{
	//每小时工资额乘当月工作时数再加上工龄工资
public:
	Worker(int WA, int SPH, int WHTM);
	~Worker() {}
	double salary();
private:
	int SalaryPerHour;//每小时工资额
	int WorkHourThisMonth;//当月工作时数
};
Worker::Worker(int WA, int SPH, int WHTM): Employee(WA)
{
	SalaryPerHour = SPH;
	WorkHourThisMonth = WHTM;
}
double Worker::salary()
{
	return SalaryPerHour * WorkHourThisMonth + WorkAge * WorkAgeSalary;
}

class Salesman: public Employee
{
public:
	Salesman(int WA, int SPH, int WHTM, int SVTM);
	~Salesman() {}
	double salary();
private:
	//每小时工资额乘当月工作时数加上销售额提成再加上工龄工资
	//其中销售额提成等于该销售员当月售出商品金额的1％
	int SalaryPerHour;//每小时工资额
	int WorkHourThisMonth;//当月工作时数
	int SalesValueThisMonth;//当月售出商品金额
};
Salesman::Salesman(int WA, int SPH, int WHTM, int SVTM): Employee(WA)
{
	SalaryPerHour = SPH;
	WorkHourThisMonth = WHTM;
	SalesValueThisMonth = SVTM;
}
double Salesman::salary()
{
	return SalaryPerHour * WorkHourThisMonth + SalesValueThisMonth * DeductionCoefficient + WorkAge * WorkAgeSalary;
}

class Manager: public Employee
{
public:
	~Manager() {}
	Manager(int WA, int BS);
	double salary();
private:
	int BasicSalary;
};
Manager::Manager(int WA, int BS): Employee(WA)
{
	BasicSalary = BS;
}
double Manager::salary()
{
	return BasicSalary + WorkAge * WorkAgeSalary;
}

int main()
{
	Worker worker(1, 2, 3);
	Salesman salesman(4, 5, 6, 7);
	Manager manager(8, 9);

	cout << "Worker's salary is " << worker.salary() << endl;
	cout << "Salesman's salary is " << salesman.salary() << endl;
	cout << "Manager's salary is " << manager.salary() << endl;

	return 0;
}

