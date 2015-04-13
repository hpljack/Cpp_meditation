#include "SPI_func.h"


LPWSAPROTOCOL_INFOW GetProviderW(LPINT lpnTotalProtocols){

	int nError;
	DWORD dwSize = 0;
	LPWSAPROTOCOL_INFOW pProtoInfo = NULL;
	//取得需要的缓冲区长度
	if(::WSCEnumProtocols(NULL,pProtoInfo,&dwSize,&nError) == SOCKET_ERROR){
		if(::WSAGetLastError() != WSAENOBUFS)
			return NULL;
	}
	//申请缓冲区， 再次调用WSAEnumProtocols函数
	pProtoInfo = (LPWSAPROTOCOL_INFOW)::GlobalAlloc(GPTR,dwSize);
	*lpnTotalProtocols = ::WSCEnumProtocols(NULL,pProtoInfo,&dwSize,&nError);
	return pProtoInfo;
}

void FreeProviderW(LPWSAPROTOCOL_INFOW nProtoInfo){
	::GlobalFree(nProtoInfo);
}
LPWSAPROTOCOL_INFO GetProvider(LPINT lpnTotalProtocols){

	DWORD dwSize = 0;
	LPWSAPROTOCOL_INFO pProtoInfo = NULL;
	//取得需要的缓冲区长度
	if(::WSAEnumProtocols(NULL,pProtoInfo,&dwSize) == SOCKET_ERROR){
		if(::WSAGetLastError() != WSAENOBUFS)
			return NULL;
	}
	//申请缓冲区， 再次调用WSAEnumProtocols函数
	pProtoInfo = (LPWSAPROTOCOL_INFO)::GlobalAlloc(GPTR,dwSize);
	*lpnTotalProtocols = ::WSAEnumProtocols(NULL,pProtoInfo,&dwSize);
	return pProtoInfo;
}


void FreeProvider(LPWSAPROTOCOL_INFO pProtoInfo){
	::GlobalFree(pProtoInfo);
}

void PrintAllProtocol(){
	CInitSock initsock;

	printf("******PrintAllProtocol*********");

	int nTotalProtocols;
	LPWSAPROTOCOL_INFO pProtocolnfo = GetProvider(&nTotalProtocols);
	if(pProtocolnfo != NULL){
		//打印各个提供者的协议信息
		for (int i = 0; i != nTotalProtocols; ++i)
		{
			printf("Protocol:%s\n",pProtocolnfo[i].szProtocol);
			printf("CatalogEntryId:%d	ChainLen:%d\n",
				pProtocolnfo[i].dwCatalogEntryId,pProtocolnfo[i].ProtocolChain.ChainLen);
		}
		FreeProvider(pProtocolnfo);
	}
#ifdef DEBUG
	system("pause");
#endif // DEBUG
}

