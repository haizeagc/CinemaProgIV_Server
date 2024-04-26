

#ifndef LOGGER_H_
#define LOGGER_H_
#include <time.h>

typedef struct mensaje{
	char *level;
	char *message;
}mensaje;

void asignarLevel(mensaje *m, char *level);
void asignarMensaje(mensaje *m, char *mensaje);
void liberarMensaje(mensaje *m);
void iniciarLogger(char *fichero);
void logger_log(char *fichero, char *level, char *mensaje);

#endif
