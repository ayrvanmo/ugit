#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_MAX 100
#define TABLE_SIZE 100


typedef struct {
    char *name;
    //para hacer una mini lista enlazada
    struct input *next;
    

    //cosas que se vayan a anhadir
    
} input;


unsigned int hash(char name[]);
void init_hash_table(input * hash_table[TABLE_SIZE]);
void print_table(input * hash_table[TABLE_SIZE]);
void insert(input * hash_table[TABLE_SIZE], char name[]);