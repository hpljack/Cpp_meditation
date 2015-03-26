#include "../../common/InitSock.h"
#include <stdio.h>

CInitSock initsock;

int main(){
	
	USHORT nPort = 4567;
	SOCKET sListen = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY; //�����һ���������ǵ�ַ

	//���׽��ֵ����ػ���
	if(::bind(sListen,(sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR){
		printf("Failed bind()\n");
		return -1;
	}

	//�������ģʽ
	::listen(sListen,5);

	//selectģ�ʹ������
	//1)��ʼ��һ���׽���fdsocket,��Ӽ����׽��־�����������
	fd_set fdsocket;  //���п����׽��ּ���
	FD_ZERO(&fdsocket);
	FD_SET(sListen,&fdsocket);

	while(TRUE){
		//2)��fdsocket���ϵ�һ������fdRead���ݸ�select����
		//  �������鷢��ʱ��select�����Ƴ�fdRead������û��δ��I/O�������׽��־����Ȼ�󷵻�
		fd_set fdRead = fdsocket;
		int nRet = ::select(0,&fdRead,NULL,NULL,NULL);
		if(nRet > 0){
			//3)ͨ����ԭ��fdsocket������select�������fdread���ϱȽ�
			//  ȷ������Щ�׽�����δ��I/O, ����һ��������ЩI/O
			for (int i = 0; i != (int)fdsocket.fd_count; ++i)
			{
				if(FD_ISSET(fdsocket.fd_array[i],&fdRead)){
					if(fdsocket.fd_array[i] == sListen){//(1)�����׽��ֽ��յ�������
						if(fdsocket.fd_count < FD_SETSIZE){
							sockaddr_in addrRemote;
							int nAddrLen = sizeof(addrRemote);
							SOCKET sNew = ::accept(sListen,(SOCKADDR*)&addrRemote,&nAddrLen);
							FD_SET(sNew,&fdsocket);
							printf("���յ�����%s\n",::inet_ntoa(addrRemote.sin_addr));
						}else{
							printf("too much connections!\n");
							continue;
						}
					}else{
						char szText[256];
						int nRecv = ::recv(fdsocket.fd_array[i],szText,strlen(szText),0);//�ɶ�
						if(nRecv > 0){
							szText[nRecv] = '\n';
							printf("���յ�����:%s",szText);
						}else{ //���ӹر� �������ж�
							::closesocket(fdsocket.fd_array[i]);
							FD_CLR(fdsocket.fd_array[i],&fdsocket);
						}
					}
				}
			}
		}else{
			printf("Failed select()\n");
			break;
		}
	}
	
	return 0;
}