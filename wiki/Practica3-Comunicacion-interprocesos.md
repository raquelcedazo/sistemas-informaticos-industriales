Antes de comenzar con el desarrollo de la práctica 3 debes haber creado una etiqueta en el repositorio con el mensaje 'Fin de la práctica 2' para marcar el hito.

A continuación, para la realización de la práctica 3, crea una rama y salta a dicha rama:

```
$ git branch practica3
$ git checkout practica3
```

# COMUNICACIÓN INTERPROCESO #

Este ejercicio pretende poner en práctica dos mecanismos de comunicación vistos en la teoría:

* Las tuberías con nombre (FIFO).
* Proyección de ficheros en memoria.

Para ello se propone desarrollar dos programas:

1. Programa **logger** (clase logger.cpp) que reciba del juego tenis una cadena de texto cada vez que alguno de los dos jugadores anota un punto. La comunicación entre el logger y el tenis se debe realizar mediante una tubería con nombre.

1. Programa **bot** (clase bot.cpp) que se encargue de controlar la raqueta1 de forma automática. La comunicación entre el **bot** y el **tenis** se debe realizar mediante el mecanismo de comunicación de ficheros proyectados en memoria.

Al finalizar la práctica se tendrán tres procesos ejecutando en nuestro equipo con el esquema siguiente:

![1030911270-esquema.png](https://bitbucket.org/repo/6L8Rg8/images/1167735620-1030911270-esquema.png)

Recuerda que hay que modificar el CMakeLists.txt para añadir los nuevos programas (mediante ADD_EXECUTABLE) y subir la nueva rama al repositorio:

```
$ git push origin practica3
```

## Descripción del programa logger ##

Se pide implementar un programa **logger** y los cambios necesarios en el código de la práctica 2 para que desde el juego se envíe al **logger** el nombre y el número de puntos que lleva un jugador en el momento que termina un tanto. Para ello hay que seguir los siguientes pasos:

1. El programa **logger** es el encargado de crear la tubería (*mkfifo*), abrirla en modo lectura (*open*) y destruirla (*close* y *unlink*). Por tanto, el **logger** debe ser ejecutado antes que el **tenis**.

1. El **logger** entra en un bucle infinito de recepción de datos (*read*) e imprime el mensaje por salida estándar.
    
1. Añadir el identificador de la tubería como atributo de la clase Mundo definida en el programa **tenis**.
    
1. Abrir la tubería (*open*) en modo escritura en el Init() de Mundo.
    
1. Enviar los datos cuando se produzcan puntos por la tubería (*write*). Esto se debe hacer en el OnTimer() de Mundo.
    
1. Cerrar la tubería adecuadamente (*close* en el destructor de Mundo).

Un ejemplo de traza de ejecución del logger podría ser:

```
Jugador 1 marca 1 punto, lleva un total de 1 puntos.
Jugador 2 marca 1 punto, lleva un total de 1 puntos.
Jugador 2 marca 1 punto, lleva un total de 2 puntos.
```

## Descripción del programa bot ##

Se pide implementar un programa **bot** que, por medio del mecanismo de ficheros proyectados en memoria, intercambie la información necesaria con el juego tenis para que sea el **bot** el que controle la raqueta1.

La información a compartir se compone de: la raqueta1 y la pelota para conocer la posición de ambas; y una acción que es la que debe decidir el **bot** en función de una lógica a desarrollar: arriba, abajo, o nada. Para ello se debe crear el fichero **DatosMemCompartida.h** (dentro del directorio **include**) con la definición de la siguiente estructura:

```
#pragma once 
#include "Esfera.h"
#include "Raqueta.h"
class DatosMemCompartida
{       
public:         
      Esfera esfera;
      Raqueta raqueta1;
      int accion; //1 arriba, 0 nada, -1 abajo
};
```

Y, por otra parte, el **tenis** debe modificarse según lo siguiente:

* Añadir un atributo del tipo DatosMemCompartida en Mundo.h.
* Añadir un atributo del tipo puntero a DatosMemCompartida en Mundo.h.
* En el método OnTimer() de Mundo, actualizar los campos del atributo DatosMemCompartida e invocar al método OnKeyboardDown según el valor de la acción correspondiente.
* En el método Init() de Mundo 

      1. Crear un fichero del tamaño del atributo DatosMemCompartida (*open* y *write*) 
      2. Proyectar el fichero en memoria (*mmap*). 
      3. Cerrar el descriptor de fichero. 
      4. Asignar la dirección de comienzo de la región creada al atributo de tipo puntero creado en el paso 2.

A continuación se recapitulan los pasos a seguir para el desarrollo del **bot**:

1. Declarar una variable de tipo puntero a DatosMemCompartida.
1. Abrir el fichero proyectado en memoria creado anteriormente en el **tenis** (*open*) y proyectarlo en memoria (*mmap*).
1. Cerrar el descriptor de fichero.
1. Asignar la dirección de comienzo de la región creada al atributo de tipo puntero creado en el paso 2.
1. El **bot** entra en un bucle infinito incluyendo una llamada a *usleep*(25000) para que se suspenda durante 25 ms y en cada iteración hay que añadir la lógica necesaria para que el **bot**, en función de las coordenadas Y de la Esfera y la Raqueta, establezca la acción a realizar.

# EJERCICIO PROPUESTO #

Se pide desarrollar al menos una de las siguientes funcionalidades a elegir por el alumno:

* Completar el juego para que finalice cuando uno de los jugadores alcance los 3 puntos.
* Hacer que el **bot** también pueda controlar la raqueta2 si detecta que durante 10 segundos no ha pulsado ninguna tecla.

Una vez desarrollado el ejercicio propuesto, haz un merge de la rama practica3 con la rama master:

```
$ git checkout master
$ git merge practica3
$ git push origin master 
```

Para finalizar el ejercicio individual, crea una etiqueta con el texto: 'Fin de la práctica 3'.