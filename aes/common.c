#include <string.h>
#include <stdio.h>
#include <openssl/ec.h> 
#include <openssl/ecdsa.h> 
#include <openssl/objects.h> 
#include <openssl/err.h>

void HexPrint(char* claim, unsigned char *AesKey, int len)
{
	int i;
	printf("%s(lenth is %d)\n", claim, len);
	for(i = 0; i < len; i++)
	{
		printf("%02x ", AesKey[i]&0xff);
		if((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
	return ;
}

static char char2Hex(char cha)
{
	if(cha >= '0' && cha <= '9')
	{
		cha = cha - '0';
	}
	else if(cha >= 'a' && cha <= 'f')
	{
		cha = cha - 'a' + 10;
	}
	else if(cha >= 'A' && cha <= 'F')
	{
		cha = cha - 'A' + 10;
	}
	return cha;
}

int Str2Hex(unsigned char *Str, unsigned char *Hex)
{
	unsigned char tmp1, tmp2;
	while(*Str != '\0')
	{
		tmp1 = char2Hex(*Str++);
		tmp2 = char2Hex(*Str++);
		*Hex++ = (tmp1 << 4) | tmp2;
	}
	return 0;
}
