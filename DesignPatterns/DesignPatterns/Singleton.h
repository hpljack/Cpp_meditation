#include <string>
#include <list>
using namespace std;

class Singleton{
public:
	static Singleton* Instance(); //可以定义子类，必须用子类实例化
	static void Register(const string& name,Singleton* s);
protected:
	Singleton();
	static Singleton* Lookup(const string& name);
private:
	static Singleton* _instance;
	static List<NameSingletonPair>*_registery;
};


Singleton* Singleton::_instance = 0;

Singleton* Singleton::Instance(){
	if(_instance == 0)
		_instance = new Singleton();
	return _instance;
}