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



int main()
{
	EVP_PKEY *pkey;
	pkey = EVP_PKEY_new();
	BIGNUM *bn;
	bn = BN_new();
	BN_set_word(bn, RSA_F4);
	RSA *rsa;
	rsa = RSA_new();
	RSA_generate_key_ex(
		rsa,  /* pointer to the RSA structure */
		2048, /* number of bits for the key - 2048 is a good value */
		bn,   /* exponent allocated earlier */
		NULL /* callback - can be NULL if progress isn't needed */
	);
	EVP_PKEY_assign_RSA(pkey, rsa);
	
	/*Refer to own code*/
	BIO *bp_public = NULL;
	BIO *bp_private = NULL;
	BIGNUM *pstExp = NULL;
	char *pcHexe = NULL;
	char *pcDexe = NULL;
		
	pstExp = rsa->e;
	pcHexe = BN_bn2hex(pstExp);
	pcDexe = BN_bn2dec(pstExp);
	printf("e is %s(0x%s)\n", pcDexe, pcHexe);
	
	bp_public = BIO_new_file("public.pem", "w+");
	PEM_write_bio_RSAPublicKey(bp_public, rsa);
	bp_private = BIO_new_file("private.pem", "w+");
	PEM_write_bio_RSAPrivateKey(bp_private, rsa, NULL, NULL, 0, NULL, NULL);
	RSA_print_fp(stdout, rsa, 0);
	/*Refer to own code*/
		
	EVP_PKEY_free(pkey);

	return 0;
}


