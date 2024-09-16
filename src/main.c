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
#include <time.h>
#include "archivos.h"
#include "busqueda.h"
#define TABLE_SIZE 100
#define COLITION_SIZE 10



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
		if(!strcmp(argv[1],"help")){ 
			printf("Comandos comunes de uGit:\n\n");
			printf("Para inicializar un area de trabajo\n   init       Crear un repositorio vacio\n\nTrabajar y realizar cambios actuales\n   add        Agregar contenido de archivos\n   rm         Borrar archivos del arbol de trabajo\n\nModificar el historial comun\n   branch     Listar, crear o borrar ramas\n   commit     Grabar los cambios del repositorio\n   switch     Cambiar el nodo/branch\n\nPara colaborar\n   pull       Realiza una descarga de objetos y referencias de otro repositorio y lo integra al actual o al de la rama actual\n   push       Actualizar las referencias remotas con sus objetos asociados\n\n");
      	}	 	
		


      /*COMANDO PARA INICIALIZAR REPOSITORIO*/
		else if(!strcmp(argv[1],"init")){
			
			// EN EL CASO DE ESTAR INICIALIZADO AVISAR QUE YA LO ESTA
			if(is_initialized(".ugit")){
				printf("uGit ya se encuentra inicializado en el directorio\n");
			}

			// INICIALIZAR EL REPOSITORIO
          	else{ 

				system("mkdir .ugit .ugit/commits .ugit/objects .ugit/index");
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
		/*END*/





		/*COMANDO PARA AGREGAR ARCHIVOS AL REPOSITORIO*/
		else if(!strcmp(argv[1],"add")){

			if(is_initialized(".ugit")){ //verificar primero si se hizo ugit init

				if(argc>2){ // verificar si se colocaron más argumentos

					for(int i=2;i<argc;i++){ // recorrer los argumentos puestos
						if(is_initialized(argv[i])){ // verificar si el archivo existe

							char file_add_directory[1024]; //  crear un string para el path del archivo
							snprintf(file_add_directory,sizeof(file_add_directory),".ugit/index/%d",jenkins_hash(argv[i]));

							// copiar archivo en carpeta index (staging area) y le pone de nombre hash de su titulo
							copy_and_paste(argv[i],file_add_directory);

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




		/*COMANDO PARA ELIMINAR ARCHIVOS DEL STAGING AREA*/
		else if(!strcmp(argv[1],"rm")){

			if(is_initialized(".ugit")){ //verificar primero si se hizo ugit init

				if(argc>2){ // verificar si se colocaron más argumentos

					char file_rm_directory[1024]; //  crear un string para el path del archivo

					for(int i=2;i<argc;i++){ // recorrer los argumentos puestos

						snprintf(file_rm_directory,sizeof(file_rm_directory),".ugit/index/%d",jenkins_hash(argv[i]));
						if(is_initialized(file_rm_directory)){ // verificar si el archivo existe

							snprintf(file_rm_directory,sizeof(file_rm_directory),"rm .ugit/index/%d",jenkins_hash(argv[i]));
							if(!system(file_rm_directory)){ // eliminar archivo del staging area
								printf("'%s' se ha eliminado con exito del staging area", argv[i]);
							}
							else {
								printf("ERROR: '%s' no pudo ser eliminado del staging area", argv[i]);
							}
						}

						else{ // sino, mostrar mensaje de error
							printf("ERROR: El archivo '%s' no ha sido agregado todavia\n",argv[i]);
						}
					}

				}
				else{ // sino, mostrar mensaje de error
					printf("ERROR: No se especifico el(los) archivo(s) a eliminar. Uso: 'ugit rm [archivo1] [archivo2]...'\n");
				}

			} // si no está inicializado,  mostrar mensaje de error
			else{
				printf("ERROR: No se ha inicializado el repositorio.  Utilice 'ugit init'\n");
			}
		}
		/*END*/





		/*COMANDO PARA CREAR COMMITS*/
		else if(!strcmp(argv[1],"commit")){

			//verificar primero si ugit está inicializado
			if(is_initialized(".ugit")){

				//verificar si se colocó el mensaje de commit
				if(argc==3){

					//verificar si existe la carpeta objects, commits e index
					if(is_initialized(".ugit/objects")&&is_initialized(".ugit/index")&&is_initialized(".ugit/commits")){

						// verifica si hay archivos en el staging area
						if(!is_folder_empty(".ugit/index")){


							//crear hash del commit con el tiempo de la máquina
							time_t user_time=time(NULL);
							char *user_time_str=ctime(&user_time);

							char command[1024];

							int commit_hash=jenkins_hash(user_time_str);

							sprintf(command, "touch .ugit/commits/%d",commit_hash);

							// crear archivo del commit (donde irán los hash de sus archivos correspondientes)
							if(system(command)){
								printf("ERROR: no se pudo crear el commit\n");
								exit(1);
							}



							//lectura y conversión de los archivos del staging area a hash
							int i=0;
							char *file_names[TABLE_SIZE];

							sprintf(command, "ls -A .ugit/index");

							FILE *f=popen(command, "r");
    						if (!f) {
        						perror("ERROR: no se pudo crear el commit");
        						exit(1);
  							}

							// obtener los nombres de los archivos en la carpeta index
							while(i<TABLE_SIZE){
								file_names[i]=malloc(NAME_MAX);
								if(fscanf(f, "%s", file_names[i])==EOF){
									break;
								}
								i++;
							}
							pclose(f);



							// agregar los hash de los archivos al commit
							    sprintf(command,".ugit/commits/prueba",commit_hash);
								printf("%s", command);
								char auxhash[MAX_CHAR];
								
								for(int j=0;j<i;j++){
									sprintf(auxhash,"%d",hashFile(file_names[j]));

									write_on_file(command,auxhash,"w");
								}

							



							






						//write_on_file(".ugit/COMMIT_MSG",argv[2],"w");
						//printf("Se ha creado un commit con el mensaje: '%s'\n",argv[2]);



						}
						// sino, avisa que no se ha hecho add
						else {
							printf("ERROR: no se han agregado archivos al staging area. Utilice 'ugit add [archivo1] [archivo2]...'\n");
						}

					}
					//sino, tirar error
					else{
						printf("ERROR: No se encontraron los archivos necesarios para que uGit funcione");
					}

				}

				// si se colocaron más argumentos de los correctos, mostrar error
				else if(argc>3){

					printf("ERROR: ");
					for(int i=3;i<argc;i++){
						printf("'%s' ", argv[i]);
					}
					printf("no son argumentos validos. Uso: 'ugit commit '[mensaje]' '\n ");
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

