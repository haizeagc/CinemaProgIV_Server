

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"



void asignarLevel(mensaje *m, char *level){
	if(strcmp(level, "SEVERE") == 0 || strcmp(level, "WARNING") == 0 || strcmp(level, "INFO") == 0 || strcmp(level, "CONFIG") == 0 || strcmp(level, "FINE") == 0 || strcmp(level, "FINER") == 0 || strcmp(level, "FINEST") == 0){
		m->level = (char*)malloc(sizeof(char)*(strlen(level)+1));
		strcpy(m->level, level);
	}
}

void asignarMensaje(mensaje *m, char *mensaje){
	m->message = (char*) malloc(sizeof(char) * (strlen(mensaje)+1));
	strcpy(m->message, mensaje);
}

void liberarMensaje(mensaje *m){
	free(m->level);
	free(m->message);
	free(m);
}

void iniciarLogger(char *fichero){
	FILE *f;
	f = fopen(fichero, "w");
	fclose(f);
}

void logger_log(char *fichero, char *level, char *mensajes){
	FILE *f;
	f = fopen(fichero, "a");

		mensaje m;

		asignarLevel(&m, level);
		asignarMensaje(&m, mensajes);

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		fprintf(f, "[%d-%02d-%02d %02d:%02d;%02d]", tm.tm_year + 1990, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "[%s] %s\n", m.level, m.message);
		fflush(stdout);

	fclose(f);

	liberarMensaje(&m);
}


