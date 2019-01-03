#include "fruit.h"
int do_insert(sqlite3 *db)
{
	struct  data_base fru;
	printf("Input id:");
	scanf("%d",&(fru.id));
	
	printf("Input name:");
	scanf("%s",fru.name);

	printf("Input price:");
	scanf("%d",&(fru.price));

	printf("Input stock:");
	scanf("%d",&(fru.stock));

	fill_time(fru.purchase_t);
	fill_time(fru.sold_t);
	printf("%s\n",fru.purchase_t);
	
	sprintf(fru.sql, "insert into "TABLE_NAME" values(%d,'%s', %d, %d,'%s', '%s');",
			fru.id, fru.name, fru.price, fru.stock, fru.purchase_t, fru.sold_t);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	} else {
		printf("Insert Done\n");
	}
	return 0;
}
int do_update(sqlite3 *db)
{
	struct  data_base fru;
	printf("Input id:");
	scanf("%d",&(fru.id));
	printf("Input price:");
	scanf("%d",&(fru.price));
	sprintf(fru.sql, "update "TABLE_NAME" set price = %d where id = %d ;", fru.price, fru.id);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	} else {
		printf("Update Done\n");
	}

	return 0;
}
int do_query(sqlite3 *db)
{
	char *errmsg;
	char ** resultp;
	int nrow;
	int ncolumn;

	if(sqlite3_get_table(db, "select * from "TABLE_NAME, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK){
		printf("%s\n", errmsg);
	} else{ 
		printf("Query done\n");
	}

	int i = 0, j = 0;
	int index = 0;

	for(i = 0; i < nrow + 1; i++){
		for(j = 0; j < ncolumn; j++){
			printf("%-13s ",resultp[index++]);
		}
		putchar(10);
	}
	return 0;
}
int do_delete(sqlite3 *db)
{
	struct  data_base fru;
	printf("Input id:");
	scanf("%d",&(fru.id));
	sprintf(fru.sql, "delete from "TABLE_NAME" where id = %d;", fru.id);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	} else {
		printf("Delete Done\n");
	}
	return 0;
}
int do_purchase(sqlite3 *db)
{
	struct  data_base fru;
	int num;
	printf("Input id:");
	scanf("%d",&(fru.id));
	printf("Input purchase num:");
	scanf("%d",&(num));
	sprintf(fru.sql, "update "TABLE_NAME" set stock = (select stock from "TABLE_NAME" where id = %d) + %d "
			"where id = %d;", fru.id, num, fru.id);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	}
	fill_time(fru.purchase_t);
	sprintf(fru.sql, "update "TABLE_NAME" set purchase_t= '%s' where id = %d;", fru.purchase_t, fru.id);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	} else {
		printf("purchase  Done\n");
	}

	return 0;
}
int do_sold(sqlite3 *db)
{
	struct  data_base fru;
	int num;
	printf("Input id:");
	scanf("%d",&(fru.id));
	printf("Input purchase num:");
	scanf("%d",&(num));
	sprintf(fru.sql, "update "TABLE_NAME" set stock = (select stock from "TABLE_NAME" where id = %d) - %d "
			"where id = %d;", fru.id, num, fru.id);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	}
	fill_time(fru.purchase_t);
	sprintf(fru.sql, "update "TABLE_NAME" set sold_t =  '%s' where id = %d;", fru.purchase_t, fru.id);
	if(sqlite3_exec(db, fru.sql, NULL, NULL, &(fru.errmsg)) != SQLITE_OK){
			printf("%s\n",fru.errmsg);	
	} else {
		printf("sold Done\n");
	}

	return 0;
}

int fill_time(char * s)
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	sprintf(s, "%d-%d-%d %d:%d",(1900+p->tm_year)%100, 1+p->tm_mon,\
			p->tm_mday, p->tm_hour, p->tm_min);
	/*sprintf(s, "%d-%d-%d %d:%d:%d", 1900+p->tm_year, 1+p->tm_mon,\
			p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);*/
	return 0;
}
