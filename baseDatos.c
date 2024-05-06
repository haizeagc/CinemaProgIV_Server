#include "baseDatos.h"
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "config.h"
#include "estructuras.h"

//SUBIR
void subirClienteBase(HashMap *config, Cliente c){
	sqlite3 *db;
		sqlite3_stmt *stmt;
		int result;

		result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
		if (result != SQLITE_OK){
			logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para subir clientes.");
		}else{
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para subir clientes.");
		}
		Cliente * clientes = volcarCl(obtenerConfigConcreto(config,"cliente"));
		logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se han obtenido los clientes para el volcado inicial.");
		for(int k=0; k< 6; k++){
			char sql1[] = "insert into CLIENTE (dni, nombre, num_tarj, pais, contrasena, telf) values (?,?,?,?,?,?)";

			char* dni = clientes[k].dni;
			char* nombre = clientes[k].nombre;
			char* num_tarj = clientes[k].num_tarj;
			char* pais = clientes[k].pais;
			int contrasena = clientes[k].contrasena;
			int telf = clientes[k].telf;

			result = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para insertar clientes no ha podido prepararse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para insertar clientes esta preparado.");
			}
			sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
			sqlite3_bind_text(stmt, 3, num_tarj,strlen(num_tarj),SQLITE_STATIC);
			sqlite3_bind_text(stmt, 4, pais, strlen(pais), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 5, contrasena);
			sqlite3_bind_int(stmt, 6, telf);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido insertar este cliente a la base de datos.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha insertado el cliente a la base de datos.");
				}

			}

		result = sqlite3_finalize(stmt);
					if (result != SQLITE_OK){
						logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para insertar clientes no ha podido finalizarse.");
					}else{
						logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para insertar clientes ha sido finalizado.");
					}
			result = sqlite3_close(db);
					if(result != SQLITE_OK){
						logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para insertar clientes.");
					}else{
						logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para insertar clientes.");
					}

		free(clientes);
		free(clientes->dni);
		free(clientes->nombre);
		free(clientes->num_tarj);
		free(clientes->pais);
		logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Memoria que contenia los valores de clientes del csv ha sido liberada.");
}

void subirEntradaBase(HashMap *config, Entrada e){
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int result;

		result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
		if (result != SQLITE_OK){
			logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para subir entradas.");
		}else{
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para subir entradas.");
		}
		Entrada *entradas = volcarEnt(obtenerConfigConcreto(config,"entrada"));
		logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se han obtenido las entradas para el volcado inicial.");
		for(int k=0; k< 6; k++){
			char sql3[] = "insert into ENTRADA (cod_E, dni, cod_pelicula, sala, hora, dia, mes, ano, importe, persona) values (?,?,?,?,?,?,?,?,?,?)";

			int cod_E = entradas[k].cod_E;
			char* dni = entradas[k].dni;
			int cod_pelicula = entradas[k].cod_pelicula;
			int sala = entradas[k].sala;
			char* hora = entradas[k].hora;
			int dia = entradas[k].dia;
			int mes = entradas[k].mes;
			int ano = entradas[k].ano;
			int importe = entradas[k].importe;
			int personas = entradas[k].personas;

			result = sqlite3_prepare_v2(db, sql3, strlen(sql3) + 1, &stmt, NULL);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para insertar entradas no ha podido prepararse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para insertar entradas esta preparado.");
			}
			sqlite3_bind_int(stmt, 1, cod_E);
			sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, cod_pelicula);
			sqlite3_bind_int(stmt, 4, sala);
			sqlite3_bind_text(stmt, 5, hora, strlen(hora), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 6, dia);
			sqlite3_bind_int(stmt, 7, mes);
			sqlite3_bind_int(stmt, 8, ano);
			sqlite3_bind_int(stmt, 9, importe);
			sqlite3_bind_int(stmt, 10, personas);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido insertar esta entrada a la base de datos.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha insertado la entrada a la base de datos.");
				}

			}

		result = sqlite3_finalize(stmt);
					if (result != SQLITE_OK){
						logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para insertar entradas no ha podido finalizarse.");
					}else{
						logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para insertar entradas ha sido finalizado.");
					}
			result = sqlite3_close(db);
					if(result != SQLITE_OK){
						logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para insertar entradas.");
					}else{
						logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para insertar entradas.");
					}

		free(entradas);
		free(entradas->dni);
		free(entradas->hora);
		logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Memoria que contenia los valores de entradas del csv ha sido liberada.");
}

