#include <spider_include.h>


int Spider_Interactive_Process(url_t * node)
{
	char Requst[4096];
	ssl_t * ssl = NULL;

	int sock = Spider_Net_Init();
	Spider_Analytical_URL(node);
	Spider_Connect_Web(sock,node);
	
	Spider_Create_RequestHead(node,Requst);
	if(node->http_type)
	  ssl =  Spider_Openssl_Create(sock);

	if((Spider_Download_HTML(sock,Requst,*node,ssl))==0)
	  return 0;
	else
	  return -1;


}
