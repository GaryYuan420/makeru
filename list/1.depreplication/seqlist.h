#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define MAXSIZE 100
typedef int data_t;
typedef struct {
	data_t data[MAXSIZE];
	int last;
}seqlist_t;

seqlist_t *create_seqlsit(void);
void clear_seqlsit(seqlist_t *L);

int is_empty_seqlist(seqlist_t *L);
int is_full_seqlist(seqlist_t *L);
void set_empty_seqlist(seqlist_t *L);
int get_length_seqlist(seqlist_t *L);
void show_seqlist(seqlist_t *L);

int insert_seqlist(seqlist_t *L,data_t x,int pos);
int delete_seqlist(seqlist_t *L,int pos);
int change_seqlist(seqlist_t *L,data_t x,int pos);
int search_seqlist(seqlist_t *L,data_t x);

int fill_seqlist(seqlist_t *L,int* str,int size);
#endif
