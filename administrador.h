#ifndef BASEDATOS_ADMINISTRADOR_H_
#define BASEDATOS_ADMINISTRADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "estructuras.h"

void starting(Arrays *arrays, HashMap *confi);
void iniciarSesion(Arrays *arrays, HashMap *confi);
void consumirNuevaLinea();

void hacer(Arrays *arrays, HashMap *confi);

void gestionAdmin(Arrays *arrays, HashMap *confi);
void gestionPeli(Arrays *arrays, HashMap *confi);
void gestionCli(Arrays *arrays, HashMap *confi);
void gestionEnt(Arrays *arrays, HashMap *confi);

void eliminarAdmin(Arrays *arrays, HashMap *confi);
void eliminarPeli(Arrays *arrays, HashMap *confi);
void eliminarCli(Arrays *arrays, HashMap *confi);
void eliminarEnt(Arrays *arrays, HashMap *confi);

void aniadirAdmin(Arrays *arrays, HashMap *confi);
void aniadirPeli(Arrays *arrays, HashMap *confi);

void liberar(Arrays *arrays, HashMap *confi);

#endif
