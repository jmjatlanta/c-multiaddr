#ifndef MULTIADDR
#define MULTIADDR
#include "varhexutils.h"
//#include "codecs.h"
#include "varint.h"
#include "protocols.h"
#include "protoutils.h"
#include <string.h>
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
struct maddr
{
	char string[800];
	uint8_t bytes[400];
	int bsize[1];
};
struct maddr new_maddr_fb(uint8_t * byteaddress,int size)//Construct new address from bytes
{
	struct maddr anewaddr2;
	if(byteaddress!=NULL)
	{
		memcpy(anewaddr2.bytes, byteaddress,size);
		if(bytes_to_string(anewaddr2.string,byteaddress,size)==1)
		{
			return anewaddr2;
		}
	}
	return anewaddr2;
}
struct maddr new_maddr_fs(char * straddress)//Construct new address from string
{
	struct maddr anewaddr;
	bzero(anewaddr.string, 800);
	strcpy(anewaddr.string, straddress);
	anewaddr.bsize[0] = 0;
	if(string_to_bytes(anewaddr.bytes,anewaddr.bsize,anewaddr.string,sizeof(anewaddr.string))==1)
	{
		int betta;
		//printf("BSIZE: %u\n", anewaddr.bsize[0]);
		for(betta=anewaddr.bsize[0];betta<400;betta++)
		{
			anewaddr.bytes[betta] = '\0';
		}
		return anewaddr;
	}
	return anewaddr;
}
int m_encapsulate(struct maddr * result, char * string)
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
int m_decapsulate(struct maddr * result, char * srci)
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

#endif
