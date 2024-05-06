#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <time.h>
#include "config.h"
#include "estructuras.h"
#include "logger.h"


#ifndef BASEDATOS_BASEDATOS_H_
#define BASEDATOS_BASEDATOS_H_

//Subir
void subirClienteBase(HashMap *config, Cliente c);
void subirEntradaBase(HashMap *config, Entrada e);

//Obtener
void obtenerClienteBase(Arrays *a, HashMap *config);
void obtenerEntradaBase(Arrays *a, HashMap *config);
void obtenerPeliculaBase(Arrays *a, HashMap *config);

//Actualizar
void actuCliente(char *dni, char* nombre, char *num, char *pais, int contra, int telf, HashMap *config);

//Borrar
void borrarClienteDni(char *dni, HashMap *config);
void borrarEntradaDni(char *dni, HashMap *config);
void borrar();

#endif
