#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/mman.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <regex.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define _RESULT_MAX 10000

int result_fd;//存储抓取数据的文件描述符
int result_num;//抓取数量
int analytical_shutdown;//0关闭解析 1开启解析







typedef struct
{
	char origin_url[8192];
	char domain[1024];
	char path[1024];
	char file_name[1024];
	char ip[16];
	int http_type;
	int port;
}url_t;


typedef struct
{
	url_t * url_list;//容器队列
	int front;
	int rear;
	int cur;
	int max;
}container_t;


typedef struct
{
	SSL * ssl_socket;//安全套接字
	SSL_CTX * ssl_ctx;//认证上下文信息
}ssl_t;//https协议，安全认证


int Spider_Net_Init();//网络初始化
int Spider_Analytical_URL(url_t *);//url 解析
int Spider_Connect_Web(int ,url_t *);//tcp连接web服务器
int Spider_Create_RequestHead(url_t *,char *);//创建并请求头信息
int Spider_Download_HTML(int ,char * ,url_t ,ssl_t *);//发送请求，接受响应，完成https安全认证，完成下载流程
int Spider_Get_StatCode(const char *);//从响应头中获取响应码并返回
ssl_t * Spider_Openssl_Create(int sockfd);//完成openssl创建并初始化，并且进行SSL单向认证

container_t * Spider_Container_Create(int max);//创建容器
int Spider_Container_add(container_t *,url_t);//添加一个新资源
int Spider_Container_get(container_t *,url_t *);//获取一个资源
int Spider_Remove_Duplication(container_t *,container_t *,const char *utl);//去重校验，环形遍历比较
int Spider_Save_Result(const char *, const char * ,const char *);//持久化关键数据，以html格式存储
int Spider_Analytical_HTML(url_t,container_t *,container_t *);//解析更多url,提取关键数据
int Spider_Interactive_Process(url_t *);//整个下载交互封装
int Spider_StartUp(char * Alpha_url);//爬虫启动接口
