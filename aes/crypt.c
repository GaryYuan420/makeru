#include <string.h>
#include <stdio.h>
#include <openssl/evp.h> 
#include <openssl/aes.h> 
#include <openssl/err.h> 
#include <openssl/rand.h>

#include "common.h"


static const EVP_CIPHER* AesGetCipeher(int CryptMode, int KeySize)
{
	const EVP_CIPHER * Cipher;
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

int AesEncrypt(int CryptMode, int KeySize, unsigned char* AesKey, const unsigned char *PlainText,
				int PlainTextlen, unsigned char* CryptData, int *CryptDataLen)
{
	EVP_CIPHER_CTX *Ctx;
	const EVP_CIPHER *Cipher;
	unsigned char IvBuf[IV_MAX_SIZE];
	int IvLen;
	unsigned char *cipherData;
	int cipherDataLen;
	int cipherEndLen;
	Cipher = AesGetCipeher(CryptMode, KeySize);

	IvLen = EVP_CIPHER_iv_length(Cipher);
	RAND_bytes(IvBuf, IvLen);
	memcpy(CryptData, IvBuf, IvLen);

	cipherData = CryptData + IvLen;
	cipherDataLen = *CryptDataLen - IvLen;
	
	Ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(Ctx);
	//EVP_CIPHER_CTX_set_padding(Ctx, 0);
	
	EVP_EncryptInit(Ctx, Cipher, AesKey, IvBuf);
	EVP_EncryptUpdate(Ctx, cipherData, &cipherDataLen, PlainText, PlainTextlen);
	EVP_EncryptFinal(Ctx, cipherData + cipherDataLen, &cipherEndLen);
	*CryptDataLen = cipherDataLen + cipherEndLen + IvLen;
	EVP_CIPHER_CTX_cleanup(Ctx);
	HexPrint("IV", IvBuf, IvLen);
	return 0;
}


int AesDecrypt(int CryptMode, int KeySize, unsigned char* AesKey, unsigned char* CryptData, int CryptDataLen, const unsigned char *PlainText,
				int *PlainTextlen)
{
	EVP_CIPHER_CTX *Ctx;
	const EVP_CIPHER *Cipher;
	unsigned char IvBuf[IV_MAX_SIZE];
	int IvLen;
	unsigned char *cipherData;
	int cipherDataLen;
	int PlainDatalen;
	int PlainDataEndlen;
	Cipher = AesGetCipeher(CryptMode, KeySize);

	IvLen = EVP_CIPHER_iv_length(Cipher);
	memcpy(IvBuf, CryptData, IvLen);
	cipherData = CryptData + IvLen;
	cipherDataLen = CryptDataLen - IvLen;
	
	Ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(Ctx);
	//EVP_CIPHER_CTX_set_padding(Ctx, 0);
	
	EVP_DecryptInit(Ctx, Cipher, AesKey, IvBuf);
	EVP_DecryptUpdate(Ctx, PlainText, &PlainDatalen, cipherData, cipherDataLen);
	EVP_DecryptFinal(Ctx, PlainText + PlainDatalen, &PlainDataEndlen);
	*PlainTextlen = PlainDatalen + PlainDataEndlen;
	EVP_CIPHER_CTX_cleanup(Ctx);
	HexPrint("IV", IvBuf, IvLen);
	return 0;
}


int main()
{
	unsigned char AesKey[AES_KEY_SIZE] = {0};
	unsigned char CryptData[DATA_MAX_SIZE] = {0};
	unsigned char PlainData[DATA_MAX_SIZE] = {0};
	int CryptDataLen = DATA_MAX_SIZE;
	int PlainDataLen = 0;
	Str2Hex(CryptKey, AesKey);
	HexPrint("Key", AesKey, AES_KEY_SIZE);
	AesEncrypt(AES_MODE_CBC, AES_KEY_SIZE, AesKey, PlainText, strlen((char*)PlainText), CryptData, &CryptDataLen);
	HexPrint("Crypt Data:", CryptData, CryptDataLen);
	AesDecrypt(AES_MODE_CBC, AES_KEY_SIZE, AesKey, CryptData, CryptDataLen, PlainData, &PlainDataLen);
	HexPrint("plain Data:", PlainData, PlainDataLen);
	PlainData[PlainDataLen] = '\0';
	printf("plain Data String: \n%s\n", PlainData);
	return 0;
}

