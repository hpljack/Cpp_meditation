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
	virtual void display() =0;  //pure vitural function , the class is abstract class ӵ�д��麯������Ϊ������ ����ʵ����
	void setColor(int color); 
};

class CRect: public CShape{ //����
public:
	//CRect(void);
	//virtual ~CRect(void);
public:
	void display(void);
};

class CEllipse: public CShape{//��Բ
public:
	//CEllipse(void);
	//virtual ~CEllipse(void);
public:
	void display(void);
};

class CTriangle: public CShape{//������
public:
	//CTriangle(void);
	//virtual ~CTriangle(void);
public:
	void display(void);
};

class CSquare: public CRect{ //�ķ���
public:
	//CSquare(void);
	//virtual ~CSquare(void);
public:
	void display(void);
};

class CCirle: public CEllipse{//Բ��
public:
	//CCirle(void);
	//virtual ~CCirle(void);
public:
	void display(void);
};