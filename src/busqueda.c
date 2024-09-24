/**
 * @file busqueda.c
 * @author Mansilla-Morrison
 * @brief Funciones relacionadas a tablas hash
 * @version 1.5
 * 
 */
#include "busqueda.h"
#include "archivos.h"



/**
 * @brief Funcion hash para caracteres conocidos
 * 
 * @param key Texto a realizar hash
 * @return unsigned int Devuelve el hash
 */
unsigned int jenkins_hash(char* key)
{
   unsigned int hash = 0;

   while (*key){
      hash += (unsigned char)(*key);
      hash += (hash << 10);     
      hash ^= (hash >> 6);
       
      key++;
   }

   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);
   
   return hash % TABLE_SIZE;
}

/**
 * @brief Funcion hash para caracteres desconocidos
 * 
 * @param key Caracteres
 * @param lenght Tamanho de los caracteres
 * @return unsigned int Devuelve el hash
 * 
 * @note Funcion ideal para contenido de archivos
 */
unsigned int Dinamic_jenkins (unsigned char *key, size_t lenght)
{
    unsigned int hash = 0;

    for (size_t i = 0; i < lenght ; i++){
        hash += key [ i ];
        hash += ( hash << 10);
        hash ^= ( hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
 * @brief Funcion hash para el contenido de un archivo
 * 
 * @param filename Ruta del archivo
 * @return unsigned int Devuelve el hash
 */
unsigned int hashFile(const char *filename)
{

    FILE *file = fopen (filename, "rb"); // Abrir el archivo en modo binario

    if (!file){
        perror("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Determinar el tamanho del archivo
    fseek (file, 0, SEEK_END);
    long fileSize = ftell (file);
    fseek (file, 0, SEEK_SET);

    // Leer el contenido del archivo
    unsigned char* buffer = (unsigned char*) malloc(fileSize* sizeof(unsigned char));

    if (!buffer){
        perror ("No se puede asignar memoria");
        fclose (file);
        exit (EXIT_FAILURE);
    }

    fread (buffer , sizeof(unsigned char), fileSize, file);
    fclose (file);

    // Calcular el hash del contenido
    unsigned int hash = Dinamic_jenkins(buffer , fileSize);

    // Liberar la memoria del buffer
    free (buffer);

    return hash;    
}

/**
 * @brief Inicializa una tabla hash internamente
 * 
 * @param hashtable Tabla hash
 */
void init_table(HashTable *hashtable)
{

    for (int i = 0; i < TABLE_SIZE; i++){
        
        for (int j = 0; j < COLITION_SIZE; j++){
          
            hashtable->table[i][j].is_occupied = false;
            hashtable->table[i][j].value = 0;
            sprintf(hashtable->table[i][j].key, "VACIO");

        }    

    }
    
}

/**
 * @brief Insertar hash en una tabla hash
 * 
 * @param hashtable Tabla hash
 * @param key Caracteres a realizar hash
 * @param value Elemento a ingresar
 * @param columns Numero de columna en caso de colision
 */
void insert_hash(HashTable * hashtable, char* key, int value, int * columns)
{

    unsigned int index = jenkins_hash(key);
    *columns = 0;
    for (int i = 0; i < COLITION_SIZE; i++){
        //PARA INSERTAR EL VALOR
        if(hashtable->table[index][i].is_occupied == false && strlen(key) < MAX_CHAR){
            sprintf(hashtable->table[index][i].key, key);
            hashtable->table[index][i].value = value;
            hashtable->table[index][i].is_occupied = true;            
            return;
        }
        //EN EL CASO DE QUE LA KEY SEA LA MISMA, SE ACTUALIZARA EL VALOR
        else if(strcmp(hashtable->table[index][i].key,key) == 0){
            hashtable->table[index][i].value = value;
            return;
        }
        //EN EL CASO DE QUE SEA MUY LARGO EL NOMBRE
        else if(strlen(key) > MAX_CHAR){
            printf("La key es muy larga\n");
            return;
        }
        //EN EL CASO DE QUE EXISTA UNA COLICION
        else {
            int j = i;
            while (hashtable->table[index][j].is_occupied == true && j < COLITION_SIZE){
                j++;
                (*columns)++;               
            }
            if (hashtable->table[index][j].is_occupied == false) { 
                sprintf(hashtable->table[index][j].key, key);
                hashtable->table[index][j].value = value;
                hashtable->table[index][j].is_occupied = true;
                return;
            }     
        }
        printf("No se ha encontrado espacio para insertar un nuevo elemento\n"); 
    }

}
/** 
 * @brief Insertar el hash del contenido de un achivo en una tabla hash
 * 
 * @param hashtable Tabla hash
 * @param filename Nombre del archivo
 * @param value ELemento a ingresar
 * @param columns Numero de columna en caso de colision
 */
void insert_hashfile(HashTable * hashtable, const char * filename, int value, int * columns){

    unsigned int index = hashFile(filename)%TABLE_SIZE;
    *columns = 0;
    for (int i = 0; i < COLITION_SIZE; i++){

        //PARA INSERTAR EL VALOR
        if(hashtable->table[index][i].is_occupied == false){
            sprintf(hashtable->table[index][i].key, filename);
            hashtable->table[index][i].value = value;
            hashtable->table[index][i].is_occupied = true;   
            return;
        }
        //EN EL CASO DE QUE LA KEY SEA LA MISMA, SE ACTUALIZARA EL VALOR
        else if(strcmp(hashtable->table[index][i].key,filename) == 0){
            hashtable->table[index][i].value = value;
            return;
        }
         //EN EL CASO DE QUE SEA MUY LARGO EL NOMBRE
        else if(strlen(filename) > MAX_CHAR){
            printf("La key es muy larga\n");
            return;
        }
        //EN EL CASO DE QUE EXISTA UNA COLICION
        else{
            int j = i;

            while (hashtable->table[index][j].is_occupied == true && j < COLITION_SIZE){
                j++;
                *columns = *columns + 1;
            }

            if (hashtable->table[index][j].is_occupied == false) { 
                sprintf(hashtable->table[index][j].key, filename);
                hashtable->table[index][j].value = value;
                hashtable->table[index][j].is_occupied = true; 
                return;
            }
        }
        printf("No se ha encontrado espacio para este commit, considere utilizar 'ugit reset'\n "); 
        
    }
    
}

/**
 * @brief Borra un elemento dentro de una tabla hash
 * 
 * @param hashtable Tabla hash
 * @param key Caracter relacionado al elemento
 */
void delete_element(HashTable * hashtable, char * key){

    unsigned int index = jenkins_hash(key);
    for(int i = 0; i < COLITION_SIZE; i++){

        if(hashtable->table[index][i].is_occupied == true)
        {
            hashtable->table[index][i].is_occupied = false;
            sprintf(hashtable->table[index][i].key, "VACIO");
            hashtable->table[index][i].value = 0;
            return;
        }

        //EN EL CASO DE QUE EXISTA UNA COLICION
        else
        {
            int j = i;

            while (hashtable->table[index][j].is_occupied == false && j < COLITION_SIZE ){
                j++;
            }
               
            if (hashtable->table[index][j].is_occupied == true) { 
                hashtable->table[index][i].is_occupied = false;
                sprintf(hashtable->table[index][i].key, "VACIO");
                hashtable->table[index][i].value = 0;
                return;
            }
        }
    }
    printf("No se encontro el elemento buscado!!\n");
}

/**
 * @brief Borra un elemento proveniente de un archivo dentro de una tabla hash
 * 
 * @param hashtable Tabla hash
 * @param filename Nombre del archivo
 */
void delete_elementfile(HashTable * hashtable, const char * filename){

    unsigned int index = hashFile(filename);
    for(int i = 0; i < COLITION_SIZE; i++){
        if(hashtable->table[index][i].is_occupied == true)
        {
            hashtable->table[index][i].is_occupied = false;
            sprintf(hashtable->table[index][i].key, "VACIO");
            hashtable->table[index][i].value = 0;
            return;
        }
        //EN EL CASO DE QUE EXISTA UNA COLICION
        else
        {
            int j = i;
            while (hashtable->table[index][j].is_occupied == false && j < COLITION_SIZE )
            {
                j++;
            }

            if (hashtable->table[index][j].is_occupied == true) { 
                hashtable->table[index][i].is_occupied = false;
                sprintf(hashtable->table[index][i].key, "VACIO");
                hashtable->table[index][i].value = 0;
                return;
            }
        }
    }
    printf("No se encontro el elemento buscado!!\n");
}

/**
 * @brief Imprime una tabla hash en pantalla
 * 
 * @param hashtable Tabla hash
 */
void print_table(HashTable* hashtable) {

    for (int i = 0; i < TABLE_SIZE ; i++) {
        printf("Index %d:", i);
        for (int j = 0; j < COLITION_SIZE; j++) {
            if (hashtable->table[i][j].is_occupied) 
                printf("[%d][%d] Key: %s, Value: %d ", i, j, hashtable->table[i][j].key, hashtable->table[i][j].value);      
        }
        printf("\n");
    }
}

/**
 * @brief Imprime y guarda una tabla hash dentro de un archivo
 * 
 * @param hashtable Tabla hash
 * @param filename Nombre del archivo
 * 
 */
void print_tablefile(HashTable* hashtable, const char * filename) {

    FILE * file = fopen ( filename , "w");
    if (!file) {
        perror ("No se puede abrir el archivo");
        exit (EXIT_FAILURE);
    }
    for (int i = 0; i < TABLE_SIZE ; i++) {
        for (int j = 0; j < COLITION_SIZE; j++) {
            fprintf(file, "%s %d %d ", hashtable->table[i][j].key, hashtable->table[i][j].value, hashtable->table[i][j].is_occupied);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/**
 * @brief Escanea una tabla hash proveniente de un archivo y lo guarda en el programa
 * 
 * @param hashtable Tabla hash
 * @param filename Nombre del archivo
 * 
 * @note El archivo debe estar en el formato que consigue con la funcion "print_tablefile"
 */
void save_table(HashTable* hashtable, const char * filename) {

    FILE * file = fopen ( filename , "r");

    if (!file) {
        perror ("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
   }   
    for(int i = 0 ; i < TABLE_SIZE; i++){
        for (int j= 0; j < COLITION_SIZE; j++){
            fscanf(file, "%s %d %d", hashtable->table[i][j].key, &hashtable->table[i][j].value, (int*)&hashtable->table[i][j].is_occupied);
        }
    }
}

