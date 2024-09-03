/**
 * @file main.c
 * @author mansilla-morrison
 * @brief 
 * @version 0.2
 * @date 2024-09-02
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "archivos.h"



/**
 * @brief 
 * 
 * @param argc numero de argumentos ingresados en el terminal. Empieza del 1, ya que el primer argumento es el nombre del programa
 * @param argv argumentos ingresados en el terminal. argv[1] es el primero que se ingresa, argv[2] el segundo, y así
 * 
 */

int main(int argc, char** argv){


    if(argc>1){ //si se colocó algún argumento

      if(strcmp(argv[1],"help")==0){ // comando para mostrar ayuda
        printf("Comandos comunes de uGit:\n\n");
				printf("Para inicializar un area de trabajo\n   init       Crear un repositorio vacio\n\nTrabajar y realizar cambios actuales\n   add        Agregar contenido de archivos\n   rm         Borrar archivos del arbol de trabajo\n\nModificar el historial comun\n   branch     Listar, crear o borrar ramas\n   commit     Grabar los cambios del repositorio\n   switch     Cambiar el nodo/branch\n\nPara colaborar\n   pull       Realiza una descarga de objetos y referencias de otro repositorio y lo integra al actual o al de la rama actual\n   push       Actualizar las referencias remotas con sus objetos asociados\n");
      } else


      /*COMANDO PARA INICIALIZAR REPOSITORIO*/
      if(strcmp(argv[1],"init")==0){

          if(isinitialized()){// Si ya está inicializado,  mostrar mensaje de que ya lo está
            printf("uGit ya se encuentra inicializado en el directorio");
          }
          else{ // Si no está inicializado, inicializarlo
            system("touch .ugit");
            if(isinitialized())
              printf("Repositorio inicializado exitosamente");
            else
              printf("ERROR: No se pudo inicializar uGit");
          }
      }





      else{ // si no se  colocó un comando válido
        printf("Uso: 'ugit [comando]'\n'ugit help' para ver la lista de comandos disponibles");
      }



    



    }
    else { //si ugit es ejecutado sin ningún argumento
      printf("Uso: 'ugit [comando]'\n'ugit help' para ver la lista de comandos disponibles");
    }

  return 0;
}
