#include "multiaddr/multiaddr.h"
//ADD TO PROTOUTILS.H

int main()
{
	char addrstr[100];
	bzero(addrstr,100);
	strcat(addrstr,"/ip4/192.168.1.1/tcp/8080/");
	printf("INITIAL: %s\n",addrstr);
	struct MultiAddress* a;
	a=new_maddr_fs(addrstr);
	printf("TEST BYTES: %s\n",Var_To_Hex(a->bsize[0], a->bytes));
	
	//Remember, Decapsulation happens from right to left, never in reverse!
	
	printf("A STRING:%s\n",a->string);
	m_encapsulate(a,"/ip4/192.31.200.1/udp/3333/");
	printf("A STRING ENCAPSULATED:%s\n",a->string);
	
	m_decapsulate(a,"udp");
	printf("A STRING DECAPSULATED UDP:%s\n",a->string);
	
	m_encapsulate(a,"/tcp/8080");
	printf("A STRING ENCAPSULATED TCP:%s\n",a->string);

	struct MultiAddress* beta;
	beta=new_maddr_fb(a->bytes,a->bsize[0]);
	printf("B STRING: %s\n",beta->string);

	maddr_free(a);
	maddr_free(beta);
}
