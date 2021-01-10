#include <string.h>
#include <stdio.h>
#include <openssl/evp.h> 
#include <openssl/aes.h> 
#include <openssl/err.h> 
#include <openssl/rand.h>

#include "common.h"

int main()
{
	char AesKey[AES_KEY_SIZE] = {0};
	char CryptData[DATA_MAX_SIZE] = {0};
	int CryptDataLen = DATA_MAX_SIZE;
	Str2Hex(CryptKey, AesKey);
	KeyPrint(AesKey, AES_KEY_SIZE);
	AesEncrypt(AES_MODE_CBC, AES_KEY_SIZE, AesKey, PlainText, strlen(PlainText), CryptData, &CryptDataLen);
	printf("cry data is %s\n", CryptData);
	return 0;
}

int AesEncrypt(int CryptMode, int KeySize, char* AesKey, char *PlainText, int *PlainTextlen, char* CryptData, int *CryptDataLen)
{
	EVP_CIPHER_CTX *Ctx;
	EVP_CIPHER *Cipher;
	char IvBuf[IV_MAX_SIZE];
	int IvLen;
	char *cipherData;
	char *cipherDataLen;
	
	Cipher = AesGetCipeher(CryptMode, KeySize);
	IvLen = EVP_CIPHER_iv_length(Cipher);
	RAND_bytes(IvBuf, IvLen);
	memcpy(CryptData, IvBuf, IvLen);
	cipherData = CryptData + IvLen;
	cipherDataLen = *CryptDataLen - IvLen;
	
	Ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(Ctx);
	EVP_CIPHER_CTX_set_padding(Ctx, 0);
	
	EVP_EncryptInit(Ctx, Cipher, AesKey, IvBuf);
	EVP_EncryptUpdate(Ctx, cipherData, cipherDataLen, PlainText, *PlainTextlen);

	
	
	
}
EVP_CIPHER* AesGetCipeher(int CryptMode, int KeySize)
{
	EVP_CIPHER * Cipher;
	switch(CryptMode)
	{
		case AES_MODE_CBC:
		{
			if(KeySize == 32)
				Cipher = EVP_aes_256_cbc();
			else
				Cipher = EVP_aes_128_cbc();
			break;
		}
		case AES_MODE_CFB:
		{
			if(KeySize == 32)
				Cipher = EVP_aes_256_cfb();
			else
				Cipher = EVP_aes_128_cfb();
			break;
		}
		case AES_MODE_OFB:
		{
			if(KeySize == 32)
				Cipher = EVP_aes_256_ofb();
			else
				Cipher = EVP_aes_128_ofb();
			break;
		}
		case AES_MODE_ECB:
		{
			if(KeySize == 32)
				Cipher = EVP_aes_256_ecb();
			else
				Cipher = EVP_aes_128_ecb();
			break;
		}
		default:
			printf("Mod Error\n");
		
	}
	return Cipher;
}