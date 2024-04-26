/*
 * estructuras.h
 *
 *  Created on: 1 abr 2024
 *      Author: Haizea
 */
#ifndef BASEDATOS_ESTRUCTURAS_H_
#define BASEDATOS_ESTRUCTURAS_H_

typedef struct Admin{
	char* usuario;
	int contrasena;
}Admin;

typedef struct Cliente{
	char* dni;
	char* nombre;
	char* num_tarj;
	char* pais;
	int contrasena;
	int telf;
}Cliente;

typedef struct Entrada{
	int cod_E;
	char* dni;
	int cod_pelicula;
	int sala;
	char* hora;
	int dia;
	int mes;
	int ano;
	int importe;
	int personas;
}Entrada;

typedef struct Pelicula{
	int cod_pelicula;
	char* nombre;
	char* genero;
	char* director;
	char* hora;
	int sala;
	int precio;
}Pelicula;

typedef struct Arrays{
	int cantidadAdmin;
	Admin* arrayAdmin;
	int cantidadPelicula;
	Pelicula* arrayPelicula;
	int cantidadEntrada;
	Entrada* arrayEntrada;
	int cantidadCliente;
	Cliente* arrayCliente;
}Arrays;

#endif
