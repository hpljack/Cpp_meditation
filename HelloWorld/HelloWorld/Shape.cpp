#include "stdafx.h"
#include "Shape.h"
#include <iostream>


CShape::CShape(void)
{
}


CShape::~CShape(void)
{
}

void CShape::display(void)
{
	std::cout<<"This is a CShape"<<std::endl;
}

void CShape::setColor(int color){
	m_color = color;
}

void CRect::display(void){
	std::cout<<"This is a CRect"<<std::endl;
}

void CEllipse::display(void){
	std::cout<<"This is a CEllipse"<<std::endl;
}

void CTriangle::display(void){
	std::cout<<"This is a CTriangle"<<std::endl;
}

void CSquare::display(void){
	std::cout<<"This is a CSquare"<<std::endl;
}

void CCirle::display(void){
	std::cout<<"This is a CCirle"<<std::endl;
}
