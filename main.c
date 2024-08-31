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
                printf("funciona");
                break;
            case '?':
                printf("se puso otra cosa");
                exit(EXIT_FAILURE);
        }
    }

    





  return 0;
}
