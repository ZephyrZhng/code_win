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
				cout<<"������һ��CPU!"<<endl;
		}
		~CPU() { cout<<"������һ��CPU!"<<endl; }
		CPU_Rank GetRank() const { return rank; }
		int GetFrequency() const { return frequency; }
		float GetVoltage() const { return voltage; }
		void SetRank(CPU_Rank r) { rank=r; }
		void SetFrequency(int f) { frequency=f; }
		void Setvoltage(float v) { voltage=v; }
		void Run() { cout<<"CPU ��ʼ����!"<<endl; }
		void Stop() { cout<<"CPU ֹͣ����!"<<endl; }
};

class RAM
{
	private:
		int ram;
	public:
		RAM(int r)
		{
			ram = r;
			cout << "������һ��RAM��" << endl;
		}
		~RAM()
		{
			cout << "������һ��RAM��" << endl;
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
			cout << "RAM��ʼ���У�" << endl;
		}
		void Stop()
		{
			cout << "RAMֹͣ���У�" << endl;
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
			cout << "������һ��CDROM��" << endl;
		}
		~CDROM()
		{
			cout << "������һ��CDROM��" << endl;
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
			cout << "CDROM��ʼ���У�" << endl;
		}
		void Stop()
		{
			cout << "CDROMֹͣ���У�" << endl;
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
			cout << "Computer��ʼ���У�" << endl;
		}
		void stop()
		{
			cout << "Computerֹͣ���У�" << endl;
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

