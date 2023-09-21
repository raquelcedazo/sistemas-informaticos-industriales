# Práctica 5 - Comunicación por sockets #

Antes de comenzar con el desarrollo de la práctica 5, crea una etiqueta en el repositorio con el mensaje 'Fin de la práctica 4' para marcar el hito (si no lo habías hecho previamente).

A continuación, para la realización de la práctica 5, crea una rama y salta a dicha rama:

```
$ git branch practica5
$ git checkout practica5
```

Recuerda hacer el merge con la rama principal cuando termines la práctica.

## Objetivos ##

Esta práctica tiene como objetivo desarrollar una versión del juego distribuida, utilizando los servicios proporcionados en POSIX para el manejo de sockets.

El esquema propuesto de los procesos para la realización de la práctica es el siguiente:

![3022657928-esquema-p4.png](https://bitbucket.org/repo/6L8Rg8/images/1312771854-3022657928-esquema-p4.png)

Tanto el envío de coordenadas del **servidor** al **cliente** como de las teclas pulsadas del **cliente** al **servidor**, se realizan a través de un socket.

## Comunicación local por sockets entre cliente y servidor ##

En este caso se ejecutarán las dos aplicaciones (**cliente** y **servidor**) en la misma máquina utilizando la dirección local 127.0.0.1.

En primer lugar, hay que eliminar las tuberías entre cliente y servidor de la anterior práctica como indica el esquema anterior.

Para esta práctica se proporciona una clase Socket en C++ que encapsula todas las funcionalidades necesarias para **cliente** y **servidor**. Copia los ficheros Socket.cpp y Socket.h de tu directorio **external** e inclúyelos en tu proyecto. Recuerda modificar el fichero CMakeLists.txt para incluirlos en el proceso de compilación.

Utilizando la API proporcionada por la clase Socket, modifica el código del **servidor** y del **cliente** para incorporar los siguientes cambios.

Los cambios en el **servidor** son:

1. Debe declarar dos sockets diferentes, uno para la conexión y otro para la comunicación con el **cliente**.
1. El **servidor** enlaza el socket de conexión a una dirección IP y un puerto (siendo la IP la de la máquina en la que corre el **servidor**).
1. Se queda a la espera de una conexión escuchando en ese puerto.
1. Cuando el **cliente** se conecta, el **servidor** se desbloquea y devuelve el socket para la comunicación con el **cliente**, que es por el que se envían y reciben los datos.
1. El **servidor** recibe el nombre del **cliente** conectado a través del socket y lo imprime por pantalla.
1. El **servidor** envía las coordenadas a través del socket al **cliente** en el OnTimer.
1. El hilo que recibe los comandos del **cliente** es el que recibe los datos de las teclas a través del socket.

Los cambios en el **cliente** son:

1. Debe declarar un socket para la comunicación con el **servidor**.
1. El **cliente** pide por teclado un nombre para enviárselo al **servidor**.
1. El **cliente** se conecta a la IP y puerto del servidor.
1. Envía el nombre a través del socket.
1. El **cliente** recibe las coordenadas a través del socket en el OnTimer.
1. El **cliente** envía la tecla a través del socket en el método OnKeyboardDown.

Nota: Los programas **logger** y **bot** deben seguir funcionando correctamente siguiendo la especificación de las prácticas anteriores.

## Comunicación distribuida por sockets entre cliente y servidor ##

Prueba en parejas la aplicación desarrollada. Para ello uno de los miembros de la pareja deberá ejecutar en su equipo los programas **servidor** y **logger**, mientras que el otro ejecutará los programas **cliente** y **bot**.

Previamente a la ejecución, configura correctamente en el código la IP y puerto de escucha del servidor (utiliza el mandato **ifconfig** para ver la IP de las máquinas).

Comprueba que todos los procesos funcionan adecuadamente. Una vez comprobado, haz un merge de la rama practica5 con la rama master:

```
$ git checkout master
$ git merge practica5
$ git push origin master 
```

Y por último crea una etiqueta con el texto: 'Fin de la práctica 5'.

# EJERCICIO OPCIONAL PROPUESTO #

El objetivo de este último ejercicio es permitir que varios **clientes** se puedan conectar y desconectar cuando quieran, y que los jugadores puedan efectivamente jugar de forma remota.

## Requisitos ##

Se resumen las funcionalidades que quedan por implementar en el sistema distribuido:

1. Se quiere permitir que los **clientes** se puedan conectar en el instante que quieran. El **servidor** no debe quedar bloqueado por esperar a que los **clientes** se conecten.
1. Se quiere permitir cualquier número de **clientes** "espectadores". De dichos espectadores, únicamente los dos primeros son los que efectivamente podrán controlar las raquetas.
1. Los dos primeros **clientes** que se conecten podrán controlar las raquetas: el primero de ellos con las teclas 'w' y 's' y el segundo con las teclas 'l' y 'o'.
1. El **servidor** debe de gestionar adecuadamente las desconexiones de los **clientes**.

## Estructura del servidor ##

Las tareas a realizar son las siguientes:

1. Puesto que la aceptación de nuevos **clientes** es bloqueante, siempre se tiene que estar ejecutando el *accept*() si se quiere que los clientes puedan conectarse y desconectarse. Por lo tanto, es necesario crear un hilo para esta tarea.
1. La recepción de las teclas del segundo **cliente** no debe bloquear al **servidor**. Por tanto, la solución es implementar otro hilo para recibir las órdenes del jugador 2 que esté a la espera de dichos mensajes.

## Múltiples conexiones simultáneas ##

Para permitir la conexión simultánea de múltiples **clientes**, es necesario mantener un socket por cada uno de dichos **clientes**. Para ello se declara en la clase CMundo de MundoServidor un vector de la STL de objetos de la clase Socket. Utilizar un vector STL permite añadir más cómodamente nuevos objetos, quitarlos y recorrer el vector de forma sencilla. Se sugiere implementar un método GestionaConexiones() que se encarga de realizar dicha gestión. De ese modo se tendría:

```
class CMundo 
{
public:
   ...
   Socket servidor;
   std::vector<Socket> conexiones;
   void GestionaConexiones();
   ...
};
```

En el **servidor** hay que lanzar un hilo de forma similar a como se hizo en la parte obligatoria de esta práctica. La tarea que tiene que hacer esta función es invocar al método GestionaConexiones(). Este método estará en un bucle infinito en el que se repite un *accept*() para que, cada vez que se conecte un cliente, se añada al vector de clientes conectados.

## Gestionar las desconexiones ##

En cualquier instante los **clientes** pueden desconectarse. El **servidor** debe analizar y gestionar las conexiones adecuadamente.

La forma más sencilla de detectar las desconexiones es en el envío realizado en la función OnTimer() en el lado del **servidor**. El envío se realiza a todos los **clientes** conectados. Por tanto, se podría utilizar el retorno de *send*() para realizar la eliminación del **cliente** del vector. No obstante, hay que tener en cuenta los efectos del borrado sobre el vector que se está recorriendo.

Una solución sería recorrer el vector al revés, desde el final al comienzo, con lo que las eliminaciones no afectan al bucle:

```
  void CMundo::OnTimer(int value) {
     ...
     for (i=conexiones.size()-1; i>=0; i--) {
         if (conexiones[i].Send(cad,200) <= 0) {
            conexiones.erase(conexiones.begin()+i);
            if (i < 2) // Hay menos de dos clientes conectados
              // Se resetean los puntos a cero
         }
     }
  }
```

Nótese que de este modo, si se han desconectado uno de los dos primeros clientes (los jugadores), entonces el primer espectador pasará a ocupar su lugar y comenzará una nueva partida poniendo los marcadores a cero.

## Finalización del programa ##

Hasta este punto, al cerrar el programa servidor, los hilos acaban de forma forzada. Es conveniente realizar un cierre ordenado de todos los hilos en ejecución.

Para ello se deben seguir los siguientes pasos en el **servidor**:

1. Añadir un atributo "acabar" que inicialmente valga 0.
2. Establecer el valor de "acabar" a 1 en el destructor de la clase CMundo.
3. Utilizar dicho atributo como condición de repetición en los bucles while() de todos los hilos:

        while(!acabar)
        {
        ...
        }

4. Poner los identificadores de todos los hilos como atributos de la clase para que se puedan utilizar en el *pthread_join*.
5. Ejecutar el *pthread_join* tantas veces como sea necesario en el destructor de la clase CMundo, para esperar a que terminen los hilos.