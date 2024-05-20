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
		logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se han obtenido los clientes para el volcado inicial.");
			char sql1[] = "insert into CLIENTE (DNI, NOMBRE, NUM_TARJ, PAIS, CONTRASENA, TELF) values (?,?,?,?,?,?)";

			result = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para insertar clientes no ha podido prepararse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para insertar clientes esta preparado.");
			}
			sqlite3_bind_text(stmt, 1, c.dni, strlen(c.dni), SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, c.nombre, strlen(c.nombre), SQLITE_STATIC);
			sqlite3_bind_text(stmt, 3, c.num_tarj,strlen(c.num_tarj),SQLITE_STATIC);
			sqlite3_bind_text(stmt, 4, c.pais, strlen(c.pais), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 5, c.contrasena);
			sqlite3_bind_int(stmt, 6, c.telf);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido insertar este cliente a la base de datos.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha insertado el cliente a la base de datos.");
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

		logger_log(obtenerConfigConcreto(config,"logger"),"INFO","Se han obtenido las entradas para el volcado inicial.");
			char sql3[] = "insert into ENTRADA (cod_E, dni, cod_pelicula, sala, hora, dia, mes, ano, importe, cantidad) values (?,?,?,?,?,?,?,?,?,?)";

			result = sqlite3_prepare_v2(db, sql3, strlen(sql3) + 1, &stmt, NULL);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para insertar entradas no ha podido prepararse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para insertar entradas esta preparado.");
			}
			sqlite3_bind_int(stmt, 1, e.cod_E);
			sqlite3_bind_text(stmt, 2, e.dni, strlen(e.dni), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, e.cod_pelicula);
			sqlite3_bind_int(stmt, 4, e.sala);
			sqlite3_bind_text(stmt, 5, e.hora, strlen(e.hora), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 6, e.dia);
			sqlite3_bind_int(stmt, 7, e.mes);
			sqlite3_bind_int(stmt, 8, e.ano);
			sqlite3_bind_int(stmt, 9, e.importe);
			sqlite3_bind_int(stmt, 10, e.cantidad);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido insertar esta entrada a la base de datos.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha insertado la entrada a la base de datos.");
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
								a->arrayEntrada[j].cantidad = sqlite3_column_int(stmt,9);
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
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int result;
		result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
		if (result != SQLITE_OK){
			logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para bloquear/desbloquear un cliente.");
		}else{
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para bloquear/desbloquear un cliente.");
			}

		char sql[] = "UPDATE CLIENTE SET NOMBRE = ?, NUM_TARJ = ?, PAIS = ?, CONTRASENA = ?, TELF = ? WHERE DNI = ?";
		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK){
			logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para bloquear/desbloquear un cliente no ha podido prepararse.");
		}else{
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para bloquear/desbloquar un cliente esta preparado.");
		}
		sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, num, strlen(num), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, pais, strlen(pais), SQLITE_STATIC);
		sqlite3_bind_int(stmt, 4, contra);
		sqlite3_bind_int(stmt, 5, telf);
		sqlite3_bind_text(stmt, 6, dni,strlen(dni), SQLITE_STATIC);


		result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","El statement para bloquear/desbloquar un cliente no se ha ejecutado.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para bloquear/desbloquar un cliente se ha ejecutado.");
				}
		result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para bloquear/desbloquear un cliente no ha podido finalizarse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para bloquear/desbloquar un cliente ha finalizado.");
			}
		result = sqlite3_close(db);
			if(result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para bloquear cliente.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para bloquear cliente.");
			}
		}

