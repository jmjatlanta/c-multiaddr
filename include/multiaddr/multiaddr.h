#ifndef MULTIADDR
#define MULTIADDR
#include <string.h>

#include "varhexutils.h"
#include "varint.h"
#include "protocols.h"
#include "protoutils.h"

/**
 * Normally, addresses have been represented using string addresses, like:

	tcp4://127.0.0.1:1234
	udp4://10.20.30.40:5060
	ws://1.2.3.4:5678
	tcp6://[1fff:0:a88:85a3::ac1f]:8001
	This isn't optimal. Instead, addresses should be formatted so:

	Binary format:

	(varint proto><n byte addr>)+
	<1 byte ipv4 code><4 byte ipv4 addr><1 byte udp code><2 byte udp port>
	<1 byte ipv6 code><16 byte ipv6 addr><1 byte tcp code><2 byte tcp port>

	String format:

	(/<addr str code>/<addr str rep>)+
	/ip4/<ipv4 str addr>/udp/<udp int port>
	/ip6/<ipv6 str addr>/tcp/<tcp int port>
 */

struct MultiAddress
{
	// A MultiAddress represented as a string
	char* string;
	// A MultiAddress represented as an array of bytes
	uint8_t* bytes;
	size_t bsize;
};


int strpos(char *haystack, char *needle);

struct MultiAddress* multiaddress_new_from_bytes(const uint8_t* byteaddress, int size); //Construct new address from bytes

struct MultiAddress* multiaddress_new_from_string(const char* straddress); //Construct new address from string

void multiaddress_free(struct MultiAddress* in);

int multiaddress_copy(const struct MultiAddress* source, struct MultiAddress* destination);

int multiaddress_encapsulate(struct MultiAddress * result, char * string);

int multiaddress_decapsulate(struct MultiAddress * result, char * srci);

#endif
