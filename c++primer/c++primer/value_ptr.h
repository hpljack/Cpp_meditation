#ifndef VALUE_PTR_H
#define VALUE_PTR_H

class HasPtr{
public:
	HasPtr(const int&p, int i):ptr(new int(p)),val(i){}
	HasPtr(const HasPtr& orig):ptr(new int(*orig.ptr)),val(orig.val){}
	HasPtr& operator=(const HasPtr&);
	~HasPtr(){delete ptr;}

	int get_ptr_val()const{return *ptr;}
	int get_int()const{return val;}

	void set_ptr(int* p){ptr = p;}
	void set_int(int i){val = i;}

	int* get_ptr()const{return ptr;}
	void set_ptr_val(int val){*ptr = val;}
private:
	int* ptr;
	int val;
};

HasPtr& HasPtr::operator =(const HasPtr& rhs){
	*ptr = *rhs.ptr; //copy the value pointer to
	val = rhs.val;   //copy the int
	return *this;
}
#endif // !VALUE_PTR_H
