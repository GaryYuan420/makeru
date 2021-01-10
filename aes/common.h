
#define AES_KEY_SIZE 32
#define DATA_MAX_SIZE 2048
#define IV_MAX_SIZE 32
unsigned char CryptKey[] = {"0CC175B9C0F1B6A831C399E269772661CEC520EA51EA0A47E87295FA3245A605"};
const unsigned char PlainText[] = {"My"};
void HexPrint(char* claim, unsigned char *AesKey, int len);
int Str2Hex(unsigned char *Str, unsigned char *Hex);

#define AES_MODE_CBC 1
#define AES_MODE_CFB 2
#define AES_MODE_OFB 3
#define AES_MODE_ECB 4
