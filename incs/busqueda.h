/**
 * @file archivos.h
 * @author Iván Mansilla y Ayrton Morrison
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*! @def TABLE_SIZE
*  @brief Tamanho vertical maximo de las tablas hash
*/
#define TABLE_SIZE 1000
/*! @def COLITION_SIZE
*  @brief Tamanho horizontal maximo de las tablas hash, hecho para evitar colisiones
*/
#define COLITION_SIZE 10
/*! @def MAX_CHAR
*  @brief Tamanho maximo de caracteres para algunos strings
*/
#define MAX_CHAR 255
/**!@def COMMAND
 * @brief Tamanho maximo de caracteres para comando
 */
#define COMMAND 1060


/*! \struct HashEntry
*  @brief Estructura que representa 1 elemento de la tabla hash
*/
typedef struct{
    char key[MAX_CHAR]; /*!< Caracteres asociados al hash */
    int value; /*!< Elemento ingresado*/
    bool is_occupied; /*!< Indica si la celda esta ocupada o no*/
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
void print_tablefile(HashTable* hashtable, const char *filename);
void save_table(HashTable* hashtable, const char * filename);

