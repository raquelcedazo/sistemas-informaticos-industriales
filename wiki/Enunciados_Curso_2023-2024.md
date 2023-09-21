# Bienvenido al Wiki de las prácticas de Sistemas Informáticos Industriales (Curso 2023-2024)#

Aquí encontrarás los guiones y el código correspondiente a cada una de
las prácticas.

[comment]: #  (La versión de la Ubuntu instalada en el *laboratorio de Informática* es la 22.04, que se puede descargar de aquí <http://www.ubuntu.com/download/desktop>. Necesitarás tener los siguientes paquetes instalados: g++, git, freeglut3-dev, cmake (en algunos casos ha dado un fallo de OpenGL y se ha resuelto instalando los paquetes mesa-common-dev y libglu1-mesa-dev). Opcionalmente, gitk y cmake-gui. )

La versión de la Ubuntu disponible actualmente es
la 22.04, que se puede descargar de aquí <http://www.ubuntu.com/download/desktop>.

Necesitarás tener los siguientes paquetes instalados: g++, git, freeglut3-dev, cmake (en algunos casos ha dado un fallo de OpenGL y se ha resuelto instalando los paquetes mesa-common-dev y libglu1-mesa-dev). Opcionalmente, gitk y cmake-gui. 

**Requisito:** Para la realización de las prácticas se requiere tener una
cuenta de usuario en **Bitbucket**, donde se vea claramente el nombre y
apellidos del alumno.

**Muy importante**: El repositorio de prácticas del alumno debe permanecer
**público y accesible durante todo el semestre** para que los profesores
evalúen su trabajo.


## Normas básicas para trabajar en el laboratorio ##

Debido a que el ordenador del laboratorio se utiliza por todos los
alumnos de la asignatura, es necesario tener cuidado con los archivos de
prácticas y hacer un uso adecuado.

 * El primer paso debe ser crear un directorio personal de trabajo
    durante tu sesión (por ejemplo, con tu número de matrícula o nombre): 

```
$ mkdir matrícula
$ cd matrícula
```

* Debes establecer la identidad para trabajar con Bitbucket:

```
$ git config --global user.name "USUARIO"
$ git config –-global user.email "EMAIL_BITBUCKET"
```

 * Cuando termines tu sesión, acuérdate de borrar tu directorio de trabajo y la identidad de Bitbucket (archivo /home/sii/.gitconfig) tras haber salvaguardado tu trabajo en el repositorio:

```
$ cd
$ rm -rf matrícula
$ rm /home/sii/.gitconfig
```

## Listado de prácticas ##

  * [Práctica 1 - Entorno de desarrollo bajo Linux](https://bitbucket.org/arodrifi/sii_c2324/wiki/Practica1-Entorno-desarrollo-Linux)
  * [Práctica 2 - Código inicial](https://bitbucket.org/arodrifi/sii_c2324/wiki/Practica2-Codigo-inicial)
  * [Práctica 3 - Comunicación interprocesos](https://bitbucket.org/arodrifi/sii_c2324/wiki/Practica3-Comunicacion-interprocesos)
* [Práctica 4 - Concurrencia](https://bitbucket.org/arodrifi/sii_c2324/wiki/Practica4-Concurrencia)
* [Práctica 5 - Comunicación con sockets](https://bitbucket.org/arodrifi/sii_c2324/wiki/Practica5-Comunicacion-sockets)
[comment]: #  (Ejemplo de comentario: * [Práctica 5 - Comunicación con sockets](https://bitbucket.org/arodrifi/sii_c2324/wiki/Practica5-Comunicacion-sockets) )
