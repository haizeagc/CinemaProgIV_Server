/*
 * info.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "logger.h"

Admin* volcarAdmin(char* fich){
		FILE *f;
		char a;
		int c = 0;
		int d = 0;

		f = fopen(fich, "r");
			while ((a = fgetc(f)) != EOF){
				c++;
				fflush(stdout);
				if(a == '\n'){
					d++;
				}
			}
		fclose(f);

	char b[c+1];
	char delimi[] =";";
	Admin *admins = (Admin*)malloc(sizeof(Admin)*d);

	f = fopen(fich, "r");
	fgets(b,c+1,f);

	for (int j=0;j<d-1;j++){
		fgets(b,c+1,f);
		//1
		char *token = strtok(b,delimi);
		admins[j].usuario = malloc (sizeof(char) * (strlen(token)+1));
		strcpy(admins[j].usuario, token);
		//2
		token = strtok(NULL,"\n");
		admins[j].contrasena = (int) strtol(token,NULL,10);
		//PRUEBAS
		//printf("Nombre: %s, Contraseña: %i \n",admins[j].usuario,admins[j].contrasena);

		}
	fclose(f);
	return admins;
}

Pelicula* volcarPeli(char *fich){
	FILE *f;
		char a;
		int c = 0;
		int d = 0;

		f = fopen(fich, "r");
			while ((a = fgetc(f)) != EOF){
				c++;
				fflush(stdout);
				if(a == '\n'){
					d++;
				}
			}
		fclose(f);

		char b[c+1];
		char delimi[] =";";
		Pelicula *peliculas = (Pelicula*)malloc(sizeof(Pelicula)*d);

		f = fopen(fich, "r");
		fgets(b,c+1,f);

		for (int i=0;i<d-1;i++){
			fgets(b, c+1, f);
			//1 int
			char *token = strtok(b, delimi);
			peliculas[i].cod_pelicula = (int) strtol(token,NULL,10);
			//2
			token = strtok (NULL, delimi);
			peliculas[i].nombre = malloc (sizeof(char)*(strlen(token)+1));
			strcpy(peliculas[i].nombre, token);
			//4
			token = strtok (NULL, delimi);
			peliculas[i].genero = malloc (sizeof(char)*(strlen(token)+1));
			strcpy(peliculas[i].genero, token);
			//5
			token = strtok (NULL, delimi);
			peliculas[i].director = malloc (sizeof(char)*(strlen(token)+1));
			strcpy(peliculas[i].director, token);
			//6
			token = strtok (NULL, delimi);
			peliculas[i].hora = malloc (sizeof(char)*(strlen(token)+1));
			strcpy(peliculas[i].hora, token);
			//7 int
			token = strtok (NULL, delimi);
			peliculas[i].sala = (int) strtol(token,NULL,10);
			//8 int
			token = strtok (NULL, "\n");
			peliculas[i].precio = (int) strtol(token,NULL,10);
			//PRUEBAS
			//printf("Cod: %d, Nombre: %s, Genero: %s, Director: %s, Hora: %s, Sala: %d, Precio: %d \n",peliculas[i].cod_pelicula,peliculas[i].nombre,peliculas[i].genero,peliculas[i].director,peliculas[i].hora,peliculas[i].sala,peliculas[i].precio);
		}

		fclose(f);
		return peliculas;
	}

Cliente* volcarCl(char *fich){
	FILE *f;
			char a;
			int c = 0;
			int d = 0;

			f = fopen(fich, "r");
				while ((a = fgetc(f)) != EOF){
					c++;
					fflush(stdout);
					if(a == '\n'){
						d++;
					}
				}
			fclose(f);
		char b[c+1];
		char delimi[] =";";
		Cliente *clientes = (Cliente*)malloc(sizeof(Cliente)*d);

		f = fopen(fich, "r");
		fgets(b,c+1,f);

		for (int k=0;k<d-1;k++){
			fgets(b,c+1,f);
			//1
			char *token = strtok(b,delimi);
			clientes[k].dni = malloc (sizeof(char) * (strlen(token)+1));
			strcpy(clientes[k].dni, token);
			//2
			token = strtok(NULL,delimi);
			clientes[k].nombre = malloc (sizeof(char) * (strlen(token)+1));
			strcpy(clientes[k].nombre, token);
			//3 int
			token = strtok(NULL,delimi);
			clientes[k].num_tarj = malloc(sizeof(char)*(strlen(token)+1));
			strcpy(clientes[k].num_tarj,token);
			//4
			token = strtok(NULL,delimi);
			clientes[k].pais = malloc (sizeof(char) * (strlen(token)+1));
			strcpy(clientes[k].pais, token);
			//5 int
			token = strtok(NULL,delimi);
			clientes[k].contrasena = (int) strtol(token,NULL,10);
			//6 int
			token = strtok(NULL,"\n");
			clientes[k].telf = (int) strtol(token,NULL,10);
			//PRUEBAS
			//printf("DNI: %s, Nombre: %s, NumTarj: %s, Pais: %s, Contrasena: %d, Telf: %d \n", clientes[k].dni,clientes[k].nombre,clientes[k].num_tarj,clientes[k].pais,clientes[k].contrasena,clientes[k].telf);
			}
		fclose(f);
		return clientes;

	}

Entrada* volcarEnt(char *fich){

	FILE *f;
			char a;
			int c = 0;
			int d = 0;

			f = fopen(fich, "r");
				while ((a = fgetc(f)) != EOF){
					c++;
					fflush(stdout);
					if(a == '\n'){
						d++;
					}
				}
			fclose(f);
		char b[c+1];
		char delimi[] =";";
		Entrada *entradas = (Entrada*)malloc(sizeof(Entrada)*d);

		f = fopen(fich, "r");
		fgets(b,c+1,f);

		for (int j=0;j<d-1;j++){
			fgets(b,c+1,f);
			//1 int
			char *token = strtok(b, delimi);
			entradas[j].cod_E = (int) strtol(token,NULL,10);
			//2 char
			token = strtok(NULL,delimi);
			entradas[j].dni = malloc (sizeof(char) * (strlen(token)+1));
			strcpy(entradas[j].dni, token);
			//3 int
			token = strtok(NULL,delimi);
			entradas[j].cod_pelicula = (int) strtol(token,NULL,10);
			//4 int
			token = strtok(NULL,delimi);
			entradas[j].sala = (int) strtol(token,NULL,10);
			//5 char
			token = strtok(NULL,delimi);
			entradas[j].hora = malloc (sizeof(char) * (strlen(token)+1));
			strcpy(entradas[j].hora, token);
			//6 int
			token = strtok(NULL,delimi);
			entradas[j].dia = (int) strtol(token,NULL,10);
			//7 int
			token = strtok(NULL,delimi);
			entradas[j].mes = (int) strtol(token,NULL,10);
			//8 int
			token = strtok(NULL,delimi);
			entradas[j].ano = (int) strtol(token,NULL,10);
			//9 int
			token = strtok(NULL,delimi);
			entradas[j].importe = (int) strtol(token,NULL,10);
			//10 int
			token = strtok(NULL,"\n");
			entradas[j].personas = (int) strtol(token,NULL,10);
			//PRUEBAS
			//printf("Cod_e: %d DNI: %s Cod_p: %d Sala: %d Hora: %s Dia: %d Mes: %d Ano: %d Importe: %d Personas: %d \n", entradas[j].cod_E, entradas[j].dni, entradas[j].cod_pelicula, entradas[j].sala, entradas[j].hora, entradas[j].dia, entradas[j].mes, entradas[j].ano, entradas[j].importe, entradas[j].personas);
			}
		fclose(f);
		return entradas;

	}

void libre(Pelicula *p, Cliente *cl, Entrada *e, Admin *a){
	free(p);
	free(cl);
	free(e);
	free(a);

}



