#include "busqueda.h"

#define NAME_MAX 100
#define TABLE_SIZE 100

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

/*
void init_hash_table(input * hash_table[TABLE_SIZE]){

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    
}
*/


/*
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


*/