#include <string.h>
#include <stdio.h>
#include <openssl/ec.h> 
#include <openssl/ecdsa.h> 
#include <openssl/objects.h> 
#include <openssl/err.h>

#define CurveId 10

int main()
{
	EC_KEY *key1,*key2; 

	EC_POINT *pubkey1,*pubkey2; 
	EC_GROUP *group1,*group2; 
	int ret,nid,size,i,sig_len;

	unsigned char *signature,digest[20]; 
	BIO *berr; 
	EC_builtin_curve *curves;
	int crv_len; 
	//char shareKey1[128*2],shareKey2[128*2];
	unsigned char shareKey1[256],shareKey2[256];
	int len1,len2;

	/* ���� EC_KEY ���ݽṹ */ 
	key1=EC_KEY_new(); 
	if(key1==NULL) {
		printf("EC_KEY_new err!\n");
		return -1; 
	}
	key2=EC_KEY_new(); 
	if(key2==NULL) {
		printf("EC_KEY_new err!\n");
		return -1;
       	}

	/* ��ȡʵ�ֵ���Բ���߸��� */
	crv_len = EC_get_builtin_curves(NULL, 0);
	curves = (EC_builtin_curve *)malloc(sizeof(EC_builtin_curve) * crv_len); 
	/* ��ȡ��Բ�����б� */
	EC_get_builtin_curves(curves, crv_len);
	/*
	nid=curves[0].nid;���д���ԭ������Կ̫��
	*/
	/* ѡȡһ����Բ���� */
	nid=curves[CurveId].nid;
	printf("Choose Cureve %s!\n", curves[CurveId].comment);
	//nid=curves[81].nid; // SM2
	/* ����ѡ�����Բ����������Կ���� group */ 
	group1=EC_GROUP_new_by_curve_name(nid);
	if(group1==NULL) {
		printf("EC_GROUP_new_by_curve_name err!\n");
		return -1; 
	}

	group2=EC_GROUP_new_by_curve_name(nid); 
	if(group1==NULL) {
		printf("EC_GROUP_new_by_curve_name err!\n");
		return -1; 
	}
	/* ������Կ���� */ 
	ret=EC_KEY_set_group(key1,group1); 
	if(ret!=1) {
		printf("EC_KEY_set_group err.\n");
		return -1; 
	}
	ret=EC_KEY_set_group(key2,group2); 
	if(ret!=1) {
		printf("EC_KEY_set_group err.\n");
		return -1; 
	}
	/* ������Կ */ 
	ret=EC_KEY_generate_key(key1); 
	if(ret!=1) {
		printf("EC_KEY_generate_key err.\n");
		return -1; 
	}
	ret=EC_KEY_generate_key(key2); 
	if(ret!=1) {
		printf("EC_KEY_generate_key err.\n");
		return -1;
       	}
	/* �����Կ */ 
	ret=EC_KEY_check_key(key1); 
	if(ret!=1) {
		printf("check key err.\n");
		return -1; 
	}
	/* ��ȡ��Կ��С */ 
	size=ECDSA_size(key1); 
	printf("size %d \n",size); 

	for(i=0;i<20;i++){
		memset(&digest[i],i+1,1);
	}

	signature=malloc(size);

	/*���ظ��Դ�����Ϣ*/
	ERR_load_crypto_strings();

	berr=BIO_new(BIO_s_file());
	BIO_set_fp(berr,stdout,BIO_NOCLOSE);

	/*ǩ�� ��ǩ*/
	/* ǩ�����ݣ�����δ��ժҪ���ɽ� digest �е����ݿ����� sha1 ժҪ��� */ 
	ret=ECDSA_sign(0,digest,20,signature,&sig_len,key1);
	if(ret!=1) {
		ERR_print_errors(berr); printf("sign err!\n"); return -1;
	}
	/* ��֤ǩ�� */ 
	ret=ECDSA_verify(0,digest,20,signature,sig_len,key1); 

	if(ret!=1) {
		ERR_print_errors(berr); printf("ECDSA_verify err!\n"); return -1;
	}

	/** DH �Ự��Կ**/
	/* ��ȡ�Է���Կ������ֱ������ */
	pubkey2 = EC_KEY_get0_public_key(key2);
	/* ����һ���Ĺ�����Կ */
	len1=ECDH_compute_key(shareKey1, 256, pubkey2, key1, NULL);
	
	/* printf */
	for ( i = 0; i<len1; i ++){
		printf("%02x:",shareKey1[i]);
	}
	printf("\n");
	

	pubkey1 = EC_KEY_get0_public_key(key1);
	/* ������һ��������Կ */
	len2=ECDH_compute_key(shareKey2, 256, pubkey1, key2, NULL); 
	if(len1!=len2) {
		printf("err\n"); 
	}
	else {
		ret=memcmp(shareKey1,shareKey2,len1); 
		if(ret==0)
			printf("ECDH_compute_key Success\n"); 
		else
			printf("ECDH_compute_key Fail\n");
	}


    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
 
    if (EC_POINT_get_affine_coordinates_GFp(group1, pubkey1, x, y, NULL)) {
        BN_print_fp(stdout, x);
        putc('\n', stdout);
        BN_print_fp(stdout, y);
        putc('\n', stdout);
    }	
	
	BIO *bp_public = NULL;
	BIO *bp_private = NULL;
	bp_public = BIO_new_file("public_ecc.pem", "w+");
	PEM_write_bio_EC_PUBKEY(bp_public, key1);
	bp_private = BIO_new_file("private_ecc.pem", "w+");
	PEM_write_bio_ECPrivateKey(bp_private, key1, NULL, NULL, 0, NULL, NULL);
	EC_KEY_print_fp(stdout, key1, 0);
	
	printf("test ok!\n"); 
	BIO_free(berr); 
	EC_KEY_free(key1); 
	EC_KEY_free(key2); 
	free(signature); 
	free(curves);
	return 0;
}