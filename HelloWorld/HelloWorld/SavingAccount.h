class SavingAccount{
private:
	char m_name[40];
	char m_addr[100];
	double m_total;
public:
	static double m_rate;//ÀûÂÊ
	/*
public:
	static void setRate(double newRate){m_rate = newRate;}
	static double getRate(){return m_rate;}*/
};
void TestSavingAccount();