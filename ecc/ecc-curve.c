#include <openssl/ec.h> 
#include <openssl/evp.h>  //include NID_sm2 

/*
  https://www.openssl.org/docs/man1.1.0/crypto/EC_GROUP_new.html
  typedef struct {
          int nid;
          const char *comment;
          } EC_builtin_curve
*/

#define CheckCurve NID_secp256k1

int main() 
{
	EC_builtin_curve *curves = NULL; 
	size_t crv_len = 0, n = 0;
	int nid,ret;
	EC_GROUP *group = NULL;

	/*
	size_t EC_get_builtin_curves(EC_builtin_curve *r, size_t nitems)
	˵��: ��ȡ���õ���Բ���ߡ�
	      ��������� r Ϊ NULL ���� nitems Ϊ 0 ʱ������������Բ���ߵĸ�����
	      ���򽫸�����Բ������Ϣ����� r �С�
	*/
	crv_len = EC_get_builtin_curves(NULL, 0);
	curves = OPENSSL_malloc(sizeof(EC_builtin_curve) * crv_len); 

	/* ��ȡ��Բ�����б� */
	EC_get_builtin_curves(curves, crv_len);
	for (n=0;n<crv_len;n++) {
		nid = curves[n].nid; 
		group=NULL;
		printf("[%zd] nid = %d comment=%s \n", 
				n , curves[n].nid,curves[n].comment);
		group = EC_GROUP_new_by_curve_name(nid);
		ret=EC_GROUP_check(group,NULL); /*�����Բ���ߣ��ɹ����� 1*/ 
	}


	group = EC_GROUP_new_by_curve_name(CheckCurve);
	ret=EC_GROUP_check(group,NULL); /*�����Բ���ߣ��ɹ����� 1*/ 
	if ( ret == 1){
		printf("\nEC_GROUP_checks seccess : %s \n\n", "CheckCurve");
	}

	OPENSSL_free(curves);


	return 0;
}