// ComDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <malloc.h>
#include <iostream>
#include <objbase.h>

using std::cout;
using std::endl;
using std::cin;

//GUIDS
// {E8AA3695-F8DB-4867-B3D0-CDB3F25E49BF}
static const IID IID_IX = 
{ 0xe8aa3695, 0xf8db, 0x4867, { 0xb3, 0xd0, 0xcd, 0xb3, 0xf2, 0x5e, 0x49, 0xbf } };

// {3D47B3BB-6305-449F-9DC2-712E8A73175D}
static const IID IID_IY = 
{ 0x3d47b3bb, 0x6305, 0x449f, { 0x9d, 0xc2, 0x71, 0x2e, 0x8a, 0x73, 0x17, 0x5d } };

// {20CE45F8-58BF-4683-A19C-F908388E25D6}
static const IID IID_IZ = 
{ 0x20ce45f8, 0x58bf, 0x4683, { 0xa1, 0x9c, 0xf9, 0x8, 0x38, 0x8e, 0x25, 0xd6 } };

//interface 
__interface IX: IUnknown
{
	virtual void _stdcall fx(void) = 0;
};
__interface IY: IUnknown
{
	virtual void _stdcall fy(void) = 0;
};

__interface IZ: IUnknown
{
	virtual void _stdcall fz(void) = 0;
};


//define the COM object
class CCOM_OBJECT: public IX, public IY{
public:
	CCOM_OBJECT(): ref_count(0){}
	~CCOM_OBJECT(){}
private:
	virtual HRESULT _stdcall QueryInterface(const GUID &iid, void **iface);
	virtual ULONG _stdcall AddRef();
	virtual ULONG _stdcall Release();

	virtual void _stdcall fx(void){
		cout<<" function fx has been called."<<endl;
	}
	virtual void _stdcall fy(void){
		cout<<" function fy has been called."<<endl;
	}

	int ref_count;
};

HRESULT _stdcall CCOM_OBJECT::QueryInterface(const GUID &iid, void **iface){
	// this function basically casts the this pointer or the IUnknown
	// pointer into the interface requested ,notice the comparision with 
	// the GUIDs generated and defined in the beginning of program
	if(iid == IID_IUnknown){
		cout<<" Requesting IUnknown interface"<<endl;
		*iface = (IX*)this;
	}
	if (iid == IID_IX){
		cout<<" Requesting IX interface"<<endl;
		*iface = (IX*)this;
	}else if (iid == IID_IY){
		cout<<" Requesting IY interface"<<endl;
		*iface = (IY*)this;
	}else{
		cout<<"Requesting Unknown interface"<<endl;
		*iface = NULL;
		return (E_NOINTERFACE);
	}

	//if everything wen well cast pointer to 
	//IUnknown and call addref()
	((IUnknown*)(*iface))->AddRef();
	return S_OK;
}

ULONG _stdcall CCOM_OBJECT::AddRef(){
	//increment reference count
	cout<<"Adding a reference "<<endl;
	return(++ref_count);
}

ULONG _stdcall CCOM_OBJECT::Release(){
	//decrement reference count
	cout<<"Deleting a reference"<<endl;
	if (--ref_count == 0){
		delete this;
		return (0);
	}else
	{
		return (ref_count);
	}
}
IUnknown* CoCreateInstance(void){
	//this is a very basic implemention of coCreateInstance()
	// it creates an instance of the COM object, in this case
	// T decided to start with a pointer to IX-IY would have
	// done just as well
	IUnknown* comm_obj = (IX *) new(CCOM_OBJECT);
	cout<<"Creating Comm object"<<endl;
	comm_obj->AddRef();
	return comm_obj;
}

int _tmain(int argc, _TCHAR* argv[])
{
	IUnknown* punknown = CoCreateInstance();

	IX *pix = NULL;
	IY *piy = NULL;

	punknown->QueryInterface(IID_IX,(void **)&pix);
	pix->fx();
	pix->Release();

	punknown->QueryInterface(IID_IY,(void **)&piy);
	piy->fy();
	piy->Release();

	punknown->Release();

	cin.get();
	return 0;
}

