#ifndef PROTOUTILS
#define PROTOUTILS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//IP2INT

//IPv4 VALIDATOR
#define DELIM "."
 
/* return 1 if string contain only digits, else return 0 */
int valid_digit(char *ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return 0;
    }
    return 1;
}
 
/* return 1 if IP string is valid, else return 0 */
int is_valid_ipv4(char *ip_str)
{
    int i, num, dots = 0;
    char *ptr;
 
    if (ip_str == NULL)
        return 0;
 
    // See following link for strtok()
    // http://pubs.opengroup.org/onlinepubs/009695399/functions/strtok_r.html
    ptr = strtok(ip_str, DELIM);
 
    if (ptr == NULL)
        return 0;
 
    while (ptr) {
 
        /* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return 0;
 
        num = atoi(ptr);
 
        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        } else
            return 0;
    }
 
    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return 0;
    return 1;
}


//////////////IPv6 Validator
#define MAX_HEX_NUMBER_COUNT 8 

int ishexdigit(char ch) 
{
   if((ch>='0'&&ch<='9')||(ch>='a'&&ch<='f')||(ch>='A'&&ch<='F'))
      return(1);
   return(0);
}

int is_valid_ipv6(char *str)
{ 
   int hdcount=0;
   int hncount=0;
   int err=0;
   int packed=0;

   if(*str==':')
   {
      str++;    
      if(*str!=':')
         return(0);
      else
      {
         packed=1;
         hncount=1;
         str++;

         if(*str==0)
            return(1);
      }
   }

   if(ishexdigit(*str)==0)
   {
      return(0);        
   }

   hdcount=1;
   hncount=1;
   str++;

   while(err==0&&*str!=0)   
   {                      
      if(*str==':')
      {
         str++;
         if(*str==':')
         {
           if(packed==1)
              err=1;
           else
           {
              str++;

          if(ishexdigit(*str)||*str==0&&hncount<MAX_HEX_NUMBER_COUNT)
          {
             packed=1;
             hncount++;

             if(ishexdigit(*str))
             {
                if(hncount==MAX_HEX_NUMBER_COUNT)
                {
                   err=1;
                } else
                {
                   hdcount=1;
                   hncount++;
                   str++;   
                }
             }
          } else
          {
             err=1;
          }
       }
    }
	else
    {
           if(!ishexdigit(*str))
           {
              err=1;
           } else
           {
              if(hncount==MAX_HEX_NUMBER_COUNT)
              {
                 err=1;
              } else
              {
                  hdcount=1;
                  hncount++;
                  str++;   
              }
           }
        }
     } 
	 else
     {  
        if(ishexdigit(*str))
        {
           if(hdcount==4)
              err=1;
           else
           {
              hdcount++;          
              str++;
           }
         } else
            err=1;
     } 
   }

   if(hncount<MAX_HEX_NUMBER_COUNT&&packed==0)
      err=1;

    return(err==0);
}
///Still in work
uint64_t ip2int(char * ipconvertint)
{
	uint64_t final_result =0;
	char * iproc;
	int ipat1=0;
	int ipat2=0;
	int ipat3=0;
	int ipat4=0;
	char ip[16];
	strcpy(ip, ipconvertint);
	printf("ip: %s\n", ip);
	iproc = strtok (ip,".");
	for(int i=0; i<4;i++)
	{
		switch(i)
		{
			case 0:
			{
				ipat1 = atoi(iproc);
				break;
			}
			case 1:
			{
				ipat2 = atoi(iproc);
				break;
			}
			case 2:
			{
				ipat3 = atoi(iproc);
				break;
			}
			case 3:
			{
				ipat4 = atoi(iproc);
				break;
			}
			default:
			{
				printf("Somebody misplaced an int\n");
				break;
			}
		}
		iproc = strtok (NULL,".");
	}
	final_result =  ((ipat1*pow(2,24))+(ipat2*pow(2,16))+(ipat3*pow(2,8))+1);
	return final_result;
}
char * address_string_to_bytes(struct protocol * xx, char * abc)
{
	static char astb__stringy[10] = "\0";
	int code = 0;
	code = xx->deccode;
	switch(code)
	{
		case 4://IPv4
		{
			if(is_valid_ipv4(abc))
			{
				uint64_t iip = ip2int(abc);
				strcpy(astb__stringy,Int_To_Hex(iip));
				return astb__stringy;
			}
			else
			{
				return "ERR";
			}
			break;
		}
		case 41://IPv6
		{
			printf("IP6\n");
			break;
		}
		case 6: //Tcp
		{
			printf("TCP!\n");
			break;
		}
		case 17: //Udp
		{
			break;
		}
		case 33://dccp
		{
			break;
		}
		case 132://sctp
		{
			break;
		}
		case 301://udt
		{
			break;
		}
		case 302://utp
		{
			break;
		}
		case 42://IPFS - !!!
		{
			break;
		}
		case 480://http
		{
			break;
		}
		case 443://https
		{
			break;
		}
		case 477://ws
		{
			break;
		}
		case 444://onion
		{
			break;
		}
		case 275://libp2p-webrtc-star
		{
			break;
		}
		default:
		{
			printf("NO SUCH PROTOCOL!\n");
			break;
		}
	}
}
uint8_t * string_to_bytes(char * strx, size_t strsize)
{
	char str[strsize]; //This string will be bad later.
	strcpy(str,strx);
	if(str[0] == '/')
	{
		char * pch;
		static char xxx[40] = "\0";
		printf ("Splitting string \"%s\" into tokens:\n",str);
		pch = strtok (str,"/");
		load_protocols();
		while (pch != NULL)
		{
			if(proto_with_name(pch))
			{
				struct protocol * protx;
				protx = proto_with_name(pch);
				char cut[20]="\0";
				strcat(cut,Int_To_Hex(protx->deccode));
				cut[2] = '\0';
				strcat(xxx,cut);
				pch = strtok (NULL, "/");
				printf("ADDRESS: %s\n", pch);
				if(address_string_to_bytes(protx, pch) != "ERR")
				{
				}
				else
				{
					return 0;
				}
			}
			else
			{
				pch = strtok (NULL, "/");
			}
		}
		unload_protocols();
		printf("S2B_RESULT: %s\n", xxx);
	}
	else
	{
		printf("ERROR, Multiaddr needs to start with '/'\n");
	}
}
#endif