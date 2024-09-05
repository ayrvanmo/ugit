#include "busqueda.h"

#define NAME_MAX 100
#define phi 1.618033988749895
#define TABLE_SIZE 100

unsigned int hash(char name[]){

    int lenght = strnlen(name, NAME_MAX);

    unsigned int hash_value = 0;

    for (int i = 0; i < lenght; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i] * phi ) ;

        return hash_value % TABLE_SIZE;

    }
    
}

void init_hash_table(input * hash_table[TABLE_SIZE]){

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    
}

void print_table(input * hash_table[TABLE_SIZE]){

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] != NULL)
        {
            printf("%s\n", hash_table[i]->name);
        }
        else
        {
            printf("VACIO\n");
        }
        
    }
    
}

void insert(input * hash_table[TABLE_SIZE], char *name, input *next){

     int index = hash(name);


    if (hash_table[index] == NULL)
    {
        hash_table[index] = (input *)malloc(sizeof(input));
        hash_table[index]->name = name;
        next= hash_table[index];     

    }
    else
    {
        printf("Colision en el indice %d\n", index);
    }
    
}
