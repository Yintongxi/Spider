#include <spider_include.h>



container_t * Spider_Container_Create(int tmax)
{
		container_t * ct = NULL;
		if((ct = (container_t *)malloc(sizeof(container_t)))==NULL){
				perror("Spider_Container_Create, Malloc Container Failed");
				exit(0);
		}
		if((ct->url_list = (url_t *)malloc(sizeof(url_t) * tmax))==NULL){
				perror("Spider_Container_Create, Malloc URL List Failed");
				exit(0);
		}
		ct->front = 0;
		ct->rear = 0;
		ct->max = tmax;
		ct->cur = 0;
		return ct;
}
