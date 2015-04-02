#ifndef SNIFFER_H
#define SNIFFER_H
#include "InitSock.h"
#include <stdio.h>
#include "ipheaderinfo.h"
#include <mstcpip.h>
void DecodeTCPPacket(char* pData);
void DecodeIPPacket(char* pData);
void Sniffer();
void GetFtp(char* pData,DWORD dwDestIP);
#endif // !SNIFFER_H
