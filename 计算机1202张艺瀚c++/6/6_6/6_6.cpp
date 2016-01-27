#include <iostream>
#include <cstring>

using namespace std;

const int max = 1000;

class Employee
{
	public:
		Employee();	
		void change_name();
		void display();
	private:
		char name[max];
		char st_addr[max];
		char city[max];
		char post_code[max];		
};
Employee::Employee()
{
	strcpy(name, "YihanZhang");
	strcpy(st_addr, "CultrureSt.");
	strcpy(city, "ShenYang");
	strcpy(post_code, "110004");
}
void Employee::change_name()
{
	memset(name, 0, sizeof(name));
	cout << "Please input your new name:" << endl;
	cin >> name;
}
void Employee::display()
{
	cout << "Name: " << name <<endl;
	cout << "Street address: " << st_addr << endl;
	cout << "City: " << city << endl;
	cout << "Post code: " << post_code << endl;
}

int main()
{
	Employee emp[5];

	for(int i = 0; i < 5; ++i)
	{
		cout << i + 1 << "." << endl;
		emp[i].display();
		cout << endl;
	}

	return 0;
}