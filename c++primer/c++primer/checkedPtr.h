#ifndef CHECKED_PTR_H
#define CHECKED_PTR_H

/*
 * smart pointer: Checks access to elements throws an out_of_range
 *		          exception if attempt to access a nonexistent element
 *
 * user allocate and free the array
 */

class CheckedPtr{
public:
	CheckedPtr(int* b, int* e):beg(b),end(e),curr(b){}
	//prefix operators
	CheckedPtr& operator++();
	CheckedPtr& operator--();
	//postfix operators
	CheckedPtr operator++(int);
	CheckedPtr operator--(int);
private:
	int* beg;
	int* end;
	int* curr;
};

CheckedPtr& CheckedPtr::operator ++(){
	if(curr == end)
		throw out_of_range ("increment past the end of CheckedPtr");
	++curr;
	return *this;
}

CheckedPtr& CheckedPtr::operator --(){
	if(curr == beg)
		throw out_of_range("decrement past the beginning of CheckedPtr");
	--curr;
	return *this;
}

CheckedPtr CheckedPtr::operator ++(int){
	CheckedPtr ret(*this);
	++*this;
	return ret;
}

CheckedPtr CheckedPtr::operator --(int){
	CheckedPtr ret(*this);
	--*this;
	return ret;
}
#endif // !CHECKED_PTR_H
