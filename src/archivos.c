#include "archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// FUNCION PARA VERIFICAR LA INICIALIZACION DE UN ARCHIVO
bool is_initialized(char file_name[]){ 

    FILE *file=fopen(file_name,"r");

    if(file!=NULL){

        return true;

    }
    else{

        return false;

    }
}

void write_on_file(char file_name[], char text[] ){

    FILE *file = fopen(file_name, "a");

    if (file != NULL)
    {
        fprintf(file, "%s HASHCODE\n", text); // EN ESTa MISMA LINEA INTRODUCIR UN EL CODIGO HASH AL LADO
        


    }
    else{

        printf("No se ha podido abrir el archivete");

    }
    
    
    return ;

}
