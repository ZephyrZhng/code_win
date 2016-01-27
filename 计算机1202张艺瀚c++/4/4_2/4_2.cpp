#include <iostream>
using namespace std;

enum CPU_Rank {P1=1,P2,P3,P4,P5,P6,P7};
class CPU
{
	private:
		CPU_Rank rank;
		int frequency;
		float voltage;
	public:
		CPU(CPU_Rank r,int f,float v)
		{
				rank=r;
				frequency=f;
				voltage=v;
				cout<<"构造了一个CPU!"<<endl;
		}
		~CPU() { cout<<"析构了一个CPU!"<<endl; }
		CPU_Rank GetRank() const { return rank; }
		int GetFrequency() const { return frequency; }
		float GetVoltage() const { return voltage; }
		void SetRank(CPU_Rank r) { rank=r; }
		void SetFrequency(int f) { frequency=f; }
		void Setvoltage(float v) { voltage=v; }
		void Run() { cout<<"CPU 开始运行!"<<endl; }
		void Stop() { cout<<"CPU 停止运行!"<<endl; }
};

class RAM
{
	private:
		int ram;
	public:
		RAM(int r)
		{
			ram = r;
			cout << "构造了一个RAM！" << endl;
		}
		~RAM()
		{
			cout << "析构了一个RAM！" << endl;
		}
		int GetRAM() const
		{
			return ram;
		}
		void SetRAM(int r)
		{
			ram = r;
		}
		void Run()
		{
			cout << "RAM开始运行！" << endl;
		}
		void Stop()
		{
			cout << "RAM停止运行！" << endl;
		}
};

class CDROM
{
	private:
		int cdrom;
	public:
		CDROM(int c)
		{
			cdrom = c;
			cout << "构造了一个CDROM！" << endl;
		}
		~CDROM()
		{
			cout << "析构了一个CDROM！" << endl;
		}
		int GetCDROM() const
		{
			return cdrom;
		}
		void SetCDROM(int c)
		{
			cdrom = c;
		}
		void Run()
		{
			cout << "CDROM开始运行！" << endl;
		}
		void Stop()
		{
			cout << "CDROM停止运行！" << endl;
		}
};

class Computer
{
	private:
		CPU cpu;
		RAM ram;
		CDROM cdrom;
	public:
		Computer(CPU_Rank _rank, int _frequency, float _voltage, int _ram, int _cdrom);
		void run()
		{
			cout << "Computer开始运行！" << endl;
		}
		void stop()
		{
			cout << "Computer停止运行！" << endl;
		}
};
Computer::Computer(CPU_Rank _rank, int _frequency, float _voltage, int _ram, int _cdrom):
cpu(_rank, _frequency, _voltage), ram(_ram), cdrom(_cdrom) {}

int main()
{
	Computer MyComputer(P6, 300, 2.8, 10, 20);

	MyComputer.run();
	MyComputer.stop();

	return 0;
}

