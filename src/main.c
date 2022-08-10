#include <spider_include.h>

//OPENSSL//编译要加 -lssl -lcrypto
int main(){
	//种子
	//https://baike.baidu.com/item/%E5%8E%9F%E7%A5%9E/23583622?fr=aladdin
	char * tmp = "https://baike.baidu.com/item/%E5%8E%9F%E7%A5%9E/23583622?fr=aladdin";
	Spider_StartUp(tmp);
	return 0;
}
