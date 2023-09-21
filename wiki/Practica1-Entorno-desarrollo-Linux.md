# Práctica 1: Entorno de desarrollo bajo Linux #

En esta primera práctica se introduce el entorno de desarrollo de aplicaciones en C/C++ en un sistema operativo *Linux*, utilizando la herramienta *CMake* para la generación del ejecutable y empleando *BitBucket* como servicio de alojamiento para un sistema de control de versiones Git.

## Introducción a Linux ##

En primer lugar, se  revisarán las acciones típicas que un alumno debería realizar en una sesión de trabajo y que deberá conocer para el resto de prácticas. 

1. Recordatorio del porqué de la filosofía espartana de UNIX:

       El Terminal: tty, vt100, terminales-serie, hosts

       CLI: Command Line Interface, la shell 

2. Establecimiento de una conexión segura: 

     * Desde windows:

        * [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html)

        * [Tera Term](http://hp.vector.co.jp/authors/VA002416/teraterm.html)

        * [WinSCP](http://winscp.net/eng/docs/lang:es)

        * [Cygwin](http://www.cygwin.com/)

     * Desde Linux:
    
        * [OpenSSH](http://www.openssh.org/)

      * Desde el punto de vista del usuario:
 	
         * Antes: telnet y rlogin; ftp y rcp

         * Ahora: ssh; ftp (anónimo) y scp

      * [Comparativa de clientes](http://en.wikipedia.org/wiki/Comparison_of_SSH_clients)

      * [Comparativa de servidores](http://en.wikipedia.org/wiki/Comparison_of_SSH_servers)


3.   Herramientas de ayuda:

     * man

     * which

     * whereis

     * apropos

     * help (para mandatos internos del bash)


4.   Editores disponibles: vi, pico (nano), gedit

5.   Editores opcionales: emacs, [eclipse](https://eclipse.org/), [sublime](https://www.sublimetext.com/)

6.   Configuración por defecto de una sesión de trabajo interactiva: examen del contenido del fichero .bashrc.

7.   Navegación por la cuenta de usuario: ls, cd, pwd

8.   Gestión de ficheros y directorios: mkdir, cp, mv, rm

9.   Herramientas de compilación, gestión y depuración de código: 

      * gcc, g++

      * make y cmake

      * Depuradores: gdb, dbx 

      * strace 

10.   Clientes de correo: mailx, pine, thunderbird, evolution


En esta práctica también se proporciona un código C++ de una aplicación gráfica
utilizando las librerías OpenGL y GLUT. La aplicación es el juego del
tenis que funciona en modo local para dos jugadores, en el que utilizan
el mismo teclado y pantalla.


## Trabajo previo: CMake, git y bitbucket ##

El primer paso es hacer un "Fork" del repositorio creado para las
prácticas de la asignatura. Un “Fork” es una copia de un repositorio.
Permite trabajar independientemente en un repositorio sin afectar al
proyecto original.

Para ello, navega al repositorio original: [https://bitbucket.org/arodrifi/sii_c2324](https://bitbucket.org/arodrifi/sii_c2324)

y desde la interfaz web (icono +), selecciona la opción *Fork*. Aparecerá un formulario donde debes completar (se requiere autenticación en Bitbucket):

* El nombre del nuevo repositorio debe llamarse *sii-DDDDD* (siendo DDDDD el número de matrícula)

* El nivel de acceso debe ser *"público"*.

Tras esto, pulsa en *Fork repository*.

El siguiente paso es crear una copia en local para trabajar dentro del directorio de trabajo creado previamente (p. ej. cd matricula). Para ello se hace un "Clone" del repositorio creado:

```
$ git clone https://USUARIO_ACTUAL@bitbucket.org:USUARIO_PROPIETARIO/sii-DDDDD.git
```
o bien
```
$ git clone https://USUARIO_ACTUAL@bitbucket.org/USUARIO_PROPIETARIO/sii-DDDDD.git
```

donde USUARIO_ACTUAL es el usuario del alumno que clona el repositorio y USUARIO_PROPIETARIO es el dueño del repositorio (en el caso de las prácticas de los alumnos, se suele utilizar el mismo identificador para el USUARIO_ACTUAL y para el USUARIO_PROPIETARIO; se muestran dos opciones porque dependiendo de la versión se utiliza como delimitador el carácter ":" o el carácter "/").

Una vez hecho esto, hay que utilizar la herramienta CMake (Cross Platform Make) para generar el ejecutable. Se ofrece dentro del código una versión básica del fichero CMakeLists.txt. Este fichero contiene los mandatos que se van a ejecutar una vez que se modifica el código y hay que regenerar el ejecutable. Suponiendo que el código fuente se encuentra en matricula/workspace/src, se crea el directorio matricula/workspace/build, se accede a él y se ejecuta:

```
$ cmake ..
```

para generar los ficheros Makefile en el árbol de directorios que permitan mantener actualizado el código con la herramienta make. Finalmente, para generar el ejecutable hay que ejecutar el mandato make en el directorio de trabajo matricula/workspace/build.

El alumno puede realizar los cambios propuestos tomando como referencia el Capítulo 1 del tutorial recomendado para la herramienta CMake además del material de apoyo disponible en el moodle de la asignatura.

## EJERCICIO INDIVIDUAL ##

El objetivo de este ejercicio es familiarizarse con las herramientas de desarrollo en Linux antes de empezar a modificar el código fuente facilitado para la realización de las prácticas. Para ello, los alumnos deben modificar las cabeceras de los ficheros fuente incorporando alguna etiqueta que les identifique como autores de ese código.

Los alumnos deben añadir un **fichero Changelog** donde indique un texto descriptivo de los cambios realizados en el código antes de completar cada commit. 

A continuación se enumeran algunos de los mandatos del git que se deben utilizar en esta práctica y que serán fundamentales para la correcta realización del resto de las prácticas. Recuerde que debe consultar el tutorial de git propuesto en el apartado de Referencias adicionales. La ayuda online de git se obtiene con la invocación de $ git help 
Al final de la práctica los alumnos deberán ser capaces de editar ficheros en Linux, de interaccionar con soltura con el intérprete de mandatos y de compilar código fuente con CMake así como de gestionar correctamente el control de versiones del código fuente.

El alumno debe familiarizarse con las opciones "status" y "log":

```
$ git status
$ git log  
```

Los alumnos deben marcar localmente los ficheros cambiados mediante

```
$ git add fichero1 fichero2 directorio1
```

para añadirlos al siguiente commit. Una vez se hayan marcado los cambios, se realiza el "commit" local indicando un mensaje explicativo:

```
$ git commit -m 'Mensaje del commit'
```

A continuación, se debe subir el código al repositorio remoto:

```
$ git push origin master
```

Los alumnos deben actualizar su repositorio local con el último "commit" mediante el mandato "pull" (en este caso no debería haber conflictos):

```
$ git pull
```

Existen mandatos adicionales para:

* Deshacer los cambios de un fichero modificado:
```
$ git checkout fichero1
```
* Crear una rama:
```
$ git branch nombre_rama
```
* Cambiar a una determinada rama:
```
$ git checkout nombre_rama
```

Por último, los alumnos deben crear una etiqueta (tag) para indicar el nuevo número de versión y enviarla al servidor remoto. Se pueden comprobar las etiquetas existentes:
```
$ git tag
```
A continuación, mediante los siguientes mandatos, se sube al repositorio la versión con etiqueta 1.1:

```
$ git tag -a v1.1 -m 'Curso 2023/24 Mensaje version 1.1'
$ git push origin v1.1 
```

Las distintas etiquetas servirán para distinguir el trabajo realizado en cada una de las cinco prácticas. Al final de esta práctica, se debe haber creado una etiqueta en el repositorio con el mensaje 'Fin de la práctica 1' para marcar el hito.

Los archivos que no quieren controlarse pueden ignorarse editando el fichero *.git/info/exclude*

Recordar que se puede utilizar la interfaz gráfica de git y gitk si están instaladas en el equipo de trabajo: gitk o git-gui 

*Los alumnos deben subir todo el código a Bitbucket para ser evaluados por los profesores al comienzo de la práctica 2.*

## Referencias adicionales ##

* [Tutorial de CMake](https://www.johnlamp.net/?p=8)
* [Material de apoyo para CMake en el moodle de la asignatura](https://moodle.upm.es/titulaciones/oficiales/mod/resource/view.php?id=369429)
* [Tutorial de git](https://git-scm.com/docs/gittutorial)
* [Material de apoyo para herramientas de control de versiones en el moodle de la asignatura](https://moodle.upm.es/titulaciones/oficiales/mod/resource/view.php?id=369428)
* [Referencia sobre svn](http://svnbook.red-bean.com/index.es.html)
* [Changelog: Qué es y cómo escribir un buen changelog](https://keepachangelog.com/en/0.3.0/)
