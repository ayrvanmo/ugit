#include "busqueda.h"



//FUNCION HASH PARA CARACTERES ESTATICOS
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


/*FUNCION HASH PARA CARACTERES DINAMICOS*/
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


// FUNCION HASH PARA EL CONTENIDO DE UN ARCHIVO
unsigned int hashFile(const char *filename)
{

    FILE *file = fopen (filename, "rb"); // Abrir el archivo en modo binario

    if (!file){
        perror("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
    }

// Determinar el tamaño del archivo
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




// FUNCION PARA INICIALIZAR LA TABLA HASH
void init_table(HashTable *hashtable)
{

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        
        for (int j = 0; j < COLITION_SIZE; j++)
        {
          
            

            hashtable->table[i][j].is_occupied = false;
            
            hashtable->table[i][j].value = 0;
            
            sprintf(hashtable->table[i][j].key, "VACIO");

        }    

    }
    
}

// FUNCION PARA INSERTAR UN HASH DENTRO DE UNA TABLA
void insert_hash(HashTable * hashtable, char* key, int value, int * columns){

    
    unsigned int index = jenkins_hash(key);
    *columns = 0;



    for (int i = 0; i < COLITION_SIZE; i++){


        //PARA INSERTAR EL VALOR
        if(hashtable->table[index][i].is_occupied == false && strlen(key) < MAX_CHAR)
        {

            sprintf(hashtable->table[index][i].key, key);
            hashtable->table[index][i].value = value;
            hashtable->table[index][i].is_occupied = true;
            
            return;

        }

        //EN EL CASO DE QUE LA KEY SEA LA MISMA, SE ACTUALIZARA EL VALOR
        else if(strcmp(hashtable->table[index][i].key,key) == 0)
        {

            hashtable->table[index][i].value = value;
            return;

        }

        //EN EL CASO DE QUE SEA MUY LARGO EL NOMBRE
        else if(strlen(key) > MAX_CHAR)
        {

            printf("La key es muy larga\n");
            return;

        }

        //EN EL CASO DE QUE EXISTA UNA COLICION
        else {

        int j = i;

        while (hashtable->table[index][j].is_occupied == true && j < COLITION_SIZE)
        {
            j++;
            *columns = *columns + 1;

        }

        if (hashtable->table[index][j].is_occupied == false) { 

            sprintf(hashtable->table[index][j].key, key);
            hashtable->table[index][j].value = value;
            hashtable->table[index][j].is_occupied = true;
            
            return;
        }

        else
        {

        }
        
        }

        printf("No se ha encontrado espacio para insertar un nuevo elemento \n "); 


    }

}

//FUNCION PARA INSERTAR EL HASH DE UN ARCHIVO
void insert_hashfile(HashTable * hashtable, const char * filename, int value, int * columns){

    
    unsigned int index = hashFile(filename);
    *columns = 0;


    for (int i = 0; i < COLITION_SIZE; i++){


        //PARA INSERTAR EL VALOR
        if(hashtable->table[index][i].is_occupied == false)
        {

            sprintf(hashtable->table[index][i].key, filename);
            hashtable->table[index][i].value = value;
            hashtable->table[index][i].is_occupied = true;
            
            return;

        }

        //EN EL CASO DE QUE LA KEY SEA LA MISMA, SE ACTUALIZARA EL VALOR
        else if(strcmp(hashtable->table[index][i].key,filename) == 0)
        {

            hashtable->table[index][i].value = value;
            return;

        }

         //EN EL CASO DE QUE SEA MUY LARGO EL NOMBRE
        else if(strlen(filename) > MAX_CHAR)
        {

            printf("La key es muy larga\n");
            return;

        }

        //EN EL CASO DE QUE EXISTA UNA COLICION
        else
        {
        int j = i;

        while (hashtable->table[index][j].is_occupied == true && j < COLITION_SIZE)
        {
            j++;
            *columns = *columns + 1;
        }

        if (hashtable->table[index][j].is_occupied == false) { 

            sprintf(hashtable->table[index][j].key, filename);
            hashtable->table[index][j].value = value;
            hashtable->table[index][j].is_occupied = true;
            
            return;
        }

        else
        {

        }
        
        }

        printf("No se ha encontrado espacio para insertar un nuevo elemento \n "); 



    }

}

//FUCNION PARA BUSCAR UN VALOR EN LA TABLA
int search_table(HashTable * hashtable, char * key){

    unsigned int index = jenkins_hash(key);

    for(int i = 0; i < COLITION_SIZE; i++){

        if(hashtable->table[index][i].is_occupied == true)
        {

            return hashtable->table[index][i].value;

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

            return hashtable->table[index][i].value;

        }
  
        }

    }

    printf("No se ha encontrado el elemento\n");
    return -1;

}

//FUNCION PARA BUSCAR UN VALOR EN LA TABLA PERO DESDE UN ARCHIVO
int search_tablefile(HashTable * hashtable, const char * filename){

    unsigned int index = hashFile(filename);

    for(int i = 0; i < COLITION_SIZE; i++){

        if(hashtable->table[index][i].is_occupied == true)
        {

            return hashtable->table[index][i].value;

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

            return hashtable->table[index][i].value;

        }
  
        }

    }

    printf("No se ha encontrado el elemento\n");
    return -1;



}

//FUNCION PARA BORRAR UN ELEMENTO
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

//FUNCION PARA BORRAR UN ELEMENTO DESDE ARCHIVO
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

//FUNCION PARA IMPRIMIR LA TABLA
void print_table(HashTable* hashtable) {

    for (int i = 0; i < TABLE_SIZE ; i++) {

        printf("Index %d:", i);

        for (int j = 0; j < COLITION_SIZE; j++) {

            if (hashtable->table[i][j].is_occupied) {

                printf("[%d][%d] Key: %s, Value: %d ", i, j, hashtable->table[i][j].key, hashtable->table[i][j].value);

            }
        }
        printf("\n");
    }
}

//FUNCION PARA IMPRIMRI UNA TABLA HASH EN UN ARCHIVO
void print_tablefile(HashTable* hashtable, const char * filename) {

    FILE * file = fopen ( filename , "w");

    if (! file ) {

        perror ( "No se puede abrir el archivo" );
        exit ( EXIT_FAILURE );

    }

    for (int i = 0; i < TABLE_SIZE ; i++) {
        


        for (int j = 0; j < COLITION_SIZE; j++) {
   
            fprintf(file, "%s %d %d ", hashtable->table[i][j].key, hashtable->table[i][j].value, hashtable->table[i][j].is_occupied);
            
        }

        fprintf(file, "\n");
    }

    fclose(file);

}

//FUNCION PARA GUARDAR UNA TABLA HASH DESDE UN ARCHIVO
void save_table(HashTable* hashtable, const char * filename) {

    FILE * file = fopen ( filename , "r");

    if (!file ) {

        perror ( "No se puede abrir el archivo" );
        exit ( EXIT_FAILURE );

   }
    
    for(int i = 0 ; i < TABLE_SIZE; i++){

        


        for (int j= 0; j < COLITION_SIZE; j++){

            

            fscanf(file, "%s %d %d", hashtable->table[i][j].key, &hashtable->table[i][j].value, (int*)&hashtable->table[i][j].is_occupied);
            

        }

    }
    
}

