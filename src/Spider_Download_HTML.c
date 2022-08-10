#include <spider_include.h>



int Spider_Download_HTML(int webfd , char * Request, url_t node, ssl_t * ssl)
{
	char buffer[8192];
	char Response[4096];
	char * pos = NULL;
	int recvlen;
	int fd;
	int statcode;
	bzero(buffer,sizeof(buffer));
	bzero(Response,sizeof(Response));
	SSL_write(ssl->ssl_socket,Request,strlen(Request));//发送请求
	printf("Spider Step [5] Send Request Success...\n");
	recvlen = SSL_read(ssl->ssl_socket,buffer,sizeof(buffer));//第一次读取响应

	if((pos = strstr(buffer,"\r\n\r\n"))==NULL){
		printf("strstr Call Failed,not Find Response Head!\n");
		exit(0);
	}

	snprintf(Response,pos - buffer + 4,"%s",buffer);//将响应头写入到Response
	printf("Spider Step [6] Response Head:\n%s",Response);

	//创建文件保存网页源码
	if((fd = open(node.file_name,O_RDWR|O_CREAT,0664))==-1){
		perror("Spider_Download_HTML ,Create HTML Call Failed\n");
		exit(0);
	}
	if((statcode = Spider_Get_StatCode(Response))==200){
		printf("Spider Step [*] Response Code %d\n",statcode);
		//将第一次读取的部分响应体，写入到文件
		write(fd,pos+4,recvlen - (pos - buffer +4));
		//循环读写剩余内容
		while((recvlen = SSL_read(ssl->ssl_socket,buffer,sizeof(buffer)))>0){
			write(fd,buffer,recvlen);
			bzero(buffer,sizeof(buffer));
		}
		close(webfd);
		close(fd);
		printf("Spider Step [7] Download HTML Successly...\n");
		free(ssl);
		ssl = NULL;
		return 0;
	}else{
		printf("Spider Step [*] Download Failed Statcode %d\n",statcode);
		close(webfd);
		free(ssl);
		ssl = NULL;
		return -1;
	}



}
