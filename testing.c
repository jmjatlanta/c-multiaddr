#include "multiaddr.h"
//ADD TO PROTOUTILS.H

int main()
{
	struct maddr a;
	a=new_maddr_fs("/ip4/192.168.1.1/");
	printf("s str:%s\n",a.string);
	//m_encapsulate("/tcp/8080");
	//m_decapsulate("tcp");
	//struct maddr b;
	//b=new_maddr_fb(a.bytes,sizeof(a.bytes));
	//printf("B STRING: %s\n",b.string);
}