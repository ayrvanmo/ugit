<h1><p align="center">  μGit  </p></h1>
<b><p align="center">Sistema de control de archivos local para GNU/Linux</p></b>
<p align="center">Proyecto para el curso de Estructura de Datos 2024</p>

## Funciones
* Gestionar versiones de archivos
* Acceder a versiones anteriores
* Historial de versiones

## Instalación
Descargue el ejecutable [ugit](https://github.com/ayrvanmo/ugit/blob/1534f1f90c6e9ae00cd754e5ac5581e2dd34072f/build/ugit) y muevalo al directorio donde va a realizar el control de versiones

Abra un terminal en el mismo directorio donde μGit se encuentra instalado y escriba el comando
`./ugit init`. Si se creó una carpeta llamada '.ugit', el programa fue inicializado exitosamente en el directorio

## Comandos
Todos los comandos deben ejecutarse con el sintax `./ugit [comando] [argumento]`
- `help`: Para ver el listado de comandos
- `init`: Para inicializar el repositorio
- `add [archivo1] [archivo2] ...`: Para agregar archivos en el *staging area*
  - `add .`: Agrega todos los archivos en el directorio
- `rm [archivo1] [archivo2] ...`: Para eliminar archivos del *staging area*
- `commit [mensaje]`: Para crear un commit
- `log`: Para ver el historial de commits
- `checkout [commit_hash]`: Para cambiar entre versiones
- `set.name [nombre]`: Para establecer un nombre de usuario

## Notas
- μGit NO funciona correctamente con carpetas, solo con archivos que estén en el mismo directorio


## Créditos
Iván Mansilla y Ayrton Morrison.

