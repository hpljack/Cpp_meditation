#include "stdafx.h"
#include "Employee.h"


CEmployee::CEmployee(void)
{
}


CEmployee::~CEmployee(void)
{
}

float CWage::computePay(){
	return m_wage * m_hours;
}

float CSales::computePay(){
	return CWage::computePay() + m_comm * m_sale;
}

float CManager::computePay(){
	return m_salary;
}