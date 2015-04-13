#include "SPI_func.h"


LPWSAPROTOCOL_INFOW GetProviderW(LPINT lpnTotalProtocols){

	int nError;
	DWORD dwSize = 0;
	LPWSAPROTOCOL_INFOW pProtoInfo = NULL;
	//ȡ����Ҫ�Ļ���������
	if(::WSCEnumProtocols(NULL,pProtoInfo,&dwSize,&nError) == SOCKET_ERROR){
		if(::WSAGetLastError() != WSAENOBUFS)
			return NULL;
	}
	//���뻺������ �ٴε���WSAEnumProtocols����
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
	//ȡ����Ҫ�Ļ���������
	if(::WSAEnumProtocols(NULL,pProtoInfo,&dwSize) == SOCKET_ERROR){
		if(::WSAGetLastError() != WSAENOBUFS)
			return NULL;
	}
	//���뻺������ �ٴε���WSAEnumProtocols����
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
		//��ӡ�����ṩ�ߵ�Э����Ϣ
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

	WCHAR wszLSPName[] =L"TinyLSP";//���ǵ�LSP����
	int nError = NO_ERROR;
	LPWSAPROTOCOL_INFOW pProtoInfo;
	int nProtocols;
	WSAPROTOCOL_INFOW UDPLayeredInfo,UDPChainInfo; //����Ҫ��װ��UDP�ֲ�Э���Э����
	DWORD dwUdpOrigCatalogId,dwLayeredCatalogId;
	//��winsockĿ¼�в��ҵ�ԭ����UDP�����ṩ�ߣ�Ϊ���ǵ�LSP��װ����֮��

	//ö�����з����ṩ��
	pProtoInfo = GetProviderW(&nProtocols);
	for (int i = 0; i != nProtocols; ++i)
	{
		memcpy(&UDPChainInfo,&pProtoInfo[i],sizeof(UDPChainInfo));
		UDPChainInfo.dwServiceFlags1 = UDPChainInfo.dwServiceFlags1 & ~XP1_IFS_HANDLES;//ȥ��XP1_IFS_HANDLES��ʶ
		dwUdpOrigCatalogId = pProtoInfo[i].dwCatalogEntryId;
		break;
	}

	//���Ȱ��ֲ�Э�� ��ȡһ��winsock�ⰲ�ŵ�Ŀ¼ID�ţ� ��dwLayeredCatalogId
	//ֱ�����²�Э���WSAPROTO_INFOW�Ľṹ�弴��
	memcpy(&UDPLayeredInfo,&UDPChainInfo,sizeof(UDPLayeredInfo));
	//�޸�Э������ ���� ����PFL_HIDEDEN��־
	wcscpy(UDPLayeredInfo.szProtocol,wszLSPName);
	UDPLayeredInfo.ProtocolChain.ChainLen = LAYERED_PROTOCOL;//LAYERED_PROTOCOL��0
	UDPLayeredInfo.dwProviderFlags |= PFL_HIDDEN;
	//��װ
	if(::WSCInstallProvider(&ProviderGuid,
		wszLSPName,&UDPLayeredInfo,1,&nError) == SOCKET_ERROR){
			return nError;
	}
	//����ö��Э�飬��ȡ�ֲ�Э���Ŀ¼ID��
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

	//��װЭ����
	//�޸�Э������ ����
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
	//�����ǵķֲ�Э������Э�����Ķ���
	UDPChainInfo.ProtocolChain.ChainEntries[0] = dwLayeredCatalogId;
	//��ȡһ��Guid 
	GUID ProviderChainGuid;
	if(::UuidCreate(&ProviderChainGuid) == RPC_S_OK){
		if(::WSCInstallProvider(&ProviderChainGuid,wszDlIPPath,&UDPChainInfo,1,&nError) == SOCKET_ERROR)
			return nError;
	}else
		return GetLastError();

	//��������winsockĿ¼ �����ǵ�Э������ǰ
	//����ö�ٰ�װ��Э��
	FreeProviderW(pProtoInfo);
	pProtoInfo = GetProviderW(&nProtocols);
	DWORD dwIds[20];
	int nIndex = 0;
	//������ǵ�Э����
	for (int i = 0; i != nProtocols; ++i)
	{
		if(pProtoInfo[i].ProtocolChain.ChainLen >1 && (pProtoInfo[i].ProtocolChain.ChainEntries[0] == dwLayeredCatalogId))
			dwIds[nIndex++] = pProtoInfo[i].dwCatalogEntryId;
	}
	//�������Э��
	for (int i = 0; i != nProtocols; ++i)
	{
		if(pProtoInfo[i].ProtocolChain.ChainLen >1 || (pProtoInfo[i].ProtocolChain.ChainEntries[0] != dwLayeredCatalogId))
			dwIds[nIndex++] = pProtoInfo[i].dwCatalogEntryId;
	}
	//��������winsockĿ¼
	nError = ::WSCWriteProviderOrder(dwIds,nIndex);
	FreeProviderW(pProtoInfo);
	return nError;
}

void RemoveProvider(){
	LPWSAPROTOCOL_INFOW pProtoInfo;
	int nProtocols;
	DWORD dwLayeredCatalogId;
	//����Guidȥ�ķֲ�Э���Ŀ¼ID
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
			//�Ƴ�Э����
			for(int i = 0; i != nProtocols; ++i){
				if(pProtoInfo[i].ProtocolChain.ChainLen > 1 && 
					(pProtoInfo[i].ProtocolChain.ChainEntries[0] == dwLayeredCatalogId))
				{
					::WSCDeinstallProvider(&pProtoInfo[i].ProviderId,&nError);
				}
			}
		//�Ƴ��ֲ�Э��
		::WSCDeinstallProvider(&ProviderGuid,&nError);
		}
	}
}