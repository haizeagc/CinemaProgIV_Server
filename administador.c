#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "administrador.h"
#include "logger.h"
#include "baseDatos.h"
#include "estructuras.h"

//REVISADO
void starting(Arrays *arrays, HashMap *confi){
	logger_log(obtenerConfigConcreto(confi, "logger"), "INFO", "Comienza el programa.");
	printf("----------------------------------------\n");
	printf("BIENVENIDO AL PROGRAMA DE ADMINISTRACION \n");
	printf("----------------------------------------\n");
	printf("Opciones:\n");
	printf("1. Iniciar Sesion\n");
	printf("2. Salir\n");
	printf("Intruduzca el numero de la opcion: ");
	fflush(stdout);
	int a;
	scanf("%d", &a);
	consumirNuevaLinea();
	if (a == 1){
		iniciarSesion(arrays, confi);
	}else if (a == 2){
		liberar(arrays, confi);
	}else{
		starting(arrays, confi);
	}
}
//REVISADO
void iniciarSesion(Arrays *arrays, HashMap *confi){
	logger_log(obtenerConfigConcreto(confi, "logger"), "INFO", "Se ha iniciado la sesion.");

	char c[22];
	int a;
	int er1 = 0;
	int er2 = 0;

	printf("----------------------------------------\n");
	printf("INICIAR SESION\n");
	printf("----------------------------------------\n");
	printf("Introduce el usuario: ");
	fflush(stdout);
	scanf("%s", c);
	consumirNuevaLinea();
	printf("Introduce la contrasena: ");
	fflush(stdout);
	scanf("%d",&a);
	consumirNuevaLinea();

	for (int i=0; i< arrays->cantidadAdmin; i++){
		if(0 == strcmp(arrays->arrayAdmin[i].usuario, c)){
			er1 = 1;
			if (a == arrays->arrayAdmin[i].contrasena){
				er2 = 1;
				hacer(arrays, confi);
			}
		}
	}
	if (er1 == 0){
		printf("Este usuario no existe\n");
		logger_log(obtenerConfigConcreto(confi, "logger"), "WARNING", "Este usuario no existe.");
		iniciarSesion(arrays, confi);
	}else if (er2 == 0){
		printf("La contraseña no es correcta\n");
		logger_log(obtenerConfigConcreto(confi, "logger"), "INFO", "La contraseña no es correcta.");
		iniciarSesion(arrays, confi);
	}
}
//REVISADO
void consumirNuevaLinea(){
	int l;
	do{
		l = getchar();
	} while (l != EOF && l !='\n');

}
//REVISADO
void hacer(Arrays *arrays, HashMap *confi){
	int b;
	logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","Se ha abierto el menu de administracion.");
	printf("----------------------------------------\n");
	printf("ADMINISTRADOR \n");
	printf("----------------------------------------\n");
	printf("1. Gestionar Administradores\n");
	printf("2. Gestionar Peliculas\n");
	printf("3. Gestionar Entradas\n");
	printf("4. Gestionar Clientes\n");
	printf("5. Cerrar sesion\n");
	printf("Intruduzca el numero de la opcion: ");
	fflush(stdout);
	scanf("%d",&b);
	consumirNuevaLinea();
	printf("----------------------------------------\n");
	if (b == 1){
		gestionAdmin(arrays,confi);
	}else if (b == 2){
		gestionPeli(arrays,confi);
	}else if (b == 3){
		gestionEnt(arrays,confi);
	}else if(b == 4){
		gestionCli(arrays,confi);
	}else if(b == 5){
		liberar(arrays,confi);
	}else{
		hacer(arrays,confi);
	}

}

//GESTION
//REVISADO
void gestionAdmin(Arrays *arrays, HashMap *confi){
	logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","Se ha abierto el menu de gestionar administrador.");
	int b;
	printf("----------------------------------------\n");
	printf("GESTION DE ADMINISTRADOR\n");
	printf("----------------------------------------\n");
	printf("Lista de Administradores:\n");
	for (int i= 0; i < arrays->cantidadAdmin; ++i) {
		printf("Administrador %i: %s\n",(i+1),arrays->arrayAdmin[i].usuario);
		}
	printf("1. Anadir Administrador\n");
	printf("2. Borrar Administrador\n");
	printf("3. Volver al menu\n");
	printf("Intruduzca el numero de la opcion: ");
	fflush(stdout);
	scanf("%d",&b);
	consumirNuevaLinea();
	printf("----------------------------------------\n");
	fflush(stdout);
	if(b == 1){
		aniadirAdmin(arrays,confi);
	}else if(b == 2){
		eliminarAdmin(arrays,confi);
	}else if(b == 3){
		hacer(arrays,confi);
	}else{
		gestionAdmin(arrays,confi);
		}

}

