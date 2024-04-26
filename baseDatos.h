#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <time.h>
#include "config.h"
#include "estructuras.h"
#include "logger.h"


#ifndef BASEDATOS_BASEDATOS_H_
#define BASEDATOS_BASEDATOS_H_

void reiniciar(HashMap *config);

void subirAdminBase(HashMap *config);
void anadirAdminBase(char* nom, int contra, HashMap *config);
void borrarAdminBase(char* nom, HashMap *config);
void obtenerAdminBase(Arrays *a, HashMap *config);

void subirPeliculaBase(HashMap *config);
void anadirPeliculaBase(int cod, char* nom, char* genero, char* director, char* hora, int sala, int precio ,HashMap *config);
void borrarPeliculaBase(int cod, HashMap *config);
void obtenerPeliculaBase(Arrays *a, HashMap *config);

void subirClienteBase(HashMap *config);
void borrarClienteBase(char* dni, HashMap *config);
void obtenerClienteBase(Arrays *a, HashMap *config);

void subirEntradaBase(HashMap *config);
void borrarEntradaBase(int cod, HashMap *config);
void obtenerEntradaBase(Arrays *a, HashMap *config);

#endif
