#include "busqueda.h"

#define NAME_MAX 100
#define TABLE_SIZE 100
#define COLITION_SIZE 10

//FUNCION HASH PARA CARACTERES ESTATICOS
unsigned int jenkins_hash(char* key){

   unsigned int hash = 0;
   

   while (*key) {

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

//FUNCION HASH PARA CARACTERES DINAMICOS
unsigned int Dinamic_jenkins ( unsigned char * key , size_t lenght ) {

    unsigned int hash = 0;
    for ( size_t i = 0; i < lenght ; i ++) {
        hash += key [ i ];
        hash += ( hash << 10);
        hash ^= ( hash >> 6);
    }
    hash += ( hash << 3);
    hash ^= ( hash >> 11);
    hash += ( hash << 15);

    return hash ;
}

// FUNCION HASH PARA EL CONTENIDO DE UN ARCHIVO
unsigned int hashFile ( const char * filename ) {

    FILE * file = fopen ( filename , "rb" ); // Abrir el archivo en modo binario

    if (! file ) {

        perror ( " No se puede abrir el archivo " );
        exit ( EXIT_FAILURE );

    }

// Determinar el tamanho del archivo
    fseek ( file , 0 , SEEK_END );

    long fileSize = ftell ( file );

    fseek ( file , 0 , SEEK_SET );
// Leer el contenido del archivo
    unsigned char * buffer = ( unsigned char *) malloc ( fileSize * sizeof ( unsigned char ));

    if (! buffer ) {

        perror ( " No se puede asignar memoria " );
        fclose ( file );
        exit ( EXIT_FAILURE );
}
    fread ( buffer , sizeof ( unsigned char ) , fileSize , file );
    fclose ( file );

// Calcular el hash del contenido
    unsigned int hash = Dinamic_jenkins( buffer , fileSize );

// Liberar la memoria del buffer
    free ( buffer );

    return hash;

}

// FUNCION PARA INICIALIZAR LA TABLA HASH
void init_table(HashTable *hashtable){

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (int j = 0; i < COLITION_SIZE; j++)
        {
            hashtable->table[i][j].is_occupied = false;
            hashtable->table[i][j].value = 0;
            strcpy(hashtable->table[i][j].key, "");

        }
        

        

    }
    
}

// FUNCION PARA INSERTAR UN HASH DENTRO DE UNA TABLA
void insert_hash(HashTable * hashtable, char* key, int value){

    
    unsigned int index = jenkins_hash(key);


    for (int i = 0; i < COLITION_SIZE; i++){


        //PARA INSERTAR EL VALOR
        if(hashtable->table[index][i].is_occupied == false)
        {

            strcpy(hashtable->table[index][i].key, key);
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

        //EN EL CASO DE QUE EXISTA UNA COLICION
        else
        {
            
            //VERIFICAR QUE NO ESTE EN EL LIMITE DEL ARRAY
            if (index != TABLE_SIZE){

                unsigned int new_index = index + 1;

                for(int j = 0; j < COLITION_SIZE; j++){

                    if(hashtable->table[new_index][j].is_occupied == false)
                    {

                        strcpy(hashtable->table[new_index][i].key, key);
                        hashtable->table[new_index][i].value = value;
                        hashtable->table[new_index][i].is_occupied = true;
            
                        return;


                    }
                  

                }

                printf("No se ha encontrado espacio para insertar un nuevo elemento \n ");

            }

            else
            {


                unsigned int new_index = index - 1;

                for(int j = 0; j < COLITION_SIZE; j++){

                    if(hashtable->table[new_index][j].is_occupied == false)
                    {

                        strcpy(hashtable->table[new_index][i].key, key);
                        hashtable->table[new_index][i].value = value;
                        hashtable->table[new_index][i].is_occupied = true;
            
                        return;


                    }
                  

                }

                printf("No se ha encontrado espacio para insertar un nuevo elemento \n ");



            }

        }

        printf("No se ha encontrado espacio para insertar un nuevo elemento \n "); 


    }

}

//FUNCION PARA INSERTAR EL HASH DE UN ARCHIVO
void insert_hashfile(HashTable * hashtable, const char * filename, int value){

    
    unsigned int index = hashFile(filename);


    for (int i = 0; i < COLITION_SIZE; i++){


        //PARA INSERTAR EL VALOR
        if(hashtable->table[index][i].is_occupied == false)
        {

            strcpy(hashtable->table[index][i].key, filename);
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

        //EN EL CASO DE QUE EXISTA UNA COLICION
        else
        {
            
            //VERIFICAR QUE NO ESTE EN EL LIMITE DEL ARRAY
            if (index != TABLE_SIZE){

                unsigned int new_index = index + 1;

                for(int j = 0; j < COLITION_SIZE; j++){

                    if(hashtable->table[new_index][j].is_occupied == false)
                    {

                        strcpy(hashtable->table[new_index][i].key, filename);
                        hashtable->table[new_index][i].value = value;
                        hashtable->table[new_index][i].is_occupied = true;
            
                        return;


                    }
                  

                }

                printf("No se ha encontrado espacio para insertar un nuevo elemento \n ");

            }

            else
            {


                unsigned int new_index = index - 1;

                for(int j = 0; j < COLITION_SIZE; j++){

                    if(hashtable->table[new_index][j].is_occupied == false)
                    {

                        strcpy(hashtable->table[new_index][i].key, filename);
                        hashtable->table[new_index][i].value = value;
                        hashtable->table[new_index][i].is_occupied = true;
            
                        return;


                    }
                  

                }

                printf("No se ha encontrado espacio para insertar un nuevo elemento \n ");



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
            strcpy(hashtable->table[index][i].key, "");
            hashtable->table[index][i].value = 0;
            return;

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
            strcpy(hashtable->table[index][i].key, "");
            hashtable->table[index][i].value = 0;
            return;

        }

    }

    printf("No se encontro el elemento buscado!!\n");

}

//FUNCION PARA IMPRIMIR LA TABLA
void print_table(HashTable* hashtable) {

    for (int i = 0; i < TABLE_SIZE; i++) {

        printf("Index %d:\n", i);

        for (int j = 0; j < COLITION_SIZE; j++) {

            if (hashtable->table[i][j].is_occupied) {

                printf("  [%d][%d] Key: %s, Value: %d\n", i, j, hashtable->table[i][j].key, hashtable->table[i][j].value);

            }
        }
    }
}