//REVISADO
void gestionPeli(Arrays *arrays, HashMap *confi){
	logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","Se ha abierto el menu de gestionar peliculas.");
	int b;
	printf("----------------------------------------\n");
	printf("GESTION DE PELICULAS\n");
	printf("----------------------------------------\n");
	printf("Lista de Peliculas:\n");
	for (int i= 0; i < arrays->cantidadPelicula; ++i) {
		printf("Pelicula %i: Cod: %d, Nombre: %s, Genero: %s, Director: %s, Hora: %s, Sala: %d, Precio: %d \n",(i+1),arrays->arrayPelicula[i].cod_pelicula, arrays->arrayPelicula[i].nombre, arrays->arrayPelicula[i].genero, arrays->arrayPelicula[i].director, arrays->arrayPelicula[i].hora, arrays->arrayPelicula[i].sala, arrays->arrayPelicula[i].precio);
		}
	printf("1. Anadir Pelicula\n");
	printf("2. Borrar Pelicula\n");
	printf("3. Volver al menu\n");
	printf("Intruduzca el numero de la opcion: ");
	fflush(stdout);
	scanf("%d",&b);
	consumirNuevaLinea();
	printf("----------------------------------------\n");
	fflush(stdout);
	if(b == 1){
		aniadirPeli(arrays,confi);
	}else if(b == 2){
		eliminarPeli(arrays,confi);
	}else if(b == 3){
		hacer(arrays,confi);
	}else{
		gestionPeli(arrays,confi);
		}
}

//REVISADO
void gestionCli(Arrays *arrays, HashMap *confi){
	logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","Se ha abierto el menu de gestionar clientes.");
		int b;
		printf("----------------------------------------\n");
		printf("GESTION DE CLIENTES\n");
		printf("----------------------------------------\n");
		printf("Lista de clientes:\n");
		for (int i= 0; i < arrays->cantidadCliente; ++i) {
			printf("Cliente %i: DNI: %s, Nombre: %s, Pais: %s, Telf: %d \n",(i+1),arrays->arrayCliente[i].dni,arrays->arrayCliente[i].nombre,arrays->arrayCliente[i].pais,arrays->arrayCliente[i].telf);
			}
		printf("1. Borrar Cliente\n");
		printf("2. Volver al menu\n");
		printf("Intruduzca el numero de la opcion: ");
		fflush(stdout);
		scanf("%d",&b);
		consumirNuevaLinea();
		printf("----------------------------------------\n");
		fflush(stdout);
		if(b == 1){
			eliminarCli(arrays,confi);
		}else if(b == 2){
			hacer(arrays,confi);
		}else{
			gestionCli(arrays,confi);
			}
}

//REVISADO
void gestionEnt(Arrays *arrays, HashMap *confi){
	logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","Se ha abierto el menu de gestionar entradas.");
		int b;
		printf("----------------------------------------\n");
		printf("GESTION DE ENTRADAS\n");
		printf("----------------------------------------\n");
		printf("Lista de entradas:\n");
		for (int k= 0; k< arrays->cantidadEntrada; ++k) {
			printf("Entrada %i Cod.Entr: %d, Dni: %s, Cod.Pel: %d Fecha: %i-%i-%i|%s Sala:%i \n",(k+1),arrays->arrayEntrada[k].cod_E,arrays->arrayEntrada[k].dni,arrays->arrayEntrada[k].cod_pelicula,arrays->arrayEntrada[k].dia,arrays->arrayEntrada[k].mes,arrays->arrayEntrada[k].ano,arrays->arrayEntrada[k].hora,arrays->arrayEntrada[k].sala);
			}
		printf("1. Borrar Entrada\n");
		printf("2. Volver al menu\n");
		printf("Intruduzca el numero de la opcion: ");
		fflush(stdout);
		scanf("%d",&b);
		consumirNuevaLinea();
		printf("----------------------------------------\n");
		fflush(stdout);
		if(b == 1){
			eliminarEnt(arrays,confi);
		}else if(b == 2){
			hacer(arrays,confi);
		}else{
			gestionEnt(arrays,confi);
			}
}

