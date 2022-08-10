#include <spider_include.h>



int Spider_Get_StatCode(const char * Response)
{
	int statcode = -1;
	char Strcode[128];
	bzero(Strcode,128);
	regex_t reg;
	regmatch_t match[2];
	regcomp(&reg,"HTTP/1.1 \\([^\r\n]\\+\\?\\)\r\n",0);
	if((regexec(&reg,Response,2,match,0))==0){
		snprintf(Strcode,match[1].rm_eo - match[1].rm_so + 1,"%s",Response + match[1].rm_so);
		sscanf(Strcode,"%d ",&statcode);//格式转变
		regfree(&reg);
		return statcode;
	}
	regfree(&reg);
	return statcode;
}
