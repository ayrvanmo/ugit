/**
 * @file main.c
 * @author Mansilla-Morrison
 * @brief Código principal del programa
 * @version 1.5
 * 
 * 
 */

#include <time.h>
#include "archivos.h"
#include "busqueda.h"



/**
 * 
 * @brief  Función principal del programa
 * 
 * Punto de inicio del programa,  donde se ejecutan las diferentes funciones
 * @param argc Número de argumentos ingresados en el terminal
 * @param argv Argumentos ingresados en el terminal
 * 
 * @note Esta función requiere de argumentos ingresados, por lo que es importante ejecutarla desde el terminal
 * 
 */

int main(int argc, char** argv){


	/* EN EL CASO DE QUE SE INGRESE UN COMANDO*/
    if(argc>1){ 

		// COMANDO PARA MOSTRAR LOS COMANDOS DISPONIBLES
		if(!strcmp(argv[1],"help")){ 
			printf("Comandos comunes de uGit:\n\n");
			printf("Para inicializar un area de trabajo\n   init       Crear un repositorio vacio\n\nTrabajar y realizar cambios actuales\n   add        Agregar contenido al staging area\n   rm         Borrar archivos del staging area\n\nHistorial comun\n   commit     Grabar los cambios del repositorio\n   log         Ver historial de commits   checkout    Volver a commit anterior\n\n\nPara colaborar\n   pull       Realiza una descarga de objetos y referencias de otro repositorio y lo integra al actual o al de la rama actual\n   push       Actualizar las referencias remotas con sus objetos asociados\n\n");
      	}	 	
		


      /*>COMANDO PARA INICIALIZAR REPOSITORIO*/
		else if(!strcmp(argv[1],"init")){
			
			// EN EL CASO DE ESTAR INICIALIZADO AVISAR QUE YA LO ESTA
			if(is_initialized(".ugit")){
				printf("uGit ya se encuentra inicializado en el directorio\n");
			}

			// INICIALIZAR EL REPOSITORIO
          	else{ 

				system("mkdir .ugit .ugit/commits .ugit/objects .ugit/index");
				system("touch .ugit/log .ugit/userinfo .ugit/index .ugit/commits/commits_table");
				

				// Si la inicialización es exitosa
				if(is_initialized(".ugit")){
					// inicializar tabla hash de los commits
					HashTable commits_table;
					init_table(&commits_table);
					print_tablefile(&commits_table,".ugit/commits/commits_table");
					printf("Repositorio inicializado exitosamente\n");
				}
				// Si no se pudo inicializar, tirar error
				else{
					printf("ERROR: No se pudo inicializar el repositorio\n");
				}
			}

        }
		/*END*/




		/*los siguientes comandos solo se podrán utilizar si ya se ha inicializado el repositorio*/
		if(is_initialized(".ugit")){


			/*ESTABLECER AUTOR DE LOS COMMITS*/
			if(!strcmp(argv[1], "set.name")){

				if(argc != 3){
					printf("ERROR: Uso 'ugit set.name [argumento]'");
				}
				else{

					FILE* userinfo;
					userinfo = fopen(".ugit/userinfo","w");
					fprintf(userinfo,"%s",argv[2]);
					fclose(userinfo);

					printf("Hola, %s!\n",argv[2]);
				}
			}
			/*END*/


			/*AGREGAR ARCHIVOS AL STAGING AREA*/
			if(!strcmp(argv[1],"add")){

				if(argc>2){ // verificar si se colocaron argumentos					
					for(int i=2;i<argc;i++){ // recorrer los argumentos puestos

						if(strcmp(argv[i], ".") == 0 ){ // En el caso de insertar "." se añadira todo el directorio

							DIR *dir;
							struct dirent *entry;
							dir = opendir(".");

							if (dir != NULL) { //si se pudo abrir el directorio
								while ((entry = readdir(dir)) != NULL) {
									if (!is_core_file(entry)) {
										char file_add_directory[1024];
										snprintf(file_add_directory, sizeof(file_add_directory), ".ugit/index/%s", entry->d_name);
										// copiar archivo en carpeta index (staging area)
										copy_and_paste(entry->d_name, file_add_directory);
									}
								}
								closedir(dir);
								} 
							else{
								perror("ERROR: No se pudo abrir el directorio 'build'");
							}
						}
						else if(is_initialized(argv[i])){ // Si no, verificar si el archivo existe
							char file_add_directory[1024]; //  crear un string para el path del archivo
							snprintf(file_add_directory,sizeof(file_add_directory),".ugit/index/%s",argv[i]);
							// copiar archivo en carpeta index (staging area)
							copy_and_paste(argv[i],file_add_directory);
						}
						else{ // Mostrar mensaje de error
							printf("ERROR: El archivo '%s' no existe\n",argv[i]);
						}
					}
					
				}
				else{ // Mostrar mensaje de error
					printf("ERROR: No se especifico el(los) archivo(s) a agregar. Uso: 'ugit add [archivo1] [archivo2]...'\n");
				}
			}
			/*END*/




			/*COMANDO PARA ELIMINAR ARCHIVOS DEL STAGING AREA*/
			else if(!strcmp(argv[1],"rm")){

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

			}
			/*END*/




			/*COMANDO PARA CREAR COMMITS*/
			else if(!strcmp(argv[1],"commit")){

				//verificar si se colocó el mensaje de commit
				if(argc==3){

					//verificar si existe la carpeta objects, commits e index
					if(is_initialized(".ugit/objects")&&is_initialized(".ugit/index")&&is_initialized(".ugit/commits")&&is_initialized(".ugit/commits/commits_table"))
					{

						// verifica si hay archivos en el staging area
						if(!is_folder_empty(".ugit/index")){

							//variable auxiliar para comandos dinámicos
							char command[1024];

							//crear hash del commit con el tiempo de la máquina
							time_t user_time=time(NULL);
							char *user_time_str=ctime(&user_time);
							unsigned int commit_hash=jenkins_hash(user_time_str);

							//leer tabla hash de commits
							HashTable commits_table;
							init_table(&commits_table);
							save_table(&commits_table,".ugit/commits/commits_table");
							int columns=0;

							//insertar el commit en la tabla hash
							insert_hash(&commits_table,user_time_str,(int)commit_hash, &columns);
							print_tablefile(&commits_table,".ugit/commits/commits_table");


							//crear archivo del commit en la carpeta commits
							sprintf(command, "touch .ugit/commits/%u%d",commit_hash, columns);
							if(system(command)){
								printf("ERROR: no se pudo crear el commit\n");
								exit(1);
							}


							//lectura y conversión de los archivos del staging area a la carpeta objects
							DIR *staging_area;
							staging_area=opendir(".ugit/index");
							struct dirent *file_for_commit;
							sprintf(command,".ugit/commits/%u%d",commit_hash, columns);

								// si se abre exitosamente la carpeta index
								if(staging_area){

									char auxchar[1024];
									FILE *commit_file=fopen(command,"a");

									while((file_for_commit=readdir(staging_area))!=NULL){

										if(!is_core_file(file_for_commit)){

											// colocar el nombre y hash del contenido del archivo en su commit
											sprintf(auxchar,".ugit/index/%s",file_for_commit->d_name);
											fprintf(commit_file,"%s %u\n",file_for_commit->d_name,hashFile(auxchar));

											//mover archivo de index a objects con su hash
											sprintf(command,"cp %s .ugit/objects/%u", auxchar, hashFile(auxchar));
											system(command);

											sprintf(command,"rm %s", auxchar);
											system(command);

										}

									}
									fclose(commit_file);
							

							

									// registrar commit en el log
									FILE *log_file=fopen(".ugit/log","a");

									fprintf(log_file,"\033[36m %s\033[0m\n '%s'\nHASH: %u%d\n",user_time_str, argv[2],  commit_hash, columns);

									// leer userinfo
									FILE* userinfo=fopen(".ugit/userinfo", "r");
									if(userinfo){
										char username[255];
										if(fscanf(userinfo,"%s",&username)!=EOF){
										fprintf(log_file,"Hecho por: %s\n\n",username);
										}
										else{
											fprintf(log_file,"\n");
										}
										fclose(userinfo);
									}
									else {
										fprintf(log_file,"\n");
									}

									fclose(log_file);


									//confirmacion
									printf("Se ha creado un commit con el mensaje: '%s'\n",argv[2]);
								}

								else{
									printf("ERROR: No se pudo leer '.ugit/index'");
									exit(1);
								}


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
			/*END*/


			/*REVISAR EL HISTORIAL DE COMMITS*/
			else if(!strcmp(argv[1],"log")){

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
			/*END*/



			/*COMANDO PARA VOLVER A VERSIONES ANTERIORES*/
			else if(!strcmp(argv[1],"checkout")){
					
					if(is_initialized(".ugit/commits")){

						//verificar que se colocó la cantidad de argumentos adecuada
						if(argc==3){

							char command[1024]; //variable auxiliar para comandos dinámicos

							//verificar si el commit ingresado existe
							sprintf(command,".ugit/commits/%s",argv[2]);
							if(is_initialized(command)){
								//borrar los archivos en la carpeta principal (excepto .ugit y ugit)
								DIR *root_directory;
								root_directory = opendir("."); //abrir carpeta donde ugit está siendo ejecutado
								struct dirent *directory_files;

        						if (root_directory) {
   									while ((directory_files = readdir(root_directory)) != NULL) {
        								// Excluir .ugit y ugit
        								if (!is_core_file(directory_files)) {
											sprintf(command,"rm %s",directory_files->d_name);
											system(command);
        								}
    								}				
    								closedir(root_directory);
								}
								free(directory_files);



							
								//leer el commit y mover los archivos correspondientes a este a la carpeta principal
								sprintf(command,".ugit/commits/%s",argv[2]);
								FILE *commit_file=fopen(command,"r");



								for(int n_files_commit=0;n_files_commit<TABLE_SIZE * COLITION_SIZE;n_files_commit++){
									long file_hash;
									char file_name[MAX_CHAR];

									if((fscanf(commit_file,"%s %ld",file_name,&file_hash))==EOF)
										break;
									
									//mover los archivos a la carpeta principal
									sprintf(command,"cp .ugit/objects/%ld %s",file_hash,file_name);
									system(command);			
								}

								fclose(commit_file);
															
							}
							//tirar error si el commit ingresado no existe
							else {
								printf("ERROR: El commit '%s' no existe o no se han hecho commits. Utilice 'ugit log' para ver el historial de commits\n",argv[2]);
							}

						} //sino, tirar mensaje de error.
						else {
							printf("ERROR:  comando invalido. Uso: 'ugit checkout [commit_hash]'. Utilice 'ugit log' para  ver el historial de commits\n");
						}

					} //sino, tirar mensaje de error
					else{
						printf("ERROR: No se pudo encontrar la carpeta commits\n");
					}
				}
				/*END*/

				else if(strcmp(argv[1],"help")!=0&&strcmp(argv[1],"init")!=0){
					printf("ERROR: Comando invalido. Utilice 'ugit help' para ver la lista de comandos");
				}
				
			
		} // si no está inicializado el repositorio
		else {
			//avisar que el comando no existe si es asi
			if(strcmp(argv[1],"add")!=0&&strcmp(argv[1],"rm")!=0&&strcmp(argv[1],"commit")!=0&&strcmp(argv[1],"log")!=0&&strcmp(argv[1],"checkout")!=0&&strcmp(argv[1],"set.name")!=0)
					printf("ERROR: Comando invalido. Utilice 'ugit help' para ver la lista de comandos");
			
			//sino, avisar que no se puede ejecutar ese comando
			else {
			printf("ERROR: No es un repositorio de git, ni un derivado de este.\nUtilice 'ugit init' para inicializar un repositorio\n");
			}
		}

	}
		//EN EL CASO DE QUE UGIT SEA EJECUTADO SIN NINGUN ARGUMENTO
    else  
		printf("No se ingreso ningun comando \n'ugit help' para ver la lista de comandos disponibles\n");		
    

  	return 0;
}

