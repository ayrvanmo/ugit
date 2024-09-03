#include "archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// FUNCION PARA VERIFICAR LA INICIALIZACION DE UN ARCHIVO
bool is_initialized(char file_name[]){ 

    FILE *ugit=fopen(file_name,"r");

    if(ugit!=NULL){

        return true;

    }
    else{

        return false;

    }
}
