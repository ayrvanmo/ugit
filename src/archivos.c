#include "archivos.h"
#include "busqueda.h"


// FUNCION PARA VERIFICAR LA INICIALIZACION DE UN ARCHIVO
bool is_initialized(char file_name[]){ 

    FILE *file=fopen(file_name,"r");

    if(file!=NULL){

        fclose(file);
        return true;

    }
    else{
        return false;
    }

}


void write_on_file(char file_name[], char text[], char mode[]){

    FILE *file = fopen(file_name, mode);

    if (file != NULL){
        fprintf(file, "%s\n", text);
        fclose(file);        
    }
    else{
        printf("ERROR: uGit no tiene los permisos necesarios");
        exit(1);
    }
    return;
}

void copy_and_paste (char* file_name, char* destination){


      char comando[1024];

      sprintf(comando, "cp %s %s", file_name, destination);

      if(!system(comando)){
        printf("'%s' ha sido agregado exitosamente\n",  file_name);
      }
      else {
        printf("ERROR: '%s' no pudo ser agregado\n",  file_name);

      }

}


bool is_folder_empty(char* folder){
    
    DIR *folder_dir;
    folder_dir=opendir(folder);
    struct dirent *file_on_folder;
    int count;

	if(folder_dir){
        
        while ((file_on_folder = readdir(folder_dir)) != NULL) {
            if (file_on_folder->d_name[0] != '.') {
            count++;
            }
        }

        if(count){
            return false;
        }

        return true;
	}

    printf("ERROR:  No se pudo abrir el directorio '%s'\n", folder);
    exit(1);
}