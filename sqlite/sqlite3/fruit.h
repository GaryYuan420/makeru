#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>
#define  DATABASE  "fruit.db"
#define  TABLE_NAME "fruit"
#define  N  128

struct data_base{
	int id;
	char name[32];
	int price;
	int stock;
	char purchase_t[32];
	char sold_t[32];
	char sql[N];
	char *errmsg;
};


int do_insert(sqlite3 *db);
int do_query(sqlite3 *db);
int do_update(sqlite3 *db);
int do_delete(sqlite3 *db);
int do_purchase(sqlite3 *db);
int do_sold(sqlite3 *db);
int fill_time(char * s);
