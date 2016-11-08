#include "protocols.h"
#include "codecs.h"
int main() //This won't exist, it's here for my own testing purposes.
{
	load_protocols();
	pp();
	printf("The returned protocol is: %s\nSIZE: %d\n", proto_with_name("onion")->name, proto_with_name("onion")->size);
	printf("The returned protocol is: %s\nSIZE: %d\n", proto_with_deccode(444)->name, proto_with_deccode(444)->size);
	for(int i=0; i<14; i++)
	{
		uint64_t extract =  (protocol_P+i)->deccode;
		char exhexco[20] = "\0"; 
		strcpy(exhexco, Num_To_HexVar_64(extract));
		uint64_t decimalval = HexVar_To_Num_64(exhexco);
		if(i<9){printf("PROTOCOL 0%d HAS HEXCODE: %s DECIMAL: %"PRIu64" \n", i+1, exhexco, decimalval);}
		else{printf("PROTOCOL %d HAS HEXCODE: %s DECIMAL: %"PRIu64" \n", i+1, exhexco, decimalval);};
	}
	free(protocol_P);
	printf("1337 in Hexvar_64: %s\n", Num_To_HexVar_64(1337));
	char HEXSTR[20] = "B90A0000000000000000"; //\0 since it's not defined in a source string
	uint64_t result = HexVar_To_Num_64(HEXSTR);
	result = HexVar_To_Num_64(HEXSTR);
	printf("Hexvar_To_Num_64: %"PRIu64"\n", result);
	uint8_t Numinvar[10] = {0};
	memcpy(Numinvar, Num_To_Varint_64(1337), 10);
	printf("Binary form unreadable obviously : %s\n", Numinvar);
	uint64_t Varinnum = 0;
	memcpy(&Varinnum, Varint_To_Num_64(Numinvar), sizeof(Varint_To_Num_64(Numinvar)));
	printf("Number form now readable again:%"PRIu64"\n", Varinnum);
	char converted2hex[20] = "\0";
	strcpy(converted2hex, Var_To_Hex(Numinvar));
	uint8_t converted2bin[10] = {0};
	memcpy(converted2bin, Hex_To_Var(converted2hex), 10);
	printf("Encoding previous binary to hex now: %s\n", converted2hex); 
	printf("Encoding previous hex to binary now: %s\n", converted2bin);
	//Series of bytes test
	int8_t bcounter = 0;
	bcounter = Var_Bytes_Count(Numinvar);
	printf("Bytes_Count of Numinvar(1337): %d\n", bcounter);
	char int2hex[20] = "\0";
	strcat(int2hex, Int_To_Hex(1337));
	printf("INT2HEX: %s\n", int2hex);
	/*TESTING ENDIAN // Aparently won't be needed.
	printf("Testing Endian:\n");
	uint32_t val32 = 1337;
	printf("val32 = %d           swapped val32 = %d\n",val32, htole32(val32));
	printf("val32 = 0x%08x  swapped val32 = 0x%08x\n\n",val32, htole32(val32));
	*/
	return 0;
}