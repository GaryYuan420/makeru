#include "fruit.h"

int main(void)
{
	sqlite3 *db;
	char *errmsg;
	int selc;
	if(sqlite3_open(DATABASE, &db) != SQLITE_OK){
		printf("%s\n", sqlite3_errmsg(db));
		exit(-1);
	} else {
		printf("open DATABASE success\n");
	}
	if(sqlite3_exec(db, "create table if not exists "TABLE_NAME"(id int, name char,"
		"price int, stock int, purchase_t char, sold_t char);",
				NULL, NULL, &errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
	} else {
		printf("create or open table success\n");
	}
	while(1){
		printf("**********************************************************\n");
		printf("1:insert 2:query 3.modify 4:delete 5:purchase 6:sold 7:quit\n");
		printf("**********************************************************\n");
		printf("please select:");
		scanf("%d", &selc);

		switch(selc) {
		case 1:
			do_insert(db);
			break;
		case 2:
			do_query(db);
			break;
		case 3:
			do_update(db);
			break;
		case 4:
			do_delete(db);
			break;
		case 5:
			do_purchase(db);
			break;
		case 6:
			do_sold(db);
			break;
		case 7:
			printf("main exit\n");
			sqlite3_close(db);
			exit(0);
			break;
		default:
			printf("invalid data\n");
		}

	}

}