//ELIMINAR

void eliminarAdmin(Arrays *arrays, HashMap *confi){
	char Usuario[22];
	char confir[3];
	Admin* arrayAdmin;
	int j = 0;
	printf("----------------------------------------\n");
	printf("BORRAR ADMINISTRADOR\n");
	printf("----------------------------------------\n");
	printf("Introduce Usuario a borrar (para cancelar introducir 0):");
	fflush(stdout);
	scanf("%s",Usuario);
	consumirNuevaLinea();
	if (Usuario[0] == '0'){
		hacer(arrays,confi);
		}
	printf("Estas seguro? S/N ");
	fflush(stdout);
	scanf("%s",confir);
	consumirNuevaLinea();
	if (strcmp(confir,"S") == 0 || strcmp(confir,"s") == 0){
		int esta = 0;
		for(int i = 0; i < arrays->cantidadAdmin; i++){
			if(strcmp(arrays->arrayAdmin[i].usuario,Usuario) == 0){
					esta = 1;
				}
			}
			if (esta == 1){
				borrarAdminBase(Usuario,confi);
				arrayAdmin = (Admin*) malloc(sizeof(Admin)*(arrays->cantidadAdmin - 1));
				for (int i = 0;i < arrays->cantidadAdmin; ++i){
					if (strcmp(arrays->arrayAdmin[i].usuario,Usuario) != 0) {
						arrayAdmin[j].usuario = (char*) malloc(sizeof(char)*(strlen(arrays->arrayAdmin[i].usuario)+1));
						strcpy(arrayAdmin[j].usuario,arrays->arrayAdmin[i].usuario);
						arrayAdmin[j].contrasena = arrays->arrayAdmin[i].contrasena;
						j++;
						}
					}
				free(arrays->arrayAdmin);
				arrays->cantidadAdmin--;
				arrays->arrayAdmin = (Admin*) malloc(sizeof(Admin)*(arrays->cantidadAdmin));
				for(int i = 0;i< arrays->cantidadAdmin; i++){
						arrays->arrayAdmin[i].usuario = (char*) malloc(sizeof(char)*(strlen(arrayAdmin[i].usuario)+1));
						strcpy(arrays->arrayAdmin[i].usuario,arrayAdmin[i].usuario);
						arrays->arrayAdmin[i].contrasena = arrayAdmin->contrasena;
				}
				for(int i = 0; i < arrays->cantidadAdmin;i++){
					free(arrayAdmin[i].usuario);
				}
				free(arrayAdmin);
				}else if(esta == 0){
					logger_log(obtenerConfigConcreto(confi,"logger"),"WARNING","El administrador que se quiere borrar no existe.");
							printf("El administrador que se quiere borrar no existe\n");
				}

			}
			printf("---------------------------------------\n");
			gestionAdmin(arrays,confi);

}
void eliminarPeli(Arrays *arrays, HashMap *confi){
	int cod_pel;
	char confir[3];
	Pelicula* arrayPelicula;
	int j = 0;

	printf("----------------------------------------\n");
	printf("BORRAR PELICULA:\n");
	printf("----------------------------------------\n");
	printf("Introduce el codigo de la Pelicula a borrar (para cancelar introducir 0):");
	fflush(stdout);
	scanf("%d",&cod_pel);
	consumirNuevaLinea();
	printf("Estas seguro? S/N ");
	fflush(stdout);
	scanf("%s",confir);
	consumirNuevaLinea();
	if (strcmp(confir,"S") == 0 || strcmp(confir,"s") == 0){
		int esta = 0;
		for(int i = 0; i < arrays->cantidadPelicula; i++){
			if(cod_pel == arrays->arrayPelicula[i].cod_pelicula){
					esta = 1;
			}
		}
		if (esta == 1){
			borrarPeliculaBase(cod_pel, confi);
			arrayPelicula = (Pelicula*) malloc(sizeof(Pelicula)*(arrays->cantidadPelicula - 1));
			for (int i = 0;i < arrays->cantidadPelicula; ++i){
				if (cod_pel != arrays->arrayPelicula[i].cod_pelicula) {
					arrayPelicula[j].cod_pelicula = arrays->arrayPelicula[i].cod_pelicula;
					arrayPelicula[j].nombre = (char*) malloc(sizeof(char)*(strlen(arrays->arrayPelicula[i].nombre)+1));
					strcpy(arrayPelicula[j].nombre,arrays->arrayPelicula[i].nombre);
					arrayPelicula[j].director = (char*) malloc(sizeof(char)*(strlen(arrays->arrayPelicula[i].director)+1));
					strcpy(arrayPelicula[j].director,arrays->arrayPelicula[i].director);
					arrayPelicula[j].genero = (char*) malloc(sizeof(char)*(strlen(arrays->arrayPelicula[i].genero)+1));
					strcpy(arrayPelicula[j].genero,arrays->arrayPelicula[i].genero);
					arrayPelicula[j].hora = (char*) malloc(sizeof(char)*(strlen(arrays->arrayPelicula[i].hora)+1));
					strcpy(arrayPelicula[j].hora,arrays->arrayPelicula[i].hora);
					arrayPelicula[j].precio = arrays->arrayPelicula[i].precio;
					arrayPelicula[j].sala = arrays->arrayPelicula[i].sala;
					j++;
				}
			}
			free(arrays->arrayPelicula);
			arrays->cantidadPelicula--;
			arrays->arrayPelicula = (Pelicula*) malloc(sizeof(Pelicula)*(arrays->cantidadPelicula));
				for(int i = 0;i< arrays->cantidadPelicula; i++){
					arrays->arrayPelicula[i].cod_pelicula = arrayPelicula[i].cod_pelicula;
					arrays->arrayPelicula[i].nombre = (char*) malloc(sizeof(char)*(strlen(arrayPelicula[i].nombre)+1));
					strcpy(arrays->arrayPelicula[i].nombre,arrayPelicula[i].nombre);
					arrays->arrayPelicula[i].director = (char*) malloc(sizeof(char)*(strlen(arrayPelicula[i].director)+1));
					strcpy(arrays->arrayPelicula[i].director,arrayPelicula[i].director);
					arrays->arrayPelicula[i].genero = (char*)malloc(sizeof(char)*(strlen(arrayPelicula[i].genero)+1));
					strcpy(arrays->arrayPelicula[i].genero,arrayPelicula[i].genero);
					arrays->arrayPelicula[i].hora = (char*)malloc(sizeof(char)*(strlen(arrayPelicula[i].hora)+1));
					strcpy(arrays->arrayPelicula[i].hora,arrayPelicula[i].hora);
					arrays->arrayPelicula[i].precio = arrayPelicula[i].precio;
					arrays->arrayPelicula[i].sala = arrayPelicula[i].sala;
			}
			for(int i = 0; i < arrays->cantidadPelicula;i++){
				free(arrayPelicula[i].nombre);
				free(arrayPelicula[i].director);
				free(arrayPelicula[i].genero);
				free(arrayPelicula[i].hora);
			}
			free(arrayPelicula);
			}else if(esta == 0){
				logger_log(obtenerConfigConcreto(confi,"logger"),"WARNING","La pelicula que se quiere borrar no existe.");
				printf("La pelicula que se quiere borrar no existe\n");
			}

		}
		printf("---------------------------------------\n");
		gestionPeli(arrays,confi);

}