int InstallProvider(WCHAR* wszDlIPPath){

	WCHAR wszLSPName[] =L"TinyLSP";//我们的LSP名称
	int nError = NO_ERROR;
	LPWSAPROTOCOL_INFOW pProtoInfo;
	int nProtocols;
	WSAPROTOCOL_INFOW UDPLayeredInfo,UDPChainInfo; //我们要安装的UDP分层协议和协议链
	DWORD dwUdpOrigCatalogId,dwLayeredCatalogId;
	//在winsock目录中查找到原来的UDP服务提供者，为我们的LSP安装在它之上

	//枚举所有服务提供者
	pProtoInfo = GetProviderW(&nProtocols);
	for (int i = 0; i != nProtocols; ++i)
	{
		memcpy(&UDPChainInfo,&pProtoInfo[i],sizeof(UDPChainInfo));
		UDPChainInfo.dwServiceFlags1 = UDPChainInfo.dwServiceFlags1 & ~XP1_IFS_HANDLES;//去掉XP1_IFS_HANDLES标识
		dwUdpOrigCatalogId = pProtoInfo[i].dwCatalogEntryId;
		break;
	}

	//首先按分层协议 获取一个winsock库安排的目录ID号， 即dwLayeredCatalogId
	//直接用下层协议的WSAPROTO_INFOW的结构体即可
	memcpy(&UDPLayeredInfo,&UDPChainInfo,sizeof(UDPLayeredInfo));
	//修改协议名称 类型 设置PFL_HIDEDEN标志
	wcscpy(UDPLayeredInfo.szProtocol,wszLSPName);
	UDPLayeredInfo.ProtocolChain.ChainLen = LAYERED_PROTOCOL;//LAYERED_PROTOCOL即0
	UDPLayeredInfo.dwProviderFlags |= PFL_HIDDEN;
	//安装
	if(::WSCInstallProvider(&ProviderGuid,
		wszLSPName,&UDPLayeredInfo,1,&nError) == SOCKET_ERROR){
			return nError;
	}
	//重新枚举协议，获取分层协议的目录ID号
	FreeProviderW(pProtoInfo);
	pProtoInfo = GetProviderW(&nProtocols);
	for (int i = 0; i != nProtocols; ++i)
	{
		if (memcpy(&pProtoInfo[i].ProviderId,&ProviderGuid,sizeof(ProviderGuid)) == 0)
		{
			dwLayeredCatalogId = pProtoInfo[i].dwCatalogEntryId;
			break;
		}
	}

	//安装协议链
	//修改协议名称 类型
	WCHAR wszChainName[WSAPROTOCOL_LEN + 1];
	swprintf(wszChainName,L"%ws over%ws",wszLSPName,UDPChainInfo.szProtocol);
	wcscpy(UDPChainInfo.szProtocol,wszChainName);
	if (UDPChainInfo.ProtocolChain.ChainLen == 1)
	{
		UDPChainInfo.ProtocolChain.ChainEntries[1] = dwUdpOrigCatalogId;
	}else{
		for (int i = UDPChainInfo.ProtocolChain.ChainLen; i > 0; i--)
		{
			UDPChainInfo.ProtocolChain.ChainEntries[i] = UDPChainInfo.ProtocolChain.ChainEntries[i - 1];
		}
	}
	UDPChainInfo.ProtocolChain.ChainLen++;
	//将我们的分层协议置于协议链的顶层
	UDPChainInfo.ProtocolChain.ChainEntries[0] = dwLayeredCatalogId;
	//获取一个Guid 
	GUID ProviderChainGuid;
	if(::UuidCreate(&ProviderChainGuid) == RPC_S_OK){
		if(::WSCInstallProvider(&ProviderChainGuid,wszDlIPPath,&UDPChainInfo,1,&nError) == SOCKET_ERROR)
			return nError;
	}else
		return GetLastError();

	//重新排序winsock目录 将我们的协议链提前
	//重新枚举安装的协议
	FreeProviderW(pProtoInfo);
	pProtoInfo = GetProviderW(&nProtocols);
	DWORD dwIds[20];
	int nIndex = 0;
	//添加我们的协议连
	for (int i = 0; i != nProtocols; ++i)
	{
		if(pProtoInfo[i].ProtocolChain.ChainLen >1 && (pProtoInfo[i].ProtocolChain.ChainEntries[0] == dwLayeredCatalogId))
			dwIds[nIndex++] = pProtoInfo[i].dwCatalogEntryId;
	}
	//添加其他协议
	for (int i = 0; i != nProtocols; ++i)
	{
		if(pProtoInfo[i].ProtocolChain.ChainLen >1 || (pProtoInfo[i].ProtocolChain.ChainEntries[0] != dwLayeredCatalogId))
			dwIds[nIndex++] = pProtoInfo[i].dwCatalogEntryId;
	}
	//重新排序winsock目录
	nError = ::WSCWriteProviderOrder(dwIds,nIndex);
	FreeProviderW(pProtoInfo);
	return nError;
}

void RemoveProvider(){
	LPWSAPROTOCOL_INFOW pProtoInfo;
	int nProtocols;
	DWORD dwLayeredCatalogId;
	//根据Guid去的分层协议的目录ID
	pProtoInfo = GetProviderW(&nProtocols);
	int nError;
	for (int i = 0; i != nProtocols; ++i)
	{
		if (memcpy(&ProviderGuid,&pProtoInfo[i].ProviderId,sizeof(ProviderGuid)) == 0)
		{
			dwLayeredCatalogId = pProtoInfo[i].dwCatalogEntryId;
			break;
		}
		if(i < nProtocols){
			//移除协议链
			for(int i = 0; i != nProtocols; ++i){
				if(pProtoInfo[i].ProtocolChain.ChainLen > 1 && 
					(pProtoInfo[i].ProtocolChain.ChainEntries[0] == dwLayeredCatalogId))
				{
					::WSCDeinstallProvider(&pProtoInfo[i].ProviderId,&nError);
				}
			}
		//移除分层协议
		::WSCDeinstallProvider(&ProviderGuid,&nError);
		}
	}
}