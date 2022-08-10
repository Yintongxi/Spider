#include <spider_include.h>


int Spider_Container_add(container_t * ct ,url_t node)
{
		if(ct->cur == ct->max)
		  return -1;

		ct->url_list[ct->front] = node;
		ct->front = (ct->front + 1) % ct->max;
		++ct->cur;
		return 0;
}
