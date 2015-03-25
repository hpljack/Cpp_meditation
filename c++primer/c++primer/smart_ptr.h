#ifndef SMART_PTR_H
#define  SMART_PTR_H

class HasPtr{
public:
	//HasPtr owns the pointer, p must been dynamically allocalted
	HasPtr(int *p, int i):ptr(new U_ptr(p)),val(i){}
	//copy memebers and increment the use count
	HasPtr(const HasPtr& orig):
		ptr(orig.ptr),val(orig.val){ ++ptr->use;}
	HasPtr& operator=(const HasPtr&);
	//if use count goes zero, delete th U_ptr object
	~HasPtr(){
		if (--ptr->use == 0)
			delete ptr;
	}
	
	int *get_ptr()const{return ptr->ip;}
	int get_int()const{return val;}
	
	void set_ptr(int *p){ptr->ip = p;}
	void set_int(int i){val = i;}

	int get_ptr_val()const{return *ptr->ip;}
	void set_ptr_val(int val){*ptr->ip = i;}
private:
	U_ptr* ptr;
	int val;
};

//private class for use by HasPtr only
class U_ptr{
	friend class HasPtr;
	int *ip; 
	size_t use;
	U_ptr(int* p):ip(p),use(1){}
	~U_ptr(){delete ip;}
};

HasPtr& HasPtr::operator =(const HasPtr& rhs){
	++rhs.ptr->use;//increment use count on rhs first
	if(--ptr->use == 0) //if use count goes to 0 on this object, delete it
		delete ptr;
	ptr = rhs.ptr;//copy the U_ptr
	val = rhs.val;//copy the int member
	return *this;
}

#endif // !SMART_PTR_H
