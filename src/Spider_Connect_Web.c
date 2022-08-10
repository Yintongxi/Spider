#include <spider_include.h>



int Spider_Connect_Web(int sockfd,url_t * node)
{
	struct sockaddr_in webAddr;
	bzero(&webAddr,sizeof(webAddr));
	webAddr.sin_family = AF_INET;
	webAddr.sin_port = htons(node->port);
	inet_pton(AF_INET,node->ip,&webAddr.sin_addr.s_addr);

	if((connect(sockfd,(struct sockaddr *)&webAddr,sizeof(webAddr)))==-1)
	{
			perror("Spider_Connect_Web >> Connect call Failed");
			return -1;
	}
	printf("Spider Step [3] Connect Web Success...\n ");
	return 0;
}
