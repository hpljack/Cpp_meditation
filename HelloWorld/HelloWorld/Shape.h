#pragma once
class CShape
{
public:
	CShape(void);
	virtual ~CShape(void);
private:
	int m_color;
public:
	//virtual void display(void);
	virtual void display() =0;  //pure vitural function , the class is abstract class 拥有纯虚函数的类为抽象类 不能实例化
	void setColor(int color); 
};

class CRect: public CShape{ //矩形
public:
	//CRect(void);
	//virtual ~CRect(void);
public:
	void display(void);
};

class CEllipse: public CShape{//椭圆
public:
	//CEllipse(void);
	//virtual ~CEllipse(void);
public:
	void display(void);
};

class CTriangle: public CShape{//三角形
public:
	//CTriangle(void);
	//virtual ~CTriangle(void);
public:
	void display(void);
};

class CSquare: public CRect{ //四方形
public:
	//CSquare(void);
	//virtual ~CSquare(void);
public:
	void display(void);
};

class CCirle: public CEllipse{//圆形
public:
	//CCirle(void);
	//virtual ~CCirle(void);
public:
	void display(void);
};