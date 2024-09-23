<h1><p align="center">  μGit  </p></h1>
<b><p align="center">Sistema de control de archivos local para GNU/Linux</p></b>
<p align="center">Proyecto para el curso de Estructura de Datos 2024</p>

## Funciones
* Gestionar versiones de archivos
* Acceder a versiones anteriores
* Historial de versiones

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
  > Comando borra archivos que no son parte del commit! Guardar antes archivos importantes que esten en el directorio
- `set.name [nombre]`: Para establecer un nombre de usuario

## Notas
- μGit NO funciona correctamente con carpetas, solo con archivos que estén en el mismo directorio


## Autores
Iván Mansilla y Ayrton Morrison.

