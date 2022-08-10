#include <spider_include.h>


int Spider_Analytical_HTML(url_t node, container_t * E_ct, container_t * P_ct)
{
	int fd;
	int filesize;
	char * map_ptr = NULL;
	char * copy_mapptr = NULL;
	char h1[1024];
	char des[8192];
	char link[8192];
	regex_t hreg,dreg,lreg;
	regmatch_t hma[2];
	regmatch_t dma[2];
	regmatch_t lma[2];
	bzero(h1,sizeof(h1));
	bzero(des,sizeof(des));
	bzero(link,sizeof(link));
	url_t tmp;
	if((fd = open(node.file_name,O_RDONLY))==-1){
		perror("Analytcial HTML >> open HTML Failed");
		exit(0);
	}
	filesize = lseek(fd,0,SEEK_END);//获取文件大小

	if((map_ptr = mmap(NULL,filesize,PROT_READ,MAP_PRIVATE,fd,0))==MAP_FAILED){
		perror("Analytical HTML >> mmap Failed");
		exit(0);
	}
	copy_mapptr = map_ptr;//备份映射地址
	close(fd);

	//编写表达式，生成正则类型
	regcomp(&hreg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);
	regcomp(&dreg,"<meta name=\"description\" content=\"\\([^>]\\+\\?\\)\">",0);
	regcomp(&lreg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^>]\\+\\?</a>",0);

	//正则匹配
	if((regexec(&hreg,map_ptr,2,hma,0))==0)
	  snprintf(h1,hma[1].rm_eo - hma[1].rm_so + 1,"%s",map_ptr + hma[1].rm_so);
	if((regexec(&dreg,map_ptr,2,dma,0))==0)
	  snprintf(des,dma[1].rm_eo - dma[1].rm_so + 1,"%s",map_ptr + dma[1].rm_so);

	++result_num;
	Spider_Save_Result(h1,des,node.origin_url);//解析提取数据完毕，持久化操作

	printf("Analytcial HTML ,Result Title=[%s], Description=[%s]\n",h1,des);
	if(analytical_shutdown){
		while((regexec(&lreg,map_ptr,2,lma,0))==0){
			snprintf(link,lma[1].rm_eo - lma[1].rm_so + 24,"https://baike.baidu.com%s",map_ptr + lma[1].rm_so);
			if(Spider_Remove_Duplication(E_ct,P_ct,link)){
				strcpy(tmp.origin_url,link);
				Spider_Container_add(E_ct,tmp);//去重校验添加到处理队列
			}
			bzero(link,sizeof(link));
			map_ptr+=lma[0].rm_eo;
			if(E_ct->cur + 1 == E_ct->max){
				printf("E Container is Full, Break..\n");
				break;
			}
		}
	
	}
	unlink(node.file_name);//删除源码文件
	regfree(&hreg);
	regfree(&dreg);
	regfree(&lreg);
	munmap(copy_mapptr,filesize);
	return 0;


}
