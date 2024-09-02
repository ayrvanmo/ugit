/**
 * @file main.c
 * @author mansilla-morrison
 * @brief 
 * @version 0.1
 * @date 2024-08-31
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/**
 * @brief 
 * 
 * @param argc numero de argumentos ingresados en el terminal. Empieza del 1, ya que el primer argumento es el nombre del programa
 * @param argv argumentos ingresados en el terminal. argv[1] es el primero que se ingresa, argv[2] el segundo, y así
 * 
 */

int main(int argc, char** argv){
  int option;

    /**
     * @brief 
     * 
     * @param option variable para guardar los argumentos ingresados al ejecutar el programa
     * 
     * En el while se verifican todos los argumentos ingresados. La funcion getopt() en este caso tirará el valor -1 si no se ingresa nada
     * 
     * 
     */
    while((option = getopt(argc, argv, "h"))!=-1){
       switch (option) {
            case 'h':
                printf("Comandos comunes de uGit:\n\n");
						printf("Para inicializar un area de trabajo\n   init       Crear un repositorio vacio\n\nTrabajar y realizar cambios actuales\n   add        Agregar contenido de archivos\n   rm         Borrar archivos del arbol de trabajo\n\nModificar el historial comun\n   branch     Listar, crear o borrar ramas\n   commit     Grabar los cambios del repositorio\n   switch     Cambiar el nodo/branch\n\nPara colaborar\n   pull       Realiza una descarga de objetos y referencias de otro repositorio y lo integra al actual o al de la rama actual\n   push       Actualizar las referencias remotas con sus objetos asociados\n");

                break;
            case '?':
                printf("se puso otra cosa");
                exit(EXIT_FAILURE);
        }
    }

    





  return 0;
}
