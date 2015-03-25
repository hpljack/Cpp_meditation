#ifndef SALESITEM_H
#define SALESITEM_H

#pragma once
#include <string>
#include <iostream>
#include <istream>
#include <ostream>
using std::string;

class Sales_item
{
public:
	Sales_item():units_sold(0),revenue(0){} //���캯���ĳ�ʼ���б�
	//Sales_item(const string& isbn=""):units_sold(0),revenue(0){this->isbn = isbn;}
	Sales_item(const string& isbn,unsigned us,double rev);
	Sales_item(std::istream&);
	Sales_item(const string& book):isbn(book),units_sold(0),revenue(0){}
	virtual ~Sales_item();

	//copy	constructor
	Sales_item(const Sales_item& orig):
		isbn(orig.isbn),
		units_sold(orig.units_sold),
		revenue(orig.revenue){}
	//��ֵ������
	Sales_item& operator=(const Sales_item& rhs);
	Sales_item& operator+=(const Sales_item& rhs);//���ϸ�ֵ
	friend Sales_item operator+(const Sales_item&,const Sales_item&);
	friend inline bool operator==(const Sales_item&,const Sales_item&);
	friend inline bool operator!=(const Sales_item&,const Sales_item&);

	//����Ա���� const member function
	double avg_price()const; //const��Ա����
	bool same_isbn(const Sales_item& rhs) const;
private:
	string isbn;
	unsigned units_sold;
	double revenue;

	friend std::istream& operator>>(std::istream&,Sales_item&);
	friend std::ostream& operator<<(std::ostream&,const Sales_item&);
};


void destructor_test();


#endif
  