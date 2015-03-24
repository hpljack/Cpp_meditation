#ifndef GETHOSTINFO_H
#define  GETHOSTINFO_H

#include <windows.h>
#include <stdio.h>
#include <iphlpapi.h>
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")

//全局数据
u_char g_ucLocalMac[6]; //local mac addr
DWORD g_dwGatewayIp;  //gateway ip
DWORD g_dwLocalIp;    //local ip
DWORD g_dwMask;     //子网掩码

BOOL GetGlobalData(){
	printf("GetGlobalData\n");

	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	ULONG ulLen = 0;

	//为适配器机构申请内存
	::GetAdaptersInfo(pAdapterInfo,&ulLen);
	pAdapterInfo = (PIP_ADAPTER_INFO)::GlobalAlloc(GPTR,ulLen);

	//获取本地适配器
	if(::GetAdaptersInfo(pAdapterInfo,&ulLen) == ERROR_SUCCESS){

		if(pAdapterInfo != NULL){
			memcpy(g_ucLocalMac,pAdapterInfo->Address,6);
			g_dwGatewayIp = ::inet_addr(pAdapterInfo->GatewayList.IpAddress.String);
			g_dwLocalIp = ::inet_addr(pAdapterInfo->IpAddressList.IpAddress.String);
			g_dwMask = ::inet_addr(pAdapterInfo->IpAddressList.IpMask.String);
		}
	}

	printf("\n------------------本机信息--------------------\n");
	in_addr in;
	in.S_un.S_addr = g_dwLocalIp;
	printf("  IP Address:%s\n",::inet_ntoa(in));

	in.S_un.S_addr = g_dwMask;
	printf("  Subnet Mask:%s\n",::inet_ntoa(in));

	in.S_un.S_addr = g_dwGatewayIp;
	printf("  Default Gateway:%s\n",::inet_ntoa(in));

	u_char* p = g_ucLocalMac;
	printf("  MAC Address:%02X-%02X-%02X-%02X-%02X-%02X\n",p[0],p[1],p[2],p[3],p[4],p[5]);

	printf("\n");

	return TRUE;
}


#endif // !GETHOSTINFO_H
