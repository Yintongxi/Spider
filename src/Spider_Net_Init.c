#include <spider_include.h>


int Spider_Net_Init()
{
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8000);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int mysock;
	mysock = socket(AF_INET,SOCK_STREAM,0);
	printf("Spider Step[1] Spider Net Init Success, Socket[%d]\n",mysock);
	//bind(mysock,(struct sockaddr *)&myaddr,sizeof(myaddr));
	return mysock;

}
