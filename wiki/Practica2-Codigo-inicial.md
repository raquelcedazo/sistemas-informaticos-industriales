# Práctica 2: Código inicial #

Antes de comenzar con el desarrollo de la práctica 2 debes haber creado una etiqueta en el repositorio con el mensaje 'Fin de la práctica 1' para marcar el hito.

A continuación, para la realización de la práctica 2, crea una rama y salta a dicha rama:

```
$ git branch practica2
$ git checkout practica2
```

## Objetivo ##

El principal objetivo es familiarizarse por completo con las herramientas de desarrollo y programar la funcionalidad básica para las tres siguientes prácticas.

Lo primero que hay que hacer es añadir movimiento tanto a la pelota como a las raquetas. Para ello, se pide añadir el código necesario para mover la pelota (Esfera.cpp) y mover las raquetas (Raqueta.cpp). Después de completar esto, súbelo a tu repositorio local mediante un commit y al repositorio de Bitbucket mediante:

```
$ git push origin practica2
```

Después de esto, visualizad a través de la interfaz web de Bitbucket las ramas que hay activas. Para ello, pincha en el menú de "Branches" en Bitbucket. 

A través de la línea de comandos también existe la posibilidad de ver cuántas ramas hay en el repositorio y en qué rama se está trabajando (marcada en verde y con asterisco). Para ello, ejecuta:

```
$ git branch
```

# EJERCICIO INDIVIDUAL PROPUESTO #

Se pide completar el juego con alguna funcionalidad extra de las siguientes propuestas:

* Las raquetas deben ser capaces de disparar y reducir el tamaño de la raqueta oponente en el momento del impacto, o inmovilizarla unos segundos.
* La pelota debe disminuir el tamaño según avanza el juego.
* Duplicar el número de pelotas según avanza el juego.

Se pide modificar el **archivo Changelog** indicando las funcionalidades desarrolladas y un **fichero README** para indicar las instrucciones para probar el juego.

El alumno debe subir todo el código a Bitbucket para ser evaluado por el profesor al comienzo de la práctica 3.  Al final de esta práctica, debes haber creado una etiqueta en el repositorio con el mensaje 'Fin de la práctica 2' para marcar el hito.

Por último, mezcla tu rama creada practica 2 con la rama master. Para ello, el alumno debe cambiar a la rama master y ejecutar lo siguiente:

```
$ git merge practica2
```

Y haz un push para que se hagan los cambios en el repositorio de Bitbucket.