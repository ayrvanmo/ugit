/**
 * @file archivos.c
 * @author Mansilla-Morrison
 * @brief Funciones relacionadas a archivos
 * @version 1.5
 * 
 * 
 */
#include "archivos.h"


/**
 * @brief Verifica si un archivo o directorio existe
 * 
 * @param file_name  Nombre de la ruta del archivo

 * @return true 
 * @return false 
 */
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


/**
 * @brief Copia y pega un archivo en otro directorio
 * 
 * @param file_name Archivo
 * @param destination Ruta de destino
 * 
 * @note La función no funciona si se quiere copiar y pegar un directorio
 */

void copy_and_paste (char* file_name, char* destination)
{
    char comando[1024]; 

    sprintf(comando, "cp %s %s", file_name, destination);

    if(system(comando))
        perror("ERROR: No se pudo mover el archivo");
}


/**
 * @brief Verifica si una carpeta se encuentra vacía
 * 
 * @param folder Ruta  de la carpeta
 * @return true 
 * @return false 
 */
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
/**
 * @brief Verifica si un elemento de una carpeta es un archivo importante
 * 
 * @param entry El elemento a verificar
 * @return true 
 * @return false 
 */
bool is_core_file(struct dirent *entry)
{  
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, "ugit") != 0 &&strcmp(entry->d_name, ".ugit") != 0) {
        return false;
	}

    else{
        return true;
    }

}