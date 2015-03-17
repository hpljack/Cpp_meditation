#include <string>
using namespace std;

class Foo{
public:
	Foo(){m_name = "foo";}
	Foo(const string& name):m_name(name){}
	~Foo(){}
private:
	string m_name;
};