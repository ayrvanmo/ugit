/**
 * @file busqueda.h
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*! @def TABLE_SIZE
*  @brief Tamaño vertical máximo de las tablas hash
*/
#define TABLE_SIZE 100
/*! @def COLITION_SIZE
*  @brief Tamaño horizontal máximo de las tablas hash, hecho para evitar colisiones
*/
#define COLITION_SIZE 10
/*! @def MAX_CHAR
*  @brief Tamaño máximo de caractéres para algunos strings
*/
#define MAX_CHAR 255


/*! \struct HashEntry
*  @brief Estructura que representa 1 elemento de la tabla hash
*/
typedef struct{
    char key[MAX_CHAR]; /*!< Nombre del elemento */
    int value; /*!< Valor hash*/
    bool is_occupied; /*!< Indica si la celda está ocupada o no*/
} HashEntry;

/*! \struct HashTable
*  @brief Estructura que representa una tabla hash.
*/
typedef struct {    
    HashEntry table[TABLE_SIZE][COLITION_SIZE]; /*!< Arreglo de HashEntry */
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