//BORRAR
void borrarEntrada(int codE, char *DNI, int cod_peli, int sala, char* hora, int dia, int mes, int ano, HashMap *config){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
	if (result != SQLITE_OK){
		logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para reembolsar una entrada.");
	}else{
		logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para reembolsar una entrada.");
	}
	char sql1[] = "DELETE FROM ENTRADA WHERE DNI = ? AND COD_E = ? AND COD_PELICULA = ? AND SALA = ? AND HORA = ? AND DIA = ? AND MES= ? AND ANO= ?";
	result = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
	if (result != SQLITE_OK){
		logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para cancelar una reserva no ha podido prepararse.");
	}else{
		logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para cancelar una reserva esta preparado.");
	}
	sqlite3_bind_text(stmt, 1, DNI, strlen(DNI), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, codE);
	sqlite3_bind_int(stmt, 3, cod_peli);
	sqlite3_bind_int(stmt, 4, sala);
	sqlite3_bind_text(stmt, 5, hora, strlen(hora), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 6, dia);
	sqlite3_bind_int(stmt, 7, mes);
	sqlite3_bind_int(stmt, 8, ano);
	result = sqlite3_step(stmt);
		if (result != SQLITE_DONE){
			logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","El statement para cancelar una reserva no se ha ejecutado.");
		}else {
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para cancelar una reserva se ha ejecutado.");
		}

	result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK){
			logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para cancelar una reserva no ha podido finalizarse.");
		}else{
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para cancelar una reserva ha finalizado.");
		}
	result = sqlite3_close(db);
		if(result != SQLITE_OK){
			logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para cancelar reserva.");
		}else{
			logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para cancelar reserva.");
		}
}



void borrarClienteDni(char *dni, HashMap *config){
			sqlite3 *db;
			sqlite3_stmt *stmt;
			int result;
			result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para borrar un cliente.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para borrar un cliente.");
			}
				char sql[] = "DELETE FROM CLIENTE WHERE DNI = ?";
				result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
			if (result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para borrar un cliente no ha podido prepararse.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para borrar un cliente esta preparado.");
				}
			sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","El statement para borrar un cliente no se ha ejecutado.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para borrar un cliente se ha ejecutado.");
				}

			result = sqlite3_finalize(stmt);
				if (result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para borrar un cliente no ha podido finalizarse.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para borrar un cliente ha finalizado.");
				}
			result = sqlite3_close(db);
				if(result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para borrar cliente.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para borrar cliente.");
				}
				borrarEntradaDni(dni,config);

}
void borrarEntradaDni(char *dni, HashMap *config){
	sqlite3 *db;
			sqlite3_stmt *stmt;
			int result;
			result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para borrar una entrada.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para borrar una entrada.");
			}
			char sql1[] = "DELETE FROM ENTRADA WHERE DNI = ?";
			result = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para borrar una entrada no ha podido prepararse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para borrar una entrada esta preparado.");
			}
			sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","El statement para borrar una entrada no se ha ejecutado.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para borrar una entrada se ha ejecutado.");
				}

			result = sqlite3_finalize(stmt);
				if (result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para borrar una entrada no ha podido finalizarse.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para borrar una entrada ha finalizado.");
				}
			result = sqlite3_close(db);
				if(result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para borrar entrada.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para borrar entrada.");
				}

}
void borrarEntrada1(char *dni, int codE, HashMap *config){
	sqlite3 *db;
			sqlite3_stmt *stmt;
			int result;
			result = sqlite3_open(obtenerConfigConcreto(config,"base"), &db);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","No se ha abierto la base de datos para cancelar una entrada.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha abierto la base de datos para cancelar una entrada.");
			}
			char sql1[] = "DELETE FROM ENTRADA WHERE DNI = ? AND COD_E = ? ";
			result = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
			if (result != SQLITE_OK){
				logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para cancelar una entrada no ha podido prepararse.");
			}else{
				logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para cancelar una entrada esta preparado.");
			}
			sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 2, codE);
			result = sqlite3_step(stmt);
				if (result != SQLITE_DONE){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","El statement para cancelar una entrada no se ha ejecutado.");
				}else {
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","El statement para cancelar una entrada se ha ejecutado.");
				}

			result = sqlite3_finalize(stmt);
				if (result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"SEVERE","El statement para cancelar una entrada no ha podido finalizarse.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Statement para cancelar una entrada ha finalizado.");
				}
			result = sqlite3_close(db);
				if(result != SQLITE_OK){
					logger_log(obtenerConfigConcreto(config,"logger"),"WARNING","No se ha podido cerrar la base de datos para cancelar entrada.");
				}else{
					logger_log(obtenerConfigConcreto(config,"logger"),"FINE","Se ha cerrado la base de datos para cancelar entrada.");
				}
}


