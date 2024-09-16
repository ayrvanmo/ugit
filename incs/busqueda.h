#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_MAX 100
#define TABLE_SIZE 100
#define COLITION_SIZE 10
#define MAX_CHAR 30




typedef struct {
    // metadatos
    char *author;
    


} commit;

typedef struct{

    char key[MAX_CHAR];
    int value;
    bool is_occupied;

} HashEntry;

typedef struct {
    
    HashEntry table[TABLE_SIZE][COLITION_SIZE];

} HashTable;




unsigned int jenkins_hash(char* key);
unsigned int hashFile ( const char * filename );
unsigned int Dinamic_jenkins ( unsigned char * key , size_t lenght );
void init_table(HashTable *hashtable);
void insert_hash(HashTable * hashtable, char* key, int value);
void insert_hashfile(HashTable * hashtable, const char * filename, int value);
int search_table(HashTable * hashtable, char * key);
int search_tablefile(HashTable * hashtable, const char * filename);
void delete_element(HashTable * hashtable, char * key);
void delete_elementfile(HashTable * hashtable, const char * filename);
void print_table(HashTable* hashtable);