void eliminarCli(Arrays *arrays, HashMap *confi){
	char cli[20];
	char confir[3];
	Cliente* arrayCliente;
	int j = 0;

	printf("----------------------------------------\n");
	printf("BORRAR CLIENTE\n");
	printf("----------------------------------------\n");
	printf("Introduce el DNI del cliente a borrar (para cancelar introducir 0):");
	fflush(stdout);
	scanf("%s",cli);
	consumirNuevaLinea();
	if (cli[0] == '0'){
		hacer(arrays,confi);
		}
	printf("Estas seguro? S/N ");
	fflush(stdout);
	scanf("%s",confir);
	consumirNuevaLinea();
	if (strcmp(confir,"S") == 0 || strcmp(confir,"s") == 0){
		int esta = 0;
		for(int i = 0; i < arrays->cantidadCliente; i++){
			if(strcmp(arrays->arrayCliente[i].dni,cli) == 0){
				esta = 1;
			}
		}
        if (esta == 1) {
            borrarClienteBase(cli, confi);
            arrayCliente = (Cliente*)malloc(sizeof(Cliente) * (arrays->cantidadCliente - 1));
            for (int i = 0; i < arrays->cantidadCliente; ++i) {
                if (strcmp(arrays->arrayCliente[i].dni, cli) != 0) {
                    arrayCliente[j].nombre = strdup(arrays->arrayCliente[i].nombre);
                    arrayCliente[j].contrasena = arrays->arrayCliente[i].contrasena;
                    arrayCliente[j].telf = arrays->arrayCliente[i].telf;
                    arrayCliente[j].dni = strdup(arrays->arrayCliente[i].dni);
                    arrayCliente[j].num_tarj = strdup(arrays->arrayCliente[i].num_tarj);
                    arrayCliente[j].pais = strdup(arrays->arrayCliente[i].pais);
                    j++;
                }
            }
            free(arrays->arrayCliente);
            arrays->cantidadCliente--;
            arrays->arrayCliente = (Cliente*)malloc(sizeof(Cliente) * (arrays->cantidadCliente));
            for (int i = 0; i < arrays->cantidadCliente; i++) {
                arrays->arrayCliente[i].dni = strdup(arrayCliente[i].dni);
                arrays->arrayCliente[i].nombre = strdup(arrayCliente[i].nombre);
                arrays->arrayCliente[i].pais = strdup(arrayCliente[i].pais);
                arrays->arrayCliente[i].num_tarj = strdup(arrayCliente[i].num_tarj);
                arrays->arrayCliente[i].contrasena = arrayCliente[i].contrasena;
                arrays->arrayCliente[i].telf = arrayCliente[i].telf;
            }
            for (int i = 0; i < arrays->cantidadCliente; i++) {
                free(arrayCliente[i].nombre);
                free(arrayCliente[i].dni);
                free(arrayCliente[i].num_tarj);
                free(arrayCliente[i].pais);
            }
            free(arrayCliente);
        } else {
            logger_log(obtenerConfigConcreto(confi, "logger"), "WARNING", "El cliente que se quiere borrar no existe.");
            printf("El cliente que se quiere borrar no existe\n");
        }
    }
    printf("---------------------------------------\n");
    gestionCli(arrays, confi);
}
void eliminarEnt(Arrays *arrays, HashMap *confi){
		int cod_e;
		char confir[3];
		Entrada* arrayEntrada;
		int j = 0;

		printf("----------------------------------------\n");
		printf("BORRAR ENTRADA\n");
		printf("----------------------------------------\n");
		printf("Introduce el codigo de la entrada a borrar (para cancelar introducir 0):");
		fflush(stdout);
		scanf("%d",&cod_e);
		consumirNuevaLinea();
		if (cod_e == 0){
			hacer(arrays,confi);
			}
		printf("Estas seguro? S/N ");
		fflush(stdout);
		scanf("%s",confir);
		consumirNuevaLinea();
		if (strcmp(confir,"S") == 0 || strcmp(confir,"s") == 0){
			int esta = 0;
			for(int i = 0; i < arrays->cantidadEntrada; i++){
				if(cod_e == arrays->arrayEntrada[i].cod_E){
					esta = 1;
				}
			}
			if (esta == 1){
			            borrarEntradaBase(cod_e, confi);
			            arrayEntrada = (Entrada*) malloc(sizeof(Entrada) * (arrays->cantidadEntrada - 1));

			            for (int i = 0; i < arrays->cantidadEntrada; ++i){
			                if (cod_e != arrays->arrayEntrada[i].cod_E) {
			                    arrayEntrada[j].cod_E = arrays->arrayEntrada[i].cod_E;
			                    arrayEntrada[j].dni = strdup(arrays->arrayEntrada[i].dni);
			                    arrayEntrada[j].cod_pelicula = arrays->arrayEntrada[i].cod_pelicula;
			                    arrayEntrada[j].sala = arrays->arrayEntrada[i].sala;
			                    arrayEntrada[j].hora = strdup(arrays->arrayEntrada[i].hora);
			                    arrayEntrada[j].dia = arrays->arrayEntrada[i].dia;
			                    arrayEntrada[j].mes = arrays->arrayEntrada[i].mes;
			                    arrayEntrada[j].ano = arrays->arrayEntrada[i].ano;
			                    arrayEntrada[j].importe = arrays->arrayEntrada[i].importe;
			                    arrayEntrada[j].personas = arrays->arrayEntrada[i].personas;
			                    j++;
			                }
			            }

			            free(arrays->arrayEntrada);
			            arrays->cantidadEntrada--;
			            arrays->arrayEntrada = (Entrada*) malloc(sizeof(Entrada) * (arrays->cantidadEntrada));

			            for(int i = 0; i < arrays->cantidadEntrada; i++){
			                arrays->arrayEntrada[i].cod_E = arrayEntrada[i].cod_E;
			                arrays->arrayEntrada[i].dni = strdup(arrayEntrada[i].dni);
			                arrays->arrayEntrada[i].cod_pelicula = arrayEntrada[i].cod_pelicula;
			                arrays->arrayEntrada[i].sala = arrayEntrada[i].sala;
			                arrays->arrayEntrada[i].hora = strdup(arrayEntrada[i].hora);
			                arrays->arrayEntrada[i].dia = arrayEntrada[i].dia;
			                arrays->arrayEntrada[i].mes = arrayEntrada[i].mes;
			                arrays->arrayEntrada[i].ano = arrayEntrada[i].ano;
			                arrays->arrayEntrada[i].importe = arrayEntrada[i].importe;
			                arrays->arrayEntrada[i].personas = arrayEntrada[i].personas;
			            }

			            for(int i = 0; i < arrays->cantidadEntrada; i++){
			                free(arrayEntrada[i].dni);
			                free(arrayEntrada[i].hora);
			            }

			            free(arrayEntrada);
			        } else if(esta == 0){
			            logger_log(obtenerConfigConcreto(confi, "logger"), "WARNING", "La entrada que se quiere borrar no existe.");
			            printf("La entrada que se quiere borrar no existe\n");
			        }
			    }

			    printf("---------------------------------------\n");
			    gestionEnt(arrays, confi);
			}

