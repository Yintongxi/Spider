#include <spider_include.h>


int Spider_Analytical_URL(url_t * node)
{
	bzero(node->domain,sizeof(node->domain));
	bzero(node->path,sizeof(node->path));
	bzero(node->ip,sizeof(node->ip));
	bzero(node->file_name,sizeof(node->file_name));

	int start;
	int flag = 0;
	int i = 0;
	int filesize;
	//协议类型判断
	char * http_array[]={"http://","https://",NULL};
	if(strncmp(node->origin_url,http_array[0],strlen(http_array[0]))==0){
			node->http_type = 0;
			node->port = 80;
			start = strlen(http_array[0]);
	}else{
			node->http_type = 1;//http协议
			node->port = 443;
			start = strlen(http_array[1]);
	}

	//获取域名
	for(i=start;node->origin_url[i]!='/'&&node->origin_url[i]!='\0';i++)
	{
		node->domain[flag] = node->origin_url[i];
		flag++;
	}
	//文件名获取
	for(i=strlen(node->origin_url);node->origin_url[i]!='/';i--,filesize++);
	flag=0;
	for(i = strlen(node->origin_url) - filesize + 1;node->origin_url[i]!='\0';i++)
	{
		node->file_name[flag] = node->origin_url[i];
		flag++;
	}
	//获取路径
	flag = 0;
	for(i = start + strlen(node->domain);i<strlen(node->origin_url)-filesize+1;i++)
	{
		node->path[flag] = node->origin_url[i];
		flag++;
	}

	//需要网络，访问DNS域名解析服务器，获取web服务器公网IP
	struct hostent * ent = NULL;
	if((ent = gethostbyname(node->domain))!=NULL){
	
		inet_ntop(AF_INET,ent->h_addr_list[0],node->ip,16);
		printf("Spider Step[2] Analytical URL Success:\nORIGIN_URL%s\nHOST_DOMAIN%s\nHOST_IP=%s\nHOST_PATH=%s\nFILE_NAME=%s\nWEB_PORT=%d\nHTTP_TYPE=%d\n",node->origin_url,node->domain,node->ip,node->path,node->file_name,node->port,node->http_type);
		return 0;
	
	}else
		return -1;

}
