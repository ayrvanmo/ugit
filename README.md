<h1><p align="center">  μGit  </p></h1>
<b><p align="center">Sistema de control de versiones local para GNU/Linux</p></b>
<p align="center">Proyecto para el curso de Estructura de Datos 2024</p>
<p align="center"><a href="https://ayrvanmo.github.io/ugit/html/">Documentación</a></p>

## Funciones
* Gestionar versiones de archivos
* Acceder a versiones anteriores
* Historial de versiones
  
## Instalación
1. Clone el repositorio
2. Abra un terminal en la carpeta del repositorio, y ejecute `make`. Se creará la carpeta `build`, el cual contiene el ejecutable `ugit`
3. Mueva el ejecutable `ugit` al directorio en donde quiera realizar el control de versiones y ejecute en el terminal `.\ugit init`
4. Si se creó en el directorio la carpeta `.ugit`, ugit fue exitosamente instalado en la carpeta


## Comandos
Todos los comandos deben ejecutarse en el terminal con el sintax `./ugit [comando] [argumento]`
- `help`: Para ver el listado de comandos
- `init`: Para inicializar el repositorio
- `add [archivo1] [archivo2] ...`: Para agregar archivos en el *staging area*
  - `add .`: Agrega todos los archivos en el directorio
- `rm [archivo1] [archivo2] ...`: Para eliminar archivos del *staging area*
- `commit [mensaje]`: Para crear un commit
- `log`: Para ver el historial de commits
- `checkout [commit_hash]`: Para cambiar entre versiones
    > Comando borra archivos que no son parte del commit! Guardar antes archivos importantes que esten en el directorio
- `status`: Para revisar el stagging area
- `set.name [nombre]`: Para establecer un nombre de usuario

## Notas
- μGit NO funciona correctamente con carpetas, solo con archivos que estén en el mismo directorio


## Créditos
Iván Mansilla y Ayrton Morrison.

