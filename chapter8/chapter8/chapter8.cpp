// chapter8.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <ostream>
#include <iostream>
#include <string>

using namespace std;

class Expr;

class Expr_node{
private:
	friend ostream& operator<<(ostream&, const Expr_node&);
	friend class Expr; //友元可以访问该类的私有变量和成员函数
	int use; //引用计数
protected:
	Expr_node():use(1){}
	virtual ~Expr_node(){}
public:
	virtual void print(ostream&)const=0;
	virtual int eval()const=0;
};

ostream& operator<<(ostream& o, const Expr_node& e){
	e.print(o);
	return o;
}


class Int_node: public Expr_node{ //Int结点
private:
	friend class Expr;
	int n;
	Int_node(int k):n(k){}
	void print(ostream& o)const{o<<n;}
	int eval()const{return n;}
};

class Unary_node: public Expr_node{ //一元结点
private:
	friend class Expr;
	string op;    //操作符
	Expr_node* opnd;
	Unary_node(const string& a, Expr_node* b):op(a),opnd(b){}
	void print(ostream& o)const{
		o<<"("<<op<<*opnd<<")";
	}
	int eval()const;
};
int Unary_node::eval()const{
	if(op == "-")
		return -opnd->eval();
	throw "error , bad op" + op + " in Unary_node";
}

class Binary_node: public Expr_node{//二元结点
private:
	friend class Expr;
	string op;
	Expr_node* left;
	Expr_node* right;

	Binary_node(const string& a, Expr_node* b, Expr_node* c):
		op(a),left(b),right(c){}
	void print(ostream& o)const{
		o<<"("<<*left<<op<<*right<<")";
	}
	int eval()const;
};
int Binary_node::eval()const{
	int op1 = left->eval();
	int op2 = right->eval();

	if(op == "-") return op1 - op2;
	if(op == "+") return op1 + op2;
	if(op == "*") return op1 * op2;
	if(op == "/" && op2 != 0) return op1 / op2;
	throw "error ,bad op "+ op +" in Binary_node";
}

class Expr{
public:
	Expr(int);
	Expr(const string&,Expr&);
	Expr(const string&,Expr&,Expr&);
	Expr(const Expr&);
	Expr& operator=(const Expr&);
	~Expr(){delete p;}
private:
	Expr_node* p;
	friend ostream& operator<<(ostream&, const Expr&);
};

Expr::Expr(int n){
	p = new Int_node(n);
}
Expr::Expr(const string& op,Expr& t){
	p = new Unary_node(op,t);
}
Expr::Expr(const string& op,Expr& left,Expr& right){
	p = new Binary_node(op,left.p,right.p);
}
Expr::Expr(const Expr& t){
	p = t.p; 
	++p->use;
}
Expr& Expr::operator=(const Expr& rhs){
	rhs.p->use++;
	if(--p->use == 0)
		delete p;
	p = rhs.p;
	return *this;
}
ostream& operator<<(ostream& o, const Expr& e){
	e.p->print(o);
	return o;
}

int _tmain(int argc, _TCHAR* argv[])
{
//	Binary_node* t = new Binary_node("+",new Int_node(3),new Int_node(5));
	Expr t = Expr("*",Expr("-",Expr(5)),Expr("+",Expr(3),Expr(4)));
	Expr t2 = Expr("-",Expr(3));
	cout<<t2<<endl;

	t = Expr("*",t,t);
	//cout<<t<<endl;

	cin.get();
	return 0;
}

