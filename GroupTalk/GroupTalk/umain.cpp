#include "GroupTalk.h"
#include "..\..\common\rawudp.h"
#include "..\..\common\Sniffer.h"

int main(){

	SendUDPPacketTest();
	Sniffer();

	system("pause");
	return 0;
}