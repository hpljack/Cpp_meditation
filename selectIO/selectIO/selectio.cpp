#include "../../common/InitSock.h"
#include <stdio.h>

CInitSock initsock;

int main(){
	
	USHORT nPort = 4567;
	SOCKET sListen = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY; //服务端一般这样这是地址

	//绑定套接字到本地机器
	if(::bind(sListen,(sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR){
		printf("Failed bind()\n");
		return -1;
	}

	//进入监听模式
	::listen(sListen,5);

	//select模型处理过程
	//1)初始化一个套接字fdsocket,添加监听套接字句柄到这个集合
	fd_set fdsocket;  //所有可用套接字集合
	FD_ZERO(&fdsocket);
	FD_SET(sListen,&fdsocket);

	while(TRUE){
		//2)将fdsocket集合的一个拷贝fdRead传递给select函数
		//  当有事情发生时，select函数移除fdRead集合中没有未决I/O操作的套接字句柄，然后返回
		fd_set fdRead = fdsocket;
		int nRet = ::select(0,&fdRead,NULL,NULL,NULL);
		if(nRet > 0){
			//3)通过将原来fdsocket集合与select处理过的fdread集合比较
			//  确定有哪些套接字有未决I/O, 并进一步处理这些I/O
			for (int i = 0; i != (int)fdsocket.fd_count; ++i)
			{
				if(FD_ISSET(fdsocket.fd_array[i],&fdRead)){
					if(fdsocket.fd_array[i] == sListen){//(1)监听套接字接收到新连接
						if(fdsocket.fd_count < FD_SETSIZE){
							sockaddr_in addrRemote;
							int nAddrLen = sizeof(addrRemote);
							SOCKET sNew = ::accept(sListen,(SOCKADDR*)&addrRemote,&nAddrLen);
							FD_SET(sNew,&fdsocket);
							printf("接收到连接%s\n",::inet_ntoa(addrRemote.sin_addr));
						}else{
							printf("too much connections!\n");
							continue;
						}
					}else{
						char szText[256];
						int nRecv = ::recv(fdsocket.fd_array[i],szText,strlen(szText),0);//可读
						if(nRecv > 0){
							szText[nRecv] = '\n';
							printf("接收到数据:%s",szText);
						}else{ //连接关闭 重启或中断
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