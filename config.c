/*
 * config.c
 *
 *  Created on: 27 mar 2024
 *
 */
#include "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void obtenerConfig(HashMap * hashMap){
	FILE *f;
	char *linea;
	char caracter;
	int cuentaCaracter = 0;
	int cuentaIguales = 0;
	int cuentaLineas = 0;
	f = fopen("configuraciones.config","r");
		while((caracter = fgetc(f)) != EOF){
			cuentaCaracter++;
			if (caracter == '='){
				cuentaIguales++;
			}
			if (caracter == '\n'){
				cuentaLineas++;
			}
		}
	fclose(f);
	linea = (char*)malloc(sizeof(char)*cuentaCaracter);
	hashMap->map = (entry*)malloc(sizeof(entry)*cuentaIguales);
	hashMap->size = cuentaIguales;
	f = fopen("configuraciones.config","r");
	cuentaIguales = 0;
	for(int i = 0; i < cuentaLineas; i++){
		fgets(linea,"%s",f);
		int esUnProperty = 0;
		for(int j = 0; j < strlen(linea);j++){
			if(linea[j] == '='){
				esUnProperty = 1;
			}
		}
		if (esUnProperty == 1){
			char *token = strtok(linea,"=");
			hashMap->map[cuentaIguales].key = malloc(sizeof(char)*(strlen(token)+1));
			strcpy(hashMap->map[cuentaIguales].key,token);
			token = strtok(NULL,"\n");
			hashMap->map[cuentaIguales].value = malloc(sizeof(char)*(strlen(token)+1));
			strcpy(hashMap->map[cuentaIguales].value,token);
			cuentaIguales++;
		}
	}
	free(linea);
	//printf("cuentaCaracter = %i, cuentaIguales = %i,cuenta Lineas = %i\n",cuentaCaracter,cuentaIguales,cuentaLineas);
}


char* obtenerConfigConcreto(HashMap* hashMap,char *key){
	char* resultado;
	for(int i = 0; i < hashMap->size; i++){
		if(strcmp(hashMap->map[i].key,key)==0){
			resultado = (char*)malloc(sizeof(char)*(strlen(hashMap->map[i].value)+1));
			strcpy(resultado,hashMap->map[i].value);
		}
	}
	return resultado;
}
