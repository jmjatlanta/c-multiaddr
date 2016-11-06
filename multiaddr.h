#ifndef MULTIADDR
#define MULTIADDR
#include "varhexutils.h"
#include "codecs.h"
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
	char string[100];
	uint8_t bytes[100];
};
struct maddr new_maddr_fb(uint8_t * byteaddress,int size)//Construct new address from bytes
{
	struct maddr anewaddr;
	if(byteaddress!=NULL)
	{
		memcpy(anewaddr.bytes, byteaddress,size);
		if(bytes_to_string(anewaddr.string,byteaddress,size)==1)
		{
			return anewaddr;
		}
	}
}
struct maddr new_maddr_fs(char * straddress)//Construct new address from string
{
	struct maddr anewaddr;
	strcpy(anewaddr.string, straddress);
	if(string_to_bytes(anewaddr.bytes,anewaddr.string,sizeof(anewaddr.string))==1)
	{
		return anewaddr;
	}
}
int m_encapsulate(struct maddr * result, char * string)
{
	if(result!=NULL&&string!=NULL)
	{
		int success = 0;
		char pstr[50];
		bzero(pstr,50);
		strcpy(pstr,result->string);
		strcat(pstr,string+1);
		if(string_to_bytes(result->bytes,pstr,sizeof(pstr)))
		{
			printf("RESULT WOULD BE: %s\n", pstr);
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
			strcpy(result->string,procstr);
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