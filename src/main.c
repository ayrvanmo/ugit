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
				system("touch .ugit/log .ugit/userinfo .ugit/index");
				

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
							snprintf(file_add_directory,sizeof(file_add_directory),".ugit/index/%s",argv[i]);

							// copiar archivo en carpeta index (staging area)
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

						snprintf(file_rm_directory ,sizeof(file_rm_directory),".ugit/index/%s",argv[i]);
						if(is_initialized(file_rm_directory)){ // verificar si el archivo existe

							snprintf(file_rm_directory,sizeof(file_rm_directory),"rm .ugit/index/%s",argv[i]);
							if(!system(file_rm_directory)){ // eliminar archivo del staging area
								printf("'%s' se ha eliminado con exito del staging area\n", argv[i]);
							}
							else {
								printf("ERROR: '%s' no pudo ser eliminado del staging area\n", argv[i]);
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
					if(is_initialized(".ugit/objects")&&is_initialized(".ugit/index")&&is_initialized(".ugit/commits"))
					{

						// verifica si hay archivos en el staging area
						if(!is_folder_empty(".ugit/index"))
						{


							//crear hash del commit con el tiempo de la máquina
							time_t user_time=time(NULL);
							char *user_time_str=ctime(&user_time);
							int commit_hash=jenkins_hash(user_time_str);

							char command[1024];
							sprintf(command, "touch .ugit/commits/%u",commit_hash);

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
							while(i<TABLE_SIZE * COLITION_SIZE){
								file_names[i]=malloc(NAME_MAX);
								if(fscanf(f, "%s", file_names[i])==EOF){
									break;
								}
								i++;
							}
							pclose(f);


							//CAMBIAR ESTO DESPUES
							// agregar los hash de los archivos al commit
							sprintf(command,".ugit/commits/%u",commit_hash); //QUE HACE ESTA VARIABLE???

							char auxchar[100];							

							FILE *archivo =fopen(command, "a");

							for(int j=0;j<i;j++){

									sprintf(auxchar,".ugit/index/%s",file_names[j]);
									fprintf(archivo, "%s %u\n", file_names[j], hashFile(auxchar));

							}

							fclose(archivo);

							// mover los archivos a carpeta objects
							for(int j=0;j<i;j++){
									sprintf(auxchar,".ugit/index/%s",file_names[j]);
									sprintf(command,"cp .ugit/index/%s .ugit/objects/%u", file_names[j], hashFile(auxchar));

									system(command);

									sprintf(command,"rm .ugit/index/%s", file_names[j]);
									system(command);
								}

							

							// registrar commit en el log
							FILE *log_file=fopen(".ugit/log","a");
							fprintf(log_file,"\033[36m %s\033[0m\n '%s' | HASH: %u\n\n",user_time_str, argv[2],  commit_hash);
							fclose(log_file);


							printf("Se ha creado un commit con el mensaje: '%s'\n",argv[2]);

						}
						// sino, avisa que no se ha hecho add
						else 
						{
							printf("ERROR: no se han agregado archivos al staging area. Utilice 'ugit add [archivo1] [archivo2]...'\n");
						}

					}
					//sino, tirar error
					else{
						printf("ERROR: No se encontraron los archivos necesarios para que uGit funcione\n");
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





		/*REVISAR EL HISTORIAL DE COMMITS*/
		else if(!strcmp(argv[1],"log")){

			if(is_initialized(".ugit")){ 

				if(argc<3){

					if(is_initialized(".ugit/log")){

						system("cat .ugit/log");

					}
					else {
						printf("ERROR: No se pudo encontrar el historial de commits");
					}
				}
				else {
					printf("ERROR: comando invalido. Uso: 'ugit log'\n");
				}

			}
			else{
				printf("ERROR: No se ha inicializado el repositorio. Utilice 'ugit init'\n");
			}

		}
		/*END*/




		/*COMANDO PARA VOLVER A VERSIONES ANTERIORES*/
			else if(!strcmp(argv[1],"checkout")){

				if(is_initialized(".ugit")){

					//verificar si se han hecho commits
					if(!is_folder_empty(".ugit/commits")){

						//verificar que se colocó la cantidad de argumentos adecuada
						if(argc==3){

							char command[100];
							char *file_names[TABLE_SIZE];
							int i=0;
							sprintf(command,".ugit/commits/%s",argv[2]);

							//verificar si el commit existe
							if(is_initialized(command)){


								
								//leer el commit
								FILE *commit_file=fopen(command,"r");
								for(int i=0;i<TABLE_SIZE * COLITION_SIZE;i++){
									int file_hash;
									char *file_name[NAME_MAX];
									fscanf(commit_file,"%s %u\n",file_name,&file_hash);

									//mover los archivos a la carpeta principal
									sprintf(command,"cp .ugit/objects/%u ./%s",file_hash,file_name);
									system(command);			
								}

								//leer archivos en la carpeta principal
								 FILE *f = popen("ls -A", "r");
        						if (!f) {
            						perror("ERROR: no se pudieron listar los archivos");
            						exit(1);
        							}

        						i = 0;
        						while (i < TABLE_SIZE * COLITION_SIZE) {
            						file_names[i] = malloc(NAME_MAX);

            						if (fscanf(f, "%s", file_names[i]) == EOF) {
                						free(file_names[i]); // Liberar memoria si no se usará
                						break;
            						}

            					i++;
        						}
								
        						
				

								 // Eliminar archivos que no están incluidos en el commit
        						for (int j = 0; j < i; j++) {

									int encontrado = 0;
									char commit_file_name[NAME_MAX];
									int file_hash;

									while (fscanf(commit_file, "%s %u\n", commit_file_name, &file_hash) != EOF) {

										if (strcmp(commit_file_name, file_names[j]) == 0) {
											encontrado = 1;  // El archivo está incluido en el commit
											break;
											}
											
											else {
												if ((file_names[j], ".ugit") && strcmp(file_names[j], ".") && strcmp(file_names[j], "..") && strcmp(file_names[j], "ugit")) {
                									sprintf(command, "rm %s", file_names[j]);
                									system(command);
            									}
											}

										}

            						
            						

        						}
								fclose(commit_file);
								pclose(f);
								
								


							}
							//tirar error
							else {
								printf("ERROR: El commit '%s' no existe. Utilice 'ugit log' para ver el historial de commits\n",argv[2]);
							}

						} //sino, tirar mensaje de error.
						else {
							printf("ERROR:  comando invalido. Uso: 'ugit checkout [commit_hash]'. Utilice 'ugit log' para  ver el historial de commits\n");
						}

					} //sino, tirar mensaje de error
					else{
						printf("ERROR: No hay commits para acceder. Utilice 'ugit add' y 'ugit commit'\n");
					}
				}
				else {
					printf("ERROR:  No se ha inicializado el repositorio. Utilice 'ugit init'\n");
				}
			}




      
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

