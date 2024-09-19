#include "archivos.h"


// FUNCION PARA VERIFICAR SI UN ARCHIVO EXISTE
bool is_initialized(char file_name[])
{ 
    FILE *file = fopen(file_name,"r");

    if(file != NULL){
        fclose(file);
        return true;
    }
    else{
        return false;
    }
}


// FUNCION PARA COPIAR Y PEGAR UN ARCHIVO EN UNA CIERTA DIRECCION
void copy_and_paste (char* file_name, char* destination)
{
    char comando[1024];

    sprintf(comando, "cp %s %s", file_name, destination);

    if(system(comando))
        perror("ERROR: No se pudo mover el archivo");
}


// FUNCION PARA VERIFICAR SI UNA CARPETA ESTA VACIA
bool is_folder_empty(char* folder)
{
    DIR* folder_dir;
    folder_dir = opendir(folder);
    struct dirent *file_on_folder;
    int count;

	if(folder_dir){
        while ((file_on_folder = readdir(folder_dir)) != NULL) {
            if (file_on_folder->d_name[0] != '.')
            count++;
        }

        if(count)
            return false;
        
        return true;
	}

    printf("ERROR:  No se pudo abrir el directorio '%s'\n", folder);
    exit(1);
}