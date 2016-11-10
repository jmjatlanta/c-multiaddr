# c-multiaddr
multiaddr for IPFS in C.

### Multiaddr provides easy networking protocols nesting, easy encapsulation of extra protocols, easy tunneling, etc.
# Usage:
# All you need to include is multiaddr.h
## Maddr struct:
char string[]; // String that contains addresses such as /ip4/192.168.1.1/
uint8_t bytes; //String that contains the enecoded address
int bsize[]; //int[1] that contains the real bytes size (Use it whenever using the bytes so you don't input trash!)
## New Multi Address From String(new_maddr_fs)
  char addrstr[] = "/ip4/192.168.1.1/"
	struct maddr a;
	a=new_maddr_fs(addrstr);
## Obtaining the byte buffer(.bytes, .bsize[0]):
  printf("TEST BYTES: %s\n",Var_To_Hex(a.bsize[0], a.bytes));
  Var_To_Hex = Byte Buffer to Hex String
## Encapsulation & Decapsulation(m_encapsulate, m_decapsulate)
Remember, Decapsulation happens from right to left, never in reverse, if you have /ip4/udp/ipfs/ if you decapsulate "udp" you will also take out ipfs!
  Now the string is: /ip4/192.168.1.1/
  m_encapsulate(&a,"/udp/3333/"); //Adds udp/3333/ to char addrstr
  Now the string is: /ip4/192.168.1.1/udp/3333/
  m_decapsulate(&a,"udp"); //Removes udp protocol and its address
  Now the string is: /ip4/192.168.1.1/
	m_encapsulate(&a,"/tcp/8080");
	Now the string is: /ip4/192.168.1.1/tcp/8080/
# Constructing a multiaddress from bytes:
  struct maddr beta;
	beta=new_maddr_fb(a.bytes,a.bsize[0]); //This will already construct back to the string too!
	printf("B STRING: %s\n",beta.string);  //So after encapsulation and decapsulation atm this string would
  contain: /ip4/192.168.1.1/tcp/8080/
 
