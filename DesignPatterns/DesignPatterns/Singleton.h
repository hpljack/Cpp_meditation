#include <string>
#include <list>
using namespace std;

class Singleton{
public:
	static Singleton* Instance(); //���Զ������࣬����������ʵ����
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