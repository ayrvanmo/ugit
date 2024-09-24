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

    return false;
    
}

/**
 * @brief Copia y pega un archivo en otro directorio
 * 
 * @param file_name Archivo
 * @param destination Ruta de destino
 * 
 * @note La funcion no funciona si se quiere copiar y pegar un directorio
 */

void copy_and_paste (char* file_name, char* destination)
{
    char comando[1024]; 

    sprintf(comando, "cp %s %s", file_name, destination);

    if(system(comando))
        perror("ERROR: No se pudo mover el archivo");
}

/**
 * @brief Verifica si una carpeta se encuentra vacia
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

	if(folder_dir){
        while ((file_on_folder = readdir(folder_dir)) != NULL) {
            if (strcmp(file_on_folder->d_name, ".") != 0 && strcmp(file_on_folder->d_name, "..") != 0){
                closedir(folder_dir);
                return false;
            }
        }
        closedir(folder_dir);
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
    return(strcmp(entry->d_name, ".") == 0 ||  strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, "ugit") == 0 || strcmp(entry->d_name, ".ugit") == 0);
}
/**
 * @brief Verifica si se ingreso un comando valido
 * 
 * @param command El comando ingesado
 * @return true 
 * @return false 
 */
bool is_valid_command(char* command){
    return(strcmp(command, "add") == 0 || strcmp(command, "rm") == 0 || strcmp(command, "commit") == 0 || strcmp(command, "log") == 0 || strcmp(command, "checkout") == 0 || strcmp(command, "set.name") == 0 || strcmp(command, "help") == 0 || strcmp(command, "init") == 0 || strcmp(command, "status") == 0 );
}