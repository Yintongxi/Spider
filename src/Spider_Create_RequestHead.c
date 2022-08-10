#include <spider_include.h>


int Spider_Create_RequestHead(url_t * node,char * Request)
{
		bzero(Request,4096);
		sprintf(Request,"GET %s HTTP/1.1\r\n"\
					"Accept:text/html,application/xhtml+xml;q=0.9,image/webp;q=0.8\r\n"\
					"User-Agent:Mozilla/5.0 (X11; Linux x86_64)\r\n"\
					"Host:%s\r\n"\
					"Connection:close\r\n\r\n",node->origin_url,node->domain);
		printf("Spider Step [4] Create RequestHand Success:%s\n",Request);
		return 0;
}
