/*
 * info.h
 *
 *  Created on: 1 abr 2024
 *      Author: Haizea
 */

#ifndef BASEDATOS_INFO_H_
#define BASEDATOS_INFO_H_
#include "estructuras.h"

Admin* volcarAdmin(char *fich);
Pelicula* volcarPeli(char *fich);
Cliente* volcarCl(char *fich);
Entrada* volcarEnt(char *fich);
void libre(Pelicula *p, Cliente *cl, Entrada *e, Admin *a);


#endif /* BASEDATOS_INFO_H_ */
