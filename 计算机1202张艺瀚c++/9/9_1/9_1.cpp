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

//���乤�ʾ��ǹ�Ա�ڸù�˾�����Ĺ���ÿ����1�꣬�¹��ʾ�����35Ԫ

class Worker: public Employee
{
	//ÿСʱ���ʶ�˵��¹���ʱ���ټ��Ϲ��乤��
public:
	Worker(int WA, int SPH, int WHTM);
	~Worker() {}
	double salary();
private:
	int SalaryPerHour;//ÿСʱ���ʶ�
	int WorkHourThisMonth;//���¹���ʱ��
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
	//ÿСʱ���ʶ�˵��¹���ʱ���������۶�����ټ��Ϲ��乤��
	//�������۶���ɵ��ڸ�����Ա�����۳���Ʒ����1��
	int SalaryPerHour;//ÿСʱ���ʶ�
	int WorkHourThisMonth;//���¹���ʱ��
	int SalesValueThisMonth;//�����۳���Ʒ���
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

