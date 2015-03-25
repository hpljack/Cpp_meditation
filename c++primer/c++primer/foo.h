#ifndef FOO_H
#define FOO_H

#include <vector>
using std::vector;

class Foo{
public:
	int &operator[](const size_t);
	const int &operator[](const size_t)const;
private:
	vector<int> data;
};

int& Foo::operator [](const size_t index){
	return data[index];//no range checking on index
}

const int& Foo::operator [](size_t index)const{
	return data[index];//no range checking on index
}

#endif // !FOO_H
