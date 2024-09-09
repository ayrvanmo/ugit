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
#include <sys/stat.h>
#include "archivos.h"
#include "busqueda.h"
#define TABLE_SIZE 100




/**
 * @brief 
 * 
 * @param argc numero de argumentos ingresados en el terminal. Empieza del 1, ya que el primer argumento es el nombre del programa
 * @param argv argumentos ingresados en el terminal. argv[1] es el primero que se ingresa, argv[2] el segundo, y así
 * 
 */


	

int main(int argc, char** argv){


	// EN EL CASO DE QUE SE INGRESE UN COMANDO
    if(argc>1){ 

		// COMANDO PARA MOSTRAR LOS COMANDOS DISPONIBLES
		if(strcmp(argv[1],"help")==0){ 
			printf("Comandos comunes de uGit:\n\n");
			printf("Para inicializar un area de trabajo\n   init       Crear un repositorio vacio\n\nTrabajar y realizar cambios actuales\n   add        Agregar contenido de archivos\n   rm         Borrar archivos del arbol de trabajo\n\nModificar el historial comun\n   branch     Listar, crear o borrar ramas\n   commit     Grabar los cambios del repositorio\n   switch     Cambiar el nodo/branch\n\nPara colaborar\n   pull       Realiza una descarga de objetos y referencias de otro repositorio y lo integra al actual o al de la rama actual\n   push       Actualizar las referencias remotas con sus objetos asociados\n\n");
      	}	 	
		


      /*COMANDO PARA INICIALIZAR REPOSITORIO*/
		else if(strcmp(argv[1],"init")==0){
			
			// EN EL CASO DE ESTAR INICIALIZADO AVISAR QUE YA LO ESTA
			if(is_initialized(".ugit")){
				printf("uGit ya se encuentra inicializado en el directorio\n");
			}

			// INICIALIZAR EL REPOSITORIO
          	else{ 
				system("mkdir .ugit .ugit/commits .ugit/objects");
				system("touch .ugit/COMMIT_MSG .ugit/log .ugit/userinfo .ugit/index");
				

				// ALERTA INICIACION EXITOSA
				if(is_initialized(".ugit")){
					printf("Repositorio inicializado exitosamente\n");
				}
				// ERROR SI NO SE PUEDE INICIALIZAR
				else{
					printf("ERROR: No se pudo inicializar el repositorio\n");
				}
			}

        }






		/*COMANDO PARA AGREGAR ARCHIVOS AL REPOSITORIO*/
		else if(strcmp(argv[1],"add")==0){

			if(is_initialized(".ugit")){ //verificar primero si se hizo ugit init

				if(argc>2){ // verificar si se colocaron más argumentos

					for(int i=2;i<argc;i++){ // recorrer los argumentos puestos
						if(is_initialized(argv[i])){ // verificar si el archivo existe


							/*POR HACER: QUE NO SE COLOQUE EL MISMO ARCHIVO VARIAS VECES*/


							write_on_file(".ugit/index",argv[i],"a");
							printf("El archivo '%s' fue añadido con exito\n", argv[i]);

						}

						else{ // sino, mostrar mensaje de error
							printf("ERROR: El archivo '%s' no existe\n",argv[i]);
						}
					}

				}
				else{ // sino, mostrar mensaje de error
					printf("ERROR: No se especifico el(los) archivo(s) a agregar. Uso: 'ugit add [archivo1] [archivo2]...'\n");
				}

			} // si no está inicializado,  mostrar mensaje de error
			else{
				printf("ERROR: No se ha inicializado el repositorio.  Utilice 'ugit init'\n");
			}
		}
		/*END*/





		/*COMANDO PARA CREAR COMMITS*/
		else if(strcmp(argv[1],"commit")==0){

			//verificar primero si ugit está inicializado
			if(is_initialized(".ugit")){

				//verificar si se colocó el mensaje de commit
				if(argc==3){

					//verificar si existe la carpeta objects
					if(is_initialized(".ugit/objects")){


						






						write_on_file(".ugit/COMMIT_MSG",argv[2],"w");
						printf("Se ha creado un commit con el mensaje: '%s'\n",argv[2]);

					}
					//sino, tirar error
					else{
						printf("ERROR: No se encontro la carpeta '.ugit/objects'.");
					}

				}

				// si se colocaron más argumentos de los correctos, mostrar error
				else if(argc>3){

					printf("ERROR: ");
					for(int i=3;i<argc;i++){
						printf("'%s' ", argv[i]);
					}
					printf("no son argumentos validos. Uso: 'ugit commit [mensaje]'\n ");
				}

				//  si no se colocó el mensaje de commit, mostrar error
				else {
					printf("ERROR: No se especificó el mensaje del commit. Uso: 'ugit commit [mensaje]'\n");
				}		


			}
			//sino, mostrar mensaje de error
			else {
				printf("ERROR: No se ha inicializado el repositorio.  Utilice 'ugit init'\n");
			}
		}
		/*END*/




      
		// EN EL CASO DE COLOCAR UN COMANDO NO VALIDO
		else{ 
			
			printf("Comando invalido\n'ugit help' para ver la lista de comandos disponibles\n");
			
		}


    }
	
	//EN EL CASO DE QUE UGIT SEA EJECUTADO SIN NINGUN ARGUMENTO
    else { 

		printf("No ingreso ningun comando'\n'ugit help' para ver la lista de comandos disponibles\n");		
    }

  return 0;
}