//AÑADIR

void aniadirAdmin(Arrays *arrays, HashMap *confi){
	char Usu[20];
	int contrasena;
	char confir[3];
	Admin* arrayAdmin;
	printf("----------------------------------------\n");
	printf("AÑADIR ADMINISTRADOR\n");
	printf("----------------------------------------\n");
	printf("Introduce Nuevo Usuario:");
	fflush(stdout);
	scanf("%s",Usu);
	consumirNuevaLinea();
	printf("Introduce Nueva Contraseña:");
	fflush(stdout);
	scanf("%d",&contrasena);
	consumirNuevaLinea();
	printf("Estas seguro? S/N ");
	fflush(stdout);
	scanf("%s",confir);
	consumirNuevaLinea();
	if (strcmp(confir,"S") == 0 || strcmp(confir,"s") == 0){
		int error1 = 0;
		int error2 = 0;
		for (int i = 0; i < arrays->cantidadAdmin; i++){
			if(strcmp(Usu,arrays->arrayAdmin[i].usuario) == 0){
				error1 = 1;
				}
			if (contrasena == arrays->arrayAdmin[i].contrasena){
				error2 = 1;
				}
			}
			if ((error1 + error2) == 2){
				printf("El usuario ya existe\n");
				logger_log(obtenerConfigConcreto(confi,"logger"),"WARNING","El administrador a anadir ya existe.");
				aniadirAdmin(arrays,confi);
			}else if(error1 == 1){
				logger_log(obtenerConfigConcreto(confi,"logger"),"WARNING","El nombre de administrador a anadir ya ha sido utilizado.");
				printf("El nombre del usuario ya ha sido utilizado\n");
				aniadirAdmin(arrays,confi);
			}else if(error2 == 1){
				logger_log(obtenerConfigConcreto(confi,"logger"),"WARNING","La contrasena de administrador a anadir ya ha sido utilizada.");
				printf("La contrasena no es valida porque alguno de los administradores ya la usa\n");
				aniadirAdmin(arrays,confi);
			} else {
				anadirAdminBase(Usu,contrasena,confi);
				arrayAdmin = (Admin*) malloc(sizeof(Admin)*(arrays->cantidadAdmin + 1));
			for (int i = 0; i < arrays->cantidadAdmin; ++i){
				arrayAdmin[i].usuario = (char*) malloc(sizeof(char)*(strlen(arrays->arrayAdmin[i].usuario)+1));
				strcpy(arrayAdmin[i].usuario,arrays->arrayAdmin[i].usuario);
				arrayAdmin[i].contrasena = arrays->arrayAdmin[i].contrasena;
				}
			free(arrays->arrayAdmin);
			arrayAdmin[arrays->cantidadAdmin].usuario = (char*) malloc(sizeof(char)*(strlen(Usu)+1));
			strcpy(arrayAdmin[arrays->cantidadAdmin].usuario,Usu);
			arrayAdmin[arrays->cantidadAdmin].contrasena = contrasena;
			arrays->cantidadAdmin++;
			arrays->arrayAdmin = (Admin*) malloc(sizeof(Admin)*(arrays->cantidadAdmin));
			for (int i = 0; i < arrays->cantidadAdmin; i++){
				arrays->arrayAdmin[i].usuario = (char*) malloc(sizeof(char)*(strlen(arrayAdmin[i].usuario)+1));
				strcpy(arrays->arrayAdmin[i].usuario,arrayAdmin[i].usuario);
				for(int i = 0; i < arrays->cantidadAdmin;i++){
					free(arrayAdmin[i].usuario);
				}
				free(arrayAdmin);
				}
			hacer(arrays,confi);
			}

	} else {
		hacer(arrays,confi);
	}

}

