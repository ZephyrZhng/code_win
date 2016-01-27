//"TimeType.h"
class TimeType{
	public:
		void Set(int hours, int minutes, int seconds);
		void Increment();
		void Write() const;
		bool Equal(TimeType otherTime) const;
		bool LessThan(TimeType otherTime) const;
	private:
		int hrs;
		int mins;
		int secs;
};