//OBTENER
void obtenerPeliculaBase(Arrays *a, HashMap *config){

			sqlite3 *db;
			sqlite3_stmt *stmt;
			int result;
			result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para obtener pelicula.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para obtener peliculas.");
			}
			char sql2[] = "SELECT COD_PELICULA,NOMBRE,GENERO,DIRECTOR,HORA,SALA,PRECIO FROM PELICULA";
			result = sqlite3_prepare_v2(db,sql2,-1,&stmt,NULL);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener peliculas no ha podido prepararse.");
			}else {
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para obtener peliculas esta preparado.");
			}

			int i = 0;
			do{
					result = sqlite3_step(stmt);
					if(result == SQLITE_ROW){
						i++;
					}
				}while(result == SQLITE_ROW);
			a->cantidadPelicula = i;
			a->arrayPelicula = (Pelicula*)malloc(sizeof(Pelicula)*i);
			logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Obtenida la cantidad de peliculas.");
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener peliculas no ha podido finalizarse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para obtener peliculas ha finalizado.");
			}

			sqlite3_prepare_v2(db,sql2,-1,&stmt,NULL);
			logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se ha preparado el statement para obtener peliculas.");
			for (int j = 0; j < i; j++){
						result = sqlite3_step(stmt);
						if(result == SQLITE_ROW){

							a->arrayPelicula[j].cod_pelicula = sqlite3_column_int(stmt, 0);
							a->arrayPelicula[j].nombre = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 1))+1));
							strcpy(a->arrayPelicula[j].nombre, (char *) sqlite3_column_text(stmt, 1));
							a->arrayPelicula[j].genero = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 2))+1));
							strcpy(a->arrayPelicula[j].genero, (char *) sqlite3_column_text(stmt, 2));
							a->arrayPelicula[j].director = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 3))+1));
							strcpy(a->arrayPelicula[j].director, (char *) sqlite3_column_text(stmt, 3));
							a->arrayPelicula[j].hora = (char*)malloc(sizeof(char)*(strlen((char *) sqlite3_column_text(stmt, 4))) +1);
							strcpy(a->arrayPelicula[j].hora, (char *) sqlite3_column_text(stmt, 4));

							//int
							a->arrayPelicula[j].sala = sqlite3_column_int(stmt, 5);
							a->arrayPelicula[j].precio =sqlite3_column_int(stmt, 6);
							logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se ha obtenido una pelicula.");
						}
			}
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener peliculas no ha podido finalizarse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para obtener peliculas ha finalizado.");
			}
			result = sqlite3_close(db);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para obtener peliculas.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para obtener peliculas.");
			}

	}

void obtenerClienteBase(Arrays *a, HashMap *config){
	sqlite3 *db;
			sqlite3_stmt *stmt;
			int result;
			result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para obtener clientes.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para obtener clientes.");
			}
			char sql2[] = "SELECT DNI,NOMBRE,NUM_TARJ,PAIS,CONTRASENA,TELF FROM CLIENTE";
			result = sqlite3_prepare_v2(db,sql2,-1,&stmt,NULL);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener clientes no ha podido prepararse.");
			}else {
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para obtener clientes esta preparado.");
			}

			int i = 0;
			do{
					result = sqlite3_step(stmt);
					if(result == SQLITE_ROW){
						i++;
					}
				}while(result == SQLITE_ROW);
			a->cantidadCliente = i;
			a->arrayCliente = (Cliente*)malloc(sizeof(Cliente)*i);
			logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Obtenida la cantidad de clientes.");
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener clientes no ha podido finalizarse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para obtener clientes ha finalizado.");
			}

			sqlite3_prepare_v2(db,sql2,-1,&stmt,NULL);
			logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se ha preparado el statement para obtener clientes.");
			for (int j = 0; j < i; j++){
						result = sqlite3_step(stmt);
						if(result == SQLITE_ROW){
							a->arrayCliente[j].dni = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 0))+1));
							strcpy(a->arrayCliente[j].dni, (char *) sqlite3_column_text(stmt, 0));
							a->arrayCliente[j].nombre = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 1))+1));
							strcpy(a->arrayCliente[j].nombre, (char *) sqlite3_column_text(stmt, 1));
							a->arrayCliente[j].num_tarj = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 2))+1));
							strcpy(a->arrayCliente[j].num_tarj, (char *) sqlite3_column_text(stmt, 2));
							a->arrayCliente[j].pais = (char*)malloc(sizeof(char)*(strlen((char *) sqlite3_column_text(stmt, 3))) +1);
							strcpy(a->arrayCliente[j].pais, (char *) sqlite3_column_text(stmt, 3));
							a->arrayCliente[j].contrasena = sqlite3_column_int(stmt, 4);
							a->arrayCliente[j].telf =sqlite3_column_int(stmt, 5);
							logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se ha obtenido un cliente.");
						}
			}
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener clientes no ha podido finalizarse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para obtener clientes ha finalizado.");
			}
			result = sqlite3_close(db);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para obtener Clientes.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para obtener Clientes.");
			}

	}

