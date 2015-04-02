#ifndef SPI_FUNC_H
#define SPI_FUNC_H
#include "InitSock.h"
#include <stdio.h>
#include <Ws2spi.h>
#include <SpOrder.h> //定义了WSCWriteProviderOrder函数

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Rpcrt4.lib")//实现了UuidCreate函数

// {92BB3309-AC23-423D-B495-39F83E207224}
GUID ProviderGuid = { 0x92bb3309, 0xac23, 0x423d, { 0xb4, 0x95, 0x39, 0xf8, 0x3e, 0x20, 0x72, 0x24 } };

LPWSAPROTOCOL_INFO GetProvider(LPINT lpnTotalProtocols);
void FreeProvider(LPWSAPROTOCOL_INFO pProtoInfo);
LPWSAPROTOCOL_INFOW GetProviderW(LPINT lpnTotalProtocols);
void FreeProviderW(LPWSAPROTOCOL_INFOW nProtoInfo);
void PrintAllProtocol();
int InstallProvider(WCHAR* wsDllIPPath);
void RemoveProvider();

#endif // !SPI_FUNC_H
