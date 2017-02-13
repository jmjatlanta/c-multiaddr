#ifndef MULTIADDR
#define MULTIADDR
#include <string.h>

#include "varhexutils.h"
#include "varint.h"
#include "protocols.h"
#include "protoutils.h"

struct MultiAddress
{
	char string[800];
	uint8_t bytes[400];
	int bsize[1];
};


int strpos(char *haystack, char *needle);

struct MultiAddress* new_maddr_fb(uint8_t * byteaddress,int size); //Construct new address from bytes

struct MultiAddress* new_maddr_fs(char * straddress); //Construct new address from string

void maddr_free(struct MultiAddress* in);

int m_encapsulate(struct MultiAddress * result, char * string);

int m_decapsulate(struct MultiAddress * result, char * srci);

#endif
