#include "stdafx.h"
#include "Sales_item.h"


Sales_item::Sales_item(void)
{
}


Sales_item::~Sales_item(void)
{
}

Sales_item::Sales_item(std::string isbn,unsigned usold,double revenue){
	this->isbn = isbn;
	this->units_sold = usold;
	this->revenue = revenue;
}