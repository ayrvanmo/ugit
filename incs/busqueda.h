#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 100
#define COLITION_SIZE 10
#define MAX_CHAR 255




typedef struct {
    // metadatos
    char *autahor;
    


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
void insert_hash(HashTable * hashtable, char* key, int value, int * columns);
void insert_hashfile(HashTable * hashtable, const char * filename, int value, int * columns);
int search_table(HashTable * hashtable, char * key);
int search_tablefile(HashTable * hashtable, const char * filename);
void delete_element(HashTable * hashtable, char * key);
void delete_elementfile(HashTable * hashtable, const char * filename);
void print_table(HashTable* hashtable);
void print_tablefile(HashTable* hashtable, const char *filename);
void save_table(HashTable* hashtable, const char * filename);

