#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];

    // borrar FIFO por si existiera previamente
    unlink("tuberia");

    /* crear el FIFO */
    if (mkfifo("tuberia", 0666)<0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abrir el FIFO */
    if ((fd=open("tuberia",O_RDONLY))<0) {
        perror("No puede abrirse el FIFO");
        return(1);
		//Guarda -1 en fd como resultado de no aberse ejecutado "bien"
    }
    /* Leer de la FIFO */
    while (read(fd, buffer, sizeof(buffer)) > 0) {
	// X5: Imprimir el texto en la pantalla
	printf("%s", buffer);
    }
    close(fd); //la funcion close recibe un entero como parametro, asi que se le pasa fd
	//TABLA DE DESCRIPTORES DE ARCHIVO, libera el que ocupe fd
    unlink("tuberia"); //eliminar el archivo tuberia
    return(0);
}