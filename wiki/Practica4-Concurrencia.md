# Práctica 4 - Concurrencia #

Antes de comenzar con el desarrollo de la práctica 4, crea una etiqueta en el repositorio con el mensaje 'Fin de la práctica 3' para marcar el hito (si no lo habías hecho previamente).

A continuación, para la realización de la práctica 4, crea una rama y salta a dicha rama:

```
$ git branch practica4
$ git checkout practica4
```

## Objetivos ##

Esta práctica tiene tres objetivos:

1. Separar código del programa tenis en dos programas diferentes denominados **cliente** y **servidor**.
1. Comunicar **cliente** y **servidor** mediante tuberías con nombre (FIFO).
1. Utilizar hilos (threads) para la programación concurrente.

El esquema propuesto de los procesos para la realización de la práctica es el siguiente:

![1772254298-esquema-p3.png](https://bitbucket.org/repo/6L8Rg8/images/2027817144-1772254298-esquema-p3.png)

El **cliente** es el programa desde donde se controlan las teclas del juego, mientras que el **servidor** es el que recibe la tecla pulsada y dibuja los movimientos. El juego se retransmite al **cliente**, de modo que en ambas ventanas se visualiza lo mismo.

Para la realización de la práctica, se recomienda seguir los siguientes pasos:

## 1. Creación de los programas cliente y servidor ##

En primer lugar, hay que crear los ficheros fuente MundoCliente.cpp y MundoServidor.cpp, ambos copia de Mundo.cpp (se debe hacer lo mismo para los ficheros de cabecera MundoCliente.h y MundoServidor.h), y un servidor.cpp y un cliente.cpp, ambos copia de tenis.cpp. Por tanto, Mundo.cpp y tenis.cpp se eliminarán.

Una vez hecho esto, modifica el fichero CMakeLists.txt para generar los dos ejecutables **servidor** y **cliente**.

Hay que asegurarse de que el **logger** es el proceso que está comunicado con el **servidor**, mientras que el **bot** lo hace con el **cliente**.

## 2. Envío de las coordenadas del **servidor** al **cliente** ##

El envío de las coordenadas del servidor al **cliente** debe hacerse mediante una tubería con nombre (FIFO). Los datos que se necesitan enviar de **servidor** a **cliente** son:

* Coordenadas (x,y) de la pelota.
* Coordenadas (x1, y1, x2, y2) de la raqueta del jugador 1.
* Coordenadas (x1, y1, x2, y2) de la raqueta del jugador 2.

Estos datos deben ser enviados por el **servidor** cada vez que se produce un cambio en los mismos, es decir, en cada temporización del timer. Una solución sencilla es escribir (con *sprintf*()) una cadena de texto con todos los valores numéricos de los datos y enviar dicha cadena por la tubería. Ejemplo de uso de *sprintf*:

```
char cad[200];
sprintf(cad,"%f %f %f %f %f %f %f %f %f %f %d %d", esfera.centro.x,esfera.centro.y, jugador1.x1,jugador1.y1,jugador1.x2,jugador1.y2,jugador2.x1,jugador2.y1,jugador2.x2,jugador2.y2, puntos1, puntos2);
```

La recepción de los datos se puede realizar con el uso de *sscanf*:

```
sscanf(cad,"%f %f %f %f %f %f %f %f %f %f %d %d", &esfera.centro.x,&esfera.centro.y, &jugador1.x1,&jugador1.y1,&jugador1.x2,&jugador1.y2, &jugador2.x1,&jugador2.y1,&jugador2.x2,&jugador2.y2, &puntos1, &puntos2); 
```

Los pasos en el **cliente** son los siguientes:

1. Añadir el identificador de la tubería como atributo de la clase MundoCliente.
1. El **cliente** abre la tubería en modo lectura en el método Init (mediante *open*).
1. Leer los datos de la tubería (*read*) en el OnTimer().
1. Actualizar los atributos de MundoCliente con los datos recibidos (*sscanf*()).
1. Cerrar la tubería adecuadamente (*close* en el destructor de MundoServidor).

Los pasos en el **servidor** son los siguientes:

1. Añadir el identificador de la tubería como atributo de la clase MundoServidor.
1. El **servidor** crea la tubería con nombre en el método Init y la abre en modo escritura (mediante *mkfifo* y *open*).
1. Construir la cadena de texto con los datos a enviar (*sprintf*()). Se debe hacer al final del OnTimer().
1. Enviar los datos por la tubería (*write*).
1. Cerrar la tubería adecuadamente (*close* y *unlink* en el destructor de MundoCliente).

De esta forma, el proceso **servidor** debe ser lanzado antes que el **cliente**.

## 3. Envío de las teclas pulsadas del **cliente** al **servidor** ##

El envío de la tecla pulsada se debe realizar con otra tubería con nombre, en este caso donde el flujo de datos va en orden inverso.

Ya que el servidor debe estar esperando el mensaje del **cliente** y la recepción es bloqueante, el programa se quedaría bloqueado hasta recibir dicho mensaje. La solución propuesta es implementar un hilo que quede a la espera de dichos mensajes.

Los pasos en el **cliente** son los siguientes:

1. Añadir el identificador de la tubería como atributo de la clase MundoCliente.
1. El **cliente** crea la tubería con nombre en el método Init y la abre en modo escritura (mediante *mkfifo* y *open*).
1. Escribe los datos de la tubería (*sprintf* y *write*) en el OnKeyboardDown().
1. Cerrar la tubería adecuadamente (*close* y *unlink* en el destructor de MundoCliente).

Los pasos en el **servidor** son los siguientes:

1. Añadir un identificador de thread como atributo de la clase MundoServidor (recuerda añadir la librería correspondiente en el fichero CMakeLists.txt).
1. En el Init() del **servidor**, crear el thread indicándole la función a ejecutar:

```
pthread_create(&thid1, NULL, hilo_comandos, this);
```

A continuación se proporciona la implementación de hilo_comandos(). Recuerda añadir el método RecibeComandosJugador() en la clase MundoServidor:

```
void* hilo_comandos(void* d)
{
      CMundo* p=(CMundo*) d;
      p->RecibeComandosJugador();
}

void CMundo::RecibeComandosJugador()
{
     while (1) {
            usleep(10);
            char cad[100];
            read(TUBERIA_CREADA, cad, sizeof(cad));
            unsigned char key;
            sscanf(cad,"%c",&key);
            if(key=='s')jugador1.velocidad.y=-4;
            if(key=='w')jugador1.velocidad.y=4;
            if(key=='l')jugador2.velocidad.y=-4;
            if(key=='o')jugador2.velocidad.y=4;
      }
}
```

Como se puede ver, el método RecibeComandosJugador() hace un bucle infinito donde, en cada iteración, lee de la tubería la tecla pulsada y modifica la velocidad del jugador correspondiente.

El **servidor** debe cerrar adecuadamente la tubería en su destructor.

Comprueba que todos los procesos funcionan adecuadamente (**cliente**, **servidor**, **logger** y **bot**). Una vez comprobado, haz un merge de la rama practica4 con la rama master:

```
$ git checkout master
$ git merge practica4
$ git push origin master 
```

Y por último crea una etiqueta con el texto: 'Fin de la práctica 4'.

# EJERCICIO OPCIONAL PROPUESTO #

Se pide incorporar la captura de señales en el **servidor** (SIGINT, SIGTERM, SIGPIPE y SIGUSR2) para que saquen por la salida estándar el estado de terminación del proceso. En el caso de la recepción de la señal SIGUSR2, el proceso termina y se considera que termina correctamente (devuelve 0). En el resto de los casos, el proceso termina por la recepción de la señal y devolverá el valor de la señal que ha provocado la finalización del **servidor**.
