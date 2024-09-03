#include "archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isinitialized(){ // función para  verificar si ugit está inicializado o no

    FILE *ugit=fopen(".ugit","r");

    if(ugit!=NULL){
        return true;
    }
    else{
        return false;
    }
}