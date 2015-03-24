#include "stdafx.h"
#include "Sales_item.h"

Sales_item::Sales_item(const string& isbn,unsigned us,double rev){
	this->isbn = isbn;
	units_sold = us;
	revenue = rev;
}
Sales_item::Sales_item(std::istream&){

}

Sales_item::~Sales_item()
{
}

double Sales_item::avg_price()const{
	if (units_sold > 0)//if (units_sold)
		return revenue/units_sold;
	else
		return 0;
}

bool Sales_item::same_isbn(const Sales_item& rhs)const{
	return isbn == rhs.isbn;
}

Sales_item& Sales_item::operator=(const Sales_item& rhs){
	isbn = rhs.isbn;
	units_sold = rhs.units_sold;
	revenue = rhs.revenue;
	return *this;
}

Sales_item& Sales_item::operator+=(const Sales_item& rhs){
	if (isbn == rhs.isbn){
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
	}
	return *this;
}

Sales_item operator+(const Sales_item& s1,const Sales_item& s2){
	Sales_item ret(s1);
	ret += s2;//use operator+= 
	return ret;
}

inline bool
	operator==(const Sales_item& lhs,const Sales_item& rhs){
		return lhs.units_sold == rhs.units_sold &&
			lhs.revenue == rhs.revenue &&
			lhs.same_isbn(rhs);
}

inline bool
	operator!=(const Sales_item& lhs,const Sales_item& rhs){
		return !(lhs==rhs);//!= defined interm of operator==
}
//

std::istream& operator>>(std::istream& in,Sales_item& s){
	double price;
	in>>s.isbn>>s.units_sold>>price;
	if(in)
		s.revenue = s.units_sold * price;
	else
		s = Sales_item();//input failed, reset object to default state
	return in;
}

std::ostream& operator<<(std::ostream& os,const Sales_item& s){
	os<<s.isbn<<"\t"<<s.units_sold<<"\t"
		<<s.revenue<<"\t"<<s.avg_price();
	return os;
}


/*
 * 撤销类对象时会自动调用析构函数
 * 动态分配的对象只有在指向该对象的指针被删除时才撤销
 */
void destructor_test(){
	Sales_item* p = new Sales_item; 
	{//new scope
		Sales_item item(*p);//copy constructor copies *p into item
		delete p;//destructor called on object pointed to by p
	}//exit local scope; destructor called on item
}