#include <string.h>
#include "multiaddr/varhexutils.h"
#include "multiaddr/varint.h"
#include "multiaddr/protocols.h"
#include "multiaddr/protoutils.h"
#include "multiaddr/multiaddr.h"

int strpos(char *haystack, char *needle)
{
	char *p = strstr(haystack, needle);
	if (p)
	{
		return p - haystack;
	}
	else
	{
		return -1;   // Not found = -1.
	}
}

struct MultiAddress* new_maddr_fb(uint8_t* byteaddress,int size)//Construct new address from bytes
{
	struct MultiAddress* anewaddr2 = (struct MultiAddress*)malloc(sizeof(struct MultiAddress));
	if (anewaddr2 != NULL) {
		if(byteaddress!=NULL)
		{
			memcpy(anewaddr2->bytes, byteaddress, size);
			if(bytes_to_string(anewaddr2->string,byteaddress,size)==1)
			{
				return anewaddr2;
			}
		}
	}
	return anewaddr2;
}
struct MultiAddress* new_maddr_fs(char * straddress)//Construct new address from string
{
	struct MultiAddress* anewaddr = (struct MultiAddress*)malloc(sizeof(struct MultiAddress));
	if (anewaddr != NULL) {
		bzero(anewaddr->string, 800);
		strcpy(anewaddr->string, straddress);
		anewaddr->bsize[0] = 0;
		if(string_to_bytes(anewaddr->bytes,anewaddr->bsize,anewaddr->string,sizeof(anewaddr->string))==1)
		{
			int betta;
			//printf("BSIZE: %u\n", anewaddr.bsize[0]);
			for(betta=anewaddr->bsize[0];betta<400;betta++)
			{
				anewaddr->bytes[betta] = '\0';
			}
			return anewaddr;
		}
	}
	return anewaddr;
}

void maddr_free(struct MultiAddress* in) {
	free(in);
}

int m_encapsulate(struct MultiAddress * result, char * string)
{
	if(result!=NULL&&string!=NULL)
	{
		int success = 0;
		char pstr[800];
		bzero(pstr,800);
		strcpy(pstr,result->string);
		strcat(pstr,string+1);
		if(string_to_bytes(result->bytes,result->bsize,pstr,sizeof(pstr)))
		{
			strcpy(result->string,pstr);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int m_decapsulate(struct MultiAddress * result, char * srci)
{
	if(result!=NULL && srci!=NULL)
	{
		char * procstr = NULL;
		procstr = result->string;
		int i=0;
		int sz=strlen(procstr);
		char * src = NULL;
		src=srci;
		for(i=0;i<sz;i++)
		{
			if(procstr[i] == '/')
			{
				procstr[i]=' ';
			}
		}
		int pos=-1;
		pos=strpos(procstr,src);
		if(pos!=-1)
		{
			for(i=pos;i<sz;i++)
			{
				procstr[i] = '\0';
			}
			for(i=0;i<sz;i++)
			{
				if(procstr[i] == ' ')
				{
					procstr[i] = '/';
				}
			}
			return 1;
		}
		else
		{
			return 0;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