void aniadirPeli(Arrays *arrays, HashMap *confi){
    int cod;
    char nombre[20];
    char genero[20];
    char director[20];
    char time[20];
    int sala;
    int precio = 10;
    char confir[3];

    Pelicula* arrayPelicula;

    printf("----------------------------------------\n");
    printf("AÑADIR PELICULA\n");
    printf("----------------------------------------\n");
    printf("Introduce Codigo:");
    fflush(stdout);
    scanf("%d", &cod);
    consumirNuevaLinea();

    printf("Introduce nombre:");
    fflush(stdout);
    scanf("%s", nombre);
    consumirNuevaLinea();

    printf("Introduce genero:");
    fflush(stdout);
    scanf("%s", genero);
    consumirNuevaLinea();

    printf("Introducir director:");
    fflush(stdout);
    scanf("%s", director);
    consumirNuevaLinea();

    printf("Introduce hora:");
    fflush(stdout);
    scanf("%s", time);
    consumirNuevaLinea();

    printf("Introduce sala:");
    fflush(stdout);
    scanf("%d", &sala);
    consumirNuevaLinea();

    printf("Estas seguro? S/N ");
    fflush(stdout);
    scanf("%s", confir);
    consumirNuevaLinea();

    if (strcmp(confir, "S") == 0 || strcmp(confir, "s") == 0) {
        int error1 = 0;
        int error2 = 0;

        for (int i = 0; i < arrays->cantidadAdmin; i++) {
            if (strcmp(nombre, arrays->arrayPelicula[i].nombre) == 0) {
                error1 = 1;
            }
            if (cod == arrays->arrayPelicula[i].cod_pelicula) {
                error2 = 1;
            }
        }

        if ((error1 + error2) == 2) {
            printf("La Pelicula ya existe\n");
            logger_log(obtenerConfigConcreto(confi, "logger"), "WARNING", "La pelicula a anadir ya existe.");
            hacer(arrays, confi);
        } else if (error1 == 1) {
            logger_log(obtenerConfigConcreto(confi, "logger"), "WARNING", "El nombre de la pelicula a anadir ya ha sido utilizado.");
            printf("El nombre de la pelicula ya ha sido utilizado\n");
            hacer(arrays, confi);
        } else if (error2 == 1) {
            logger_log(obtenerConfigConcreto(confi, "logger"), "WARNING", "El codigo de la pelicula a anadir ya ha sido utilizada.");
            printf("EL codigo de la pelicula no es valida porque alguna pelicula ya la usa\n");
            hacer(arrays, confi);
        } else {
            anadirPeliculaBase(cod, nombre, genero, director, time, sala, precio, confi);
            arrayPelicula = (Pelicula*) malloc(sizeof(Pelicula) * (arrays->cantidadPelicula + 1));

            for (int i = 0; i < arrays->cantidadPelicula; ++i) {
                arrayPelicula[i].cod_pelicula = arrays->arrayPelicula[i].cod_pelicula;
                arrayPelicula[i].nombre = strdup(arrays->arrayPelicula[i].nombre);
                arrayPelicula[i].genero = strdup(arrays->arrayPelicula[i].genero);
                arrayPelicula[i].director = strdup(arrays->arrayPelicula[i].director);
                arrayPelicula[i].hora = strdup(arrays->arrayPelicula[i].hora);
                arrayPelicula[i].sala = arrays->arrayPelicula[i].sala;
                arrayPelicula[i].precio = arrays->arrayPelicula[i].precio;
            }

            arrayPelicula[arrays->cantidadPelicula].cod_pelicula = cod;
            arrayPelicula[arrays->cantidadPelicula].nombre = strdup(nombre);
            arrayPelicula[arrays->cantidadPelicula].genero = strdup(genero);
            arrayPelicula[arrays->cantidadPelicula].director = strdup(director);
            arrayPelicula[arrays->cantidadPelicula].hora = strdup(time);
            arrayPelicula[arrays->cantidadPelicula].sala = sala;
            arrayPelicula[arrays->cantidadPelicula].precio = precio;

            free(arrays->arrayPelicula);
            arrays->cantidadPelicula++;
            arrays->arrayPelicula = (Pelicula*) malloc(sizeof(Pelicula) * (arrays->cantidadPelicula));

            for (int i = 0; i < arrays->cantidadPelicula; i++) {
                arrays->arrayPelicula[i].cod_pelicula = arrayPelicula[i].cod_pelicula;
                arrays->arrayPelicula[i].nombre = strdup(arrayPelicula[i].nombre);
                arrays->arrayPelicula[i].genero = strdup(arrayPelicula[i].genero);
                arrays->arrayPelicula[i].director = strdup(arrayPelicula[i].director);
                arrays->arrayPelicula[i].hora = strdup(arrayPelicula[i].hora);
                arrays->arrayPelicula[i].sala = arrayPelicula[i].sala;
                arrays->arrayPelicula[i].precio = arrayPelicula[i].precio;
            }

            for (int i = 0; i < arrays->cantidadPelicula; i++) {
                free(arrayPelicula[i].nombre);
                free(arrayPelicula[i].director);
                free(arrayPelicula[i].genero);
                free(arrayPelicula[i].hora);
            }
            free(arrayPelicula);
        }
    }
    hacer(arrays, confi);
}