void obtenerEntradaBase(Arrays *a, HashMap *config){
	sqlite3 *db;
				sqlite3_stmt *stmt;
				int result;
				result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
				if (result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para obtener clientes.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para obtener clientes.");
				}
				char sql2[] = "SELECT COD_E, DNI, COD_PELICULA, SALA, HORA, DIA, MES, ANO, IMPORTE, PERSONA FROM ENTRADA";
				result = sqlite3_prepare_v2(db,sql2,-1,&stmt,NULL);
				if (result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener clientes no ha podido prepararse.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para obtener clientes esta preparado.");
				}

				int i = 0;
				do{
						result = sqlite3_step(stmt);
						if(result == SQLITE_ROW){
							i++;
						}
					}while(result == SQLITE_ROW);
				a->cantidadEntrada = i;
				a->arrayEntrada = (Entrada*)malloc(sizeof(Entrada)*i);
				logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Obtenida la cantidad de entradas.");
				result = sqlite3_finalize(stmt);
				if (result != SQLITE_OK) {
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener entradas no ha podido finalizarse.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para obtener entradas ha finalizado.");
				}

				sqlite3_prepare_v2(db,sql2,-1,&stmt,NULL);
				logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se ha preparado el statement para obtener entradas.");
				for (int j = 0; j < i; j++){
							result = sqlite3_step(stmt);
							if(result == SQLITE_ROW){
								a->arrayEntrada[j].cod_E = sqlite3_column_int(stmt,0);
								a->arrayEntrada[j].dni = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 1))+1));
								strcpy(a->arrayEntrada[j].dni, (char *) sqlite3_column_text(stmt, 1));
								a->arrayEntrada[j].cod_pelicula = sqlite3_column_int(stmt,2);
								a->arrayEntrada[j].sala = sqlite3_column_int(stmt,3);
								a->arrayEntrada[j].hora = (char*)malloc(sizeof(char) * (strlen((char *) sqlite3_column_text(stmt, 4))+1));
								strcpy(a->arrayEntrada[j].hora, (char *) sqlite3_column_text(stmt, 4));
								a->arrayEntrada[j].dia = sqlite3_column_int(stmt,5);
								a->arrayEntrada[j].mes = sqlite3_column_int(stmt,6);
								a->arrayEntrada[j].ano = sqlite3_column_int(stmt,7);
								a->arrayEntrada[j].importe = sqlite3_column_int(stmt,8);
								a->arrayEntrada[j].personas = sqlite3_column_int(stmt,9);
								logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se ha obtenido una entrada.");
							}
				}
				result = sqlite3_finalize(stmt);
				if (result != SQLITE_OK) {
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para obtener entradas no ha podido finalizarse.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para obtener entradas ha finalizado.");
				}
				result = sqlite3_close(db);
				if(result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para obtener Entradas.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para obtener Entradas.");
				}

		}
//ACTUALIZAR
void actuCliente(char *dni, char* nombre, char *num, char *pais, int contra, int telf, HashMap *config){

}

//BORRAR

void borrarClienteDni(char *dni, HashMap *config){

}
void borrarEntradaDni(char *dni, HashMap *config){

}
void borrar(){

}


