// bot.cpp
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "DatosMemCompartida.h"

#define SHM_NAME "/shm_tenis"

int main(int argc, char* argv[])
{
    // 1. Declarar una variable de tipo puntero a DatosMemCompartida
    DatosMemCompartida* dat;
    int fd;
    
    // 2. Abrir el fichero proyectado en memoria creado en el tenis y proyectarlo
    fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1)
    {
        perror("Error al abrir el objeto de memoria compartida"); 
        return 1;
    }

    char *direccion = (char *)mmap(NULL, sizeof(DatosMemCompartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (direccion == MAP_FAILED)
    {
        perror("Error en la proyección mmap"); 
        close(fd);
        return 1;
    }

    // 3. Cerrar el descriptor de fichero
    close(fd);

    // 4. Asignar la dirección de comienzo de la región creada al puntero
    dat = (DatosMemCompartida*)direccion;

    //  Bucle infinito con usleep(25000)  y lógica de movimiento del bot
    while(1)
    {
        usleep(25000);

        // Lógica de control: comparar la posición Y de la esfera con la raqueta1
        float raquetaY = (dat->raqueta1.y1 + dat->raqueta1.y2) / 2.0f;
        float esferaY = dat->esfera.centro.y;

        if (esferaY > raquetaY + 0.1f)
        {
            dat->accion = 1;  // Mover hacia arriba
        }
        else if (esferaY < raquetaY - 0.1f)
        {
            dat->accion = -1; // Mover hacia abajo
        }
        else
        {
            dat->accion = 0;  // Mantenerse
        }
    }

    munmap(direccion, sizeof(DatosMemCompartida));
    return 0;
}
