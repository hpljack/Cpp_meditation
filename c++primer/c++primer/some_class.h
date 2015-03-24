#ifndef SOME_CLASS_H
#define SOME_CLASS_H
#include <string>
using namespace std;

class First{
public:
	int memi;
	double mend;
};

class Second{
public:
	int memi;
	double mend;
};

//即使First 和Second有相同的数据域，但是还是不同的类型


typedef double Money;
class Account{
public:
	void applyint(){
		amount += amount * interestRate;		
	}
	static double rate(){return interestRate;}
	static void rate(double);//set a new rate
	Money balance(){return bal;} //use global defined of Money
private:
	//typedef double Money; //error: cannot change meaning of Money
	Money bal;
	string owner;
	double amount;
	static double interestRate;
	static double initRate(){return 0.943;}

	static const int period = 30;
	double daily_tbl[period];
};

double Account::interestRate = initRate();
const int Account::period;


#endif // !SOME_CLASS_H
