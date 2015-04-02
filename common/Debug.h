#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef _DEBUG
#define ODS(szOut)\
{                     \
	OutputDebugString(szOut);\
}
#define  ODS1(szOut,var) \
{ \
	TCHAR sz[1024]; \
	_stprintf(sz,szOut,var);\
	OutputDebugString(sz);\
}
#else
#define ODS(szOut);
#define ODS1(szOut,var);
#endif // _DEBUG


#endif // !_DEBUG_H_
