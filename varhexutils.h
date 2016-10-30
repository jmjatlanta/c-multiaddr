#ifndef VARHEXUTILS
#define VARHEXUTILS
#include <stdio.h>
#include <inttypes.h>
#include "varint.h"
#include <stdlib.h>
#include <string.h>
int8_t Var_Bytes_Count(uint8_t countbytesofthis[10])
{
	static int8_t xrzk_bytescnt = 0;
	for(int8_t i=0; i<10; i++)
	{
		if(countbytesofthis[i] != 0)
		{
			xrzk_bytescnt++;
		}
	}
	return xrzk_bytescnt;
}
uint8_t * Num_To_Varint_64(uint64_t TOV64INPUT) //UINT64_T TO VARINT
{
	static uint8_t buffy_001[10] = {0};
	uvarint_encode64(TOV64INPUT, buffy_001, 10);
	return buffy_001;
}
uint8_t * Num_To_Varint_32(uint32_t TOV32INPUT) // UINT32_T TO VARINT
{
	static uint8_t buffy_032[10] = {0};
	uvarint_encode32(TOV32INPUT, buffy_032, 10);
	return buffy_032;
}
uint64_t * Varint_To_Num_64(uint8_t TON64INPUT[10]) //VARINT TO UINT64_t
{
	static uint64_t varintdecode_001 = 0;
	uvarint_decode64(TON64INPUT, 10, &varintdecode_001);
	return &varintdecode_001;
}
uint32_t * Varint_To_Num_32(uint8_t TON32INPUT[10]) //VARINT TO UINT32_t
{
	static uint32_t varintdecode_032 = 0;
	uvarint_decode32(TON32INPUT, 10, &varintdecode_032);
	return &varintdecode_032;
}
//
char * Var_To_Hex(uint8_t TOHEXINPUT[10]) //VAR[binformat] TO HEX
{
	static char convert_resultz1[10]="\0";
	memset(convert_resultz1,0,sizeof(convert_resultz1));
	void convert(uint8_t buf[10])
	{
		char conv_proc[10]="\0";
		for(int i=0; i < 10; i++)
		{
			sprintf (conv_proc, "%02X", buf[i]);
			//printf("%d:%d\n",i, buf[i]);
			strcat(convert_resultz1, conv_proc);
		}
	}
	convert(TOHEXINPUT);
	return convert_resultz1;
}
uint8_t * Hex_To_Var(char * Hexstr) //HEX TO VAR[BINFORMAT]
{
	static uint8_t buffy_HEX[10] = {0};
	char codo[20] = "\0";
	strcpy(codo, Hexstr);
	char code[3] = "\0";
	int x = 0;
	for(int i= 0;i<20;i++)
	{
		strncpy(&code[0],&codo[i],1);
		strncpy(&code[1],&codo[i+1],1);
    	char *ck = NULL;
    	uint64_t lu = 0;
    	lu=strtoul(code, &ck, 16);
		buffy_HEX[x] = lu;
		i++;
		x++;
	}
	return buffy_HEX;
}
//
char * Num_To_HexVar_64(uint64_t TOHVINPUT) //UINT64 TO HEXIFIED VAR 
{											//Code to varint - py
	static char convert_result[10]="\0";//Note that the hex resulted from this will differ from py
	memset(convert_result,0,sizeof(convert_result));//But if you make sure the string is always 20 chars in size
	void convert(uint8_t buf[10])					//Both of them read them properly.
	{
		char conv_proc[10]="\0";
		int i=0;
		for(; i < 10; i++)
		{
			sprintf (conv_proc, "%02X", buf[i]);
			//printf("%d:%d\n",i, buf[i]);
			strcat(convert_result, conv_proc);
		}
	}
	uint8_t buf[10] = {0};
	uvarint_encode64(TOHVINPUT, buf, 10);
	convert(buf);

	return convert_result;
}
char * Num_To_HexVar_32(uint32_t TOHVINPUT) //UINT32 TO HEXIFIED VAR
{											//Code to varint - py
	static char convert_result2[10]="\0";
	memset(convert_result2,0,sizeof(convert_result2));
	void convert(uint8_t buf[10])
	{
		char conv_proc[10]="\0";
		int i=0;
		for(; i < 10; i++)
		{
			sprintf (conv_proc, "%02X", buf[i]);
			printf("%d:%d\n",i, buf[i]);
			strcat(convert_result2, conv_proc);
		}
	}
	uint8_t buf[10] = {0};
	uvarint_encode32(TOHVINPUT, buf, 10);
	convert(buf);

	return convert_result2;
}

uint64_t HexVar_To_Num_64(char * theHEXstring) //HEXIFIED VAR TO UINT64_T
{											   //Varint to code - py
	uint8_t buffy[10] = {0};
	char codo[20] = "\0";
	strcpy(codo, theHEXstring);
	char code[3] = "\0";
	int x = 0;
	for(int i= 0;i<20;i++)
	{
		strncpy(&code[0],&codo[i],1);
		strncpy(&code[1],&codo[i+1],1);
    	char *ck = NULL;
    	uint64_t lu = 0;
    	lu=strtoul(code, &ck, 16);
		buffy[x] = lu;
		i++;
		x++;
	}
	static uint64_t decoded;
	uvarint_decode64 (buffy, 10, &decoded);
	return decoded;
}
uint32_t HexVar_To_Num_32(char theHEXstring[]) //HEXIFIED VAR TO UINT32_T
{												//Varint to code py
	uint8_t buffy[10] = {0};
	char codo[20] = "\0";
	strcpy(codo, theHEXstring);
	char code[2] = "\0";
	int x = 0;
	for(int i= 0;i<20;i++)
	{
		strncpy(&code[0],&codo[i],1);
		strncpy(&code[1],&codo[i+1],1);
    	char *ck = NULL;
    	uint32_t lu = {0};
    	lu=strtoul(code, &ck, 16);
		buffy[x] = lu;
		i++;
		x++;
	}
	static uint32_t decoded;
	uvarint_decode32 (buffy, 10, &decoded);
	return decoded;
}
#endif