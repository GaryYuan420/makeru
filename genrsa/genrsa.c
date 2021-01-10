#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<openssl/err.h>
#include<openssl/bn.h>
#include<openssl/bio.h>
#include<openssl/ec.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>

#define BN_GENCB_get_arg(cb) ((void*)(cb)->arg)

int genRsaCb(int iP, int iN, BN_GENCB *pstCb)
{
	char cData = '*';
	(void)iN;
	
	if(iP == 0)
	{
		cData = '.';
	}
	if(iP == 1)
	{
		cData = '+';
	}
	if(iP == 2)
	{
		cData = '*';
	}
	if(iP == 3)
	{
		cData = '\n';
	}
	(void)BIO_write(BN_GENCB_get_arg(pstCb), &cData, 1);
	(void)BIO_flush(BN_GENCB_get_arg(pstCb));
	
	return 1;
}

int main()
{
	BIGNUM *pstExp = NULL;
	BN_GENCB *pstCb = OPENSSL_malloc(sizeof(BN_GENCB));
	BIGNUM *pstBn;
	RSA *pstRsa = NULL;
	char *pcHexe = NULL;
	char *pcDexe = NULL;
	int iRet = 1;
	int bits = 1024;
	//int defprimes = 2;
	BIO *bp_public = NULL;
	BIO *bp_private = NULL;
	pstBn = BN_new();
	
	BN_GENCB_set(pstCb, genRsaCb, NULL);
	pstRsa=RSA_new();
	iRet = BN_set_word(pstBn, RSA_F4);
	RSA_generate_key_ex(pstRsa, bits, pstBn, pstCb);
	pstExp = pstRsa->e;
	pcHexe = BN_bn2hex(pstExp);
	pcDexe = BN_bn2dec(pstExp);
	printf("e is %s(0x%s)\n", pcDexe, pcHexe);
	
	bp_public = BIO_new_file("public.pem", "w+");
	PEM_write_bio_RSAPublicKey(bp_public, pstRsa);
	bp_private = BIO_new_file("private.pem", "w+");
	PEM_write_bio_RSAPrivateKey(bp_private, pstRsa, NULL, NULL, 0, NULL, NULL);
	RSA_print_fp(stdout, pstRsa, 0);
	
	return iRet;
}


