#pragma once
#include <string.h>
class CEmployee //员工
{
public:
	CEmployee(void);
	virtual ~CEmployee(void);
	CEmployee(const char* nm){strcpy_s(m_name,nm);}
	char* getName(){return m_name;}
	virtual float computePay(){return 0;}
private:
	char m_name[30];
};

class CWage: public CEmployee{ //时薪职员
private:
	float m_wage;
	float m_hours;
public:
	CWage(const char* nm): CEmployee(nm){m_wage = 250.0; m_hours = 40.0;}
	void SetWage(float wg){m_wage = wg;}
	void SetHours(float hrs){m_hours = hrs;}
	float computePay();
};

class CSales: public CWage{//销售
private:
	float m_comm;
	float m_sale;
public:
	CSales(const char* nm):CWage(nm){m_comm = m_sale = 0.0;}
	void setComm(float comm){m_comm = comm;}
	void setSale(float sale){m_sale = sale;}
	float computePay();
};

class CManager: public CEmployee{//经理
private:
	float  m_salary;
public:
	CManager(const char* nm): CEmployee(nm){m_salary = 99999;}
	void setSalary(float salary){m_salary = salary;}
	float computePay();
};
