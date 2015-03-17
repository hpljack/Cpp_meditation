#ifndef SALESITEM_H
#define SALESITEM_H

#pragma once
#include <string>
class Sales_item
{
public:
	Sales_item(void);
	Sales_item(std::string isbn,unsigned usold,double revenue);
	virtual ~Sales_item(void);
private:
	std::string isbn;
	unsigned units_sold;
	double revenue;
};

#endif