void liberar(Arrays *arrays, HashMap *confi){
	for(int i = 0; i < arrays->cantidadAdmin; i++){
			free(arrays->arrayAdmin[i].usuario);
		}
		free(arrays->arrayAdmin);
		logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","El ArrayAdmin ha sido liberado.");

		for(int i = 0; i < arrays->cantidadEntrada; i++){
			free(arrays->arrayEntrada[i].dni);
			free(arrays->arrayEntrada[i].hora);
		}
		free(arrays->arrayEntrada);
		logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","El ArrayEntrada ha sido liberado.");

		for(int i = 0; i < arrays->cantidadCliente; i++){
			free(arrays->arrayCliente[i].dni);
			free(arrays->arrayCliente[i].nombre);
			free(arrays->arrayCliente[i].pais);
			free(arrays->arrayCliente[i].num_tarj);
		}
		free(arrays->arrayCliente);
		logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","El ArrayCliente ha sido liberado.");

		for(int i = 0; i < arrays->cantidadPelicula; i++){
			free(arrays->arrayPelicula[i].nombre);
			free(arrays->arrayPelicula[i].genero);
			free(arrays->arrayPelicula[i].director);
			free(arrays->arrayPelicula[i].hora);
		}
		free(arrays->arrayPelicula);
		logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","El ArrayPelicula ha sido liberado.");
		logger_log(obtenerConfigConcreto(confi,"logger"),"INFO","Fin de el programa.");
		exit(-1);

}
