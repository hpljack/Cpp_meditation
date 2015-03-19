// chapter5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class Vehicle{
public:
	virtual double weight()const=0;
	virtual void start()=0;
	virtual Vehicle* copy()const=0;
	virtual ~Vehicle(){}
};

class RoadVehicle: public Vehicle{
public:
	virtual double weight()const{return 2;}
	virtual void start(){cout<<"RoadVehicle start"<<endl;}
	virtual Vehicle* copy()const{ return new RoadVehicle(*this);} //产生一个新的副本
	~RoadVehicle(){}
};

class AutoVehicle: public RoadVehicle{
public:
	virtual double weight()const{ return 0;}
	virtual void start(){cout<<"AutoVehicle start"<<endl;}
	virtual Vehicle* copy()const{return new AutoVehicle(*this);}
	~AutoVehicle(){}
};
class Aircraft: public Vehicle{
public:
	virtual double weight()const{return 0;}
	virtual void start(){cout<<"Aircraft  start"<<endl;}
	virtual Vehicle* copy()const{return new Aircraft(*this);}
	~Aircraft(){}
};
class Helicopter: public Aircraft{
public:
	virtual double weight()const{return 0;}
	virtual void start(){cout<<"Helicopter start"<<endl;}
	virtual Vehicle* copy()const{return new Helicopter(*this);}
	~Helicopter(){}
};

//定义代理类
class VehicleSurrogate{
public:
	VehicleSurrogate();
	VehicleSurrogate(const Vehicle& v);
	~VehicleSurrogate();
	VehicleSurrogate(const VehicleSurrogate& vs);
	VehicleSurrogate& operator=(const VehicleSurrogate& vs);

	//来自Vehicle的操作
	double weight()const;
	void start();
private:
	Vehicle* vp;
};


VehicleSurrogate::VehicleSurrogate():vp(0){}
VehicleSurrogate::VehicleSurrogate(const Vehicle& v):vp(v.copy()){}
VehicleSurrogate::~VehicleSurrogate(){
	delete vp;
}
VehicleSurrogate::VehicleSurrogate(const VehicleSurrogate& vs):vp(vs.vp? vp->copy(): 0){}
VehicleSurrogate& VehicleSurrogate::operator=(const VehicleSurrogate& vs){
	if(this != &vs){
		delete vp;
		vp = (vs.vp? vs.vp->copy(): 0);
	}
	return *this;
}

double VehicleSurrogate::weight()const{
	if(vp == 0)
		throw "empty VehicleSurrogate.weight()";
	return vp->weight();
}

void VehicleSurrogate::start(){
	if(vp == 0)
		throw "empty VehicleSurrogate.start()";
	vp->start();
}

int _tmain(int argc, _TCHAR* argv[])
{
	int num_vehicles = 0;
	VehicleSurrogate parking_lot[1000];
	RoadVehicle x;
	AutoVehicle y;
	Aircraft z;
	Helicopter helicopter;
	parking_lot[num_vehicles++] = x; //copy x to parking_lot[0] 产生副本
	parking_lot[num_vehicles++] = y;
	parking_lot[num_vehicles++] = z;

	for(int i = 0; i != num_vehicles; ++i){
		parking_lot[i].start();
	}
	cin.get();
	return 0;
}

