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

    if (file != NULL)
    {
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
        printf("'%s' ha sido agregado exitosamente",  file_name);
      }
      else {
        printf("ERROR: '%s' no pudo ser agregado",  file_name);

      }

}


bool is_folder_empty(char* folder){
    char command[1024];
    
    snprintf(command, sizeof(command), "ls -A %s | wc -l", folder);

    FILE* f=popen(command, "r");
    if (f==NULL) {
        perror("Error al verificar  si el directorio esta vacio");
        return -1;
    }

    int cantidad_archivos;
    fscanf(f, "%d", &cantidad_archivos);
    pclose(f);

    if(cantidad_archivos==0){
        return true;
    }
    else {
        return false;
    }

}