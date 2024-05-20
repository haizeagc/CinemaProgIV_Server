#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "estructuras.h"
#include "config.h"
#include "logger.h"
#include "sqlite3.h"
#include "baseDatos.h"
#define dirConf "configuraciones.config"

int main(int argc, char *argv[]){

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];
	HashMap confi;

	obtenerConfig(&confi);

	char* SERVER_IP = obtenerConfigConcreto(&confi, "serverIP");
	int SERVER_PORT = (int) strtol(obtenerConfigConcreto(&confi, "serverPort"), NULL, 10);

	iniciarLogger(obtenerConfigConcreto(&confi, "logger"));

	Arrays a;

	obtenerPeliculaBase(&a, &confi);
	obtenerClienteBase(&a, &confi);
	obtenerEntradaBase(&a, &confi);

	Cliente c;
	Entrada e;
	char *token;

	printf("\nInitialising ServerSocket...\n");
			logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Inicializando el socket del servidor.");
				if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
					printf("Failed. Error Code : %d", WSAGetLastError());
					logger_log(obtenerConfigConcreto(&confi,"logger"),"SEVERE","Error inicializado el socket server.");
					return -1;
				}
			printf("Initialised.\n");
			logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha inicializado el socket del servidor.");
			logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Creando socket.");
			if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
					printf("Could not create socket : %d", WSAGetLastError());
					logger_log(obtenerConfigConcreto(&confi,"logger"),"SEVERE","No se ha podido crear el socket.");
					WSACleanup();
					return -1;
				}

				printf("Socket created.\n");
				logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha creado el socket.");

				server.sin_addr.s_addr = inet_addr(SERVER_IP);
				server.sin_family = AF_INET;
				server.sin_port = htons(SERVER_PORT);

				//BIND (the IP/port with socket)
				if (bind(conn_socket, (struct sockaddr*) &server,sizeof(server)) == SOCKET_ERROR) {
					printf("Bind failed with error code: %d", WSAGetLastError());
					logger_log(obtenerConfigConcreto(&confi,"logger"),"SEVERE","El servidor no ha podido conectarse al cliente.");
					closesocket(conn_socket);
					WSACleanup();
					return -1;
				}
				printf("Bind done.\n");
				logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","El servidor se ha conectado al cliente.");

						//LISTEN to incoming connections (socket server moves to listening mode)
						if (listen(conn_socket, 1) == SOCKET_ERROR) {
							printf("Listen failed with error code: %d", WSAGetLastError());
							logger_log(obtenerConfigConcreto(&confi,"logger"),"SEVERE","No se ha podido conectar correctamente al modo listening.");
							closesocket(conn_socket);
							WSACleanup();
							return -1;
						}
						//ACCEPT incoming connections (server keeps waiting for them)
						printf("Waiting for incoming connections...\n");
						logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Esperando para obtener conexiones.");

						int stsize = sizeof(struct sockaddr);
						comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
						// Using comm_socket is able to send/receive data to/from connected client
						if (comm_socket == INVALID_SOCKET) {
							printf("accept failed with error code : %d", WSAGetLastError());
							logger_log(obtenerConfigConcreto(&confi,"logger"),"SEVERE","No se ha podido conectar correctamente con el client.");
							closesocket(conn_socket);
							WSACleanup();
							return -1;
						}
						printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),ntohs(client.sin_port));
						logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","El servidor se ha recibido una connexion");
						// Closing the listening sockets (is not going to be used anymore)
						closesocket(conn_socket);
						//SEND and RECEIVE data
						printf("Waiting for incoming commands from client... \n");
						logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Esperando para obtener informacion del cliente.");

							do
							{
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

								printf("Command received: %s \n", recvBuff);
								logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha obtenido un mensaje.");
								if (strcmp(recvBuff,"OBTAIN PELICULAS") == 0){
									char b[510];
									char c[100];
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido obtener peliculas.");
									for(int i = 0; i < a.cantidadPelicula; i++){
										sprintf(c,"%d",a.arrayPelicula[i].cod_pelicula);
										strcpy(b,c);
										strcat(b,",");
										strcat(b,a.arrayPelicula[i].nombre);
										strcat(b,",");
										strcat(b,a.arrayPelicula[i].genero);
										strcat(b,",");
										strcat(b,a.arrayPelicula[i].director);
										strcat(b,",");
										sprintf(b,a.arrayPelicula[i].hora);
										strcat(b,",");
										sprintf(c,"%d",a.arrayPelicula[i].sala);
										strcat(b,c);
										strcat(b,",");
										sprintf(c,"%d",a.arrayPelicula[i].precio);
										strcat(b,c);
										strcat(b,",");
										printf("%s\n",b);
										strcpy(sendBuff,b);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
										logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha enviado una pelicula.");

									}
									strcpy(sendBuff,"ALL PELICULAS SENT");
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha enviado todos las peliculas.");
								}
								if (strcmp(recvBuff,"OBTAIN CLIENTS") == 0){
									char d[510];
									char e[100];
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido obtener clientes.");
									for(int i = 0; i < a.cantidadCliente; i++){
										strcpy(d,a.arrayCliente[i].dni);
										strcat(d,",");
										strcat(d,a.arrayCliente[i].nombre);
										strcat(d,",");
										strcat(d,a.arrayCliente[i].num_tarj);
										strcat(d,",");
										strcat(d,a.arrayCliente[i].pais);
										strcat(d,",");
										sprintf(e,"%d",a.arrayCliente[i].contrasena);
										strcat(d,e);
										strcat(d,",");
										sprintf(e,"%d",a.arrayCliente[i].telf);
										strcat(d,e);
										strcat(d,",");
										strcat(d,",");
										printf("%s\n",d);
										strcpy(sendBuff,d);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
										logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha enviado un cliente.");
									}
									strcpy(sendBuff,"ALL CLIENTS SENT");
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se han enviado todos los clientes.");
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
								}
								if (strcmp(recvBuff,"OBTENER ENTRADAS") == 0){
									char d[510];
									char e[100];
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido obtener entrada.");
									for(int i = 0; i < a.cantidadEntrada; i++){
										sprintf(e,"%d",a.arrayEntrada[i].cod_E);
										strcat(d,e);
										strcat(d,",");
										strcpy(d,a.arrayEntrada[i].dni);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].cod_pelicula);
										strcat(d,e);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].sala);
										strcat(d,e);
										strcat(d,",");
										strcpy(d,a.arrayEntrada[i].hora);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].dia);
										strcat(d,e);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].mes);
										strcat(d,e);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].ano);
										strcat(d,e);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].importe);
										strcat(d,e);
										strcat(d,",");
										sprintf(e,"%d",a.arrayEntrada[i].cantidad);
										strcat(d,e);
										strcat(d,",");
										printf("%s\n",d);
										strcpy(sendBuff,d);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
										logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha enviado una entrada.");
									}
									strcpy(sendBuff,"TODAS LAS ENTRADAS ENVIADAS");
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se han enviado todas las entradas.");
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
								}
								if(strcmp(recvBuff,"REEMBOLSAR ENTRADA") == 0){
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido reembolsar una entrada.");
									do{
										recv(comm_socket,recvBuff,sizeof(recvBuff),0);
										if (strcmp(recvBuff,"ENTRADA A BORRAR ENVIADO") == 0){
												break;
										}
										token = strtok(recvBuff,",");
										char * dni = malloc(sizeof(char) *strlen(token)+1);
										strcpy(dni,token);
										token = strtok(NULL,",");
										int cod_peli = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										int codE = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										int sala = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										char * hora = malloc(sizeof(char) *strlen(token)+1);
										strcpy(hora,token);
										token = strtok(NULL,",");
										int dia = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										int mes = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										int ano = (int) strtol(token,NULL,10);
										borrarEntrada(dni,cod_peli, codE, sala, hora, dia, mes, ano, &confi);
									}while(1);
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha cancelado la entrada.");
								}
								if(strcmp(recvBuff,"HACER ENTRADA") == 0){
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido hacer una entrada.");
									do{
										recv(comm_socket,recvBuff,sizeof(recvBuff),0);
										if (strcmp(recvBuff,"ENTRADAS A ANADIR ENVIADAS") == 0){
												break;
										}
										token = strtok(recvBuff,",");
										e.dni = malloc(sizeof(char) *strlen(token)+1);
										strcpy(e.dni,token);
										token = strtok(NULL,",");
										e.cod_E = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.cod_pelicula = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.sala = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.hora = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(e.hora,token);
										token = strtok(NULL,",");
										e.dia = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.mes = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.ano = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.cantidad = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										e.importe = (int) strtol(token,NULL,10);
										subirEntradaBase(e,&confi);

									}while(1);
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha creado la entrada.");
								}

								if (strcmp(recvBuff, "NUEVO Cliente") == 0)
								{
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido anadir un cliente.");
									do{
										recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
										printf("%s \n",recvBuff);
										if (strcmp(recvBuff, "VALOR ENVIADO") == 0){
											break;
										}
										token = strtok(recvBuff,",");
										c.dni = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.dni,token);
										token = strtok(NULL,",");
										c.nombre = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.nombre,token);
										token = strtok(NULL,",");
										c.num_tarj = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.num_tarj,token);
										token = strtok(NULL,",");
										c.pais = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.pais,token);
										token = strtok(NULL,",");
										c.contrasena = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										c.telf = (int) strtol(token,NULL,10);
										subirClienteBase(&confi,c);

									} while(1);

								}
								if (strcmp(recvBuff, "UPDATE CLIENTE") == 0){
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido actualizar un cliente.");
									do{
										recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
										printf("%s \n",recvBuff);
										if (strcmp(recvBuff, "CLIENTE ACTUALIZADO") == 0){
											break;
												}
										token = strtok(recvBuff,",");
										c.dni = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.dni,token);
										token = strtok(NULL,",");
										c.nombre = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.nombre,token);
										token = strtok(NULL,",");
										c.num_tarj = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.num_tarj,token);
										token = strtok(NULL,",");
										c.pais = malloc (sizeof(char)*(strlen(token)+1));
										strcpy(c.pais,token);
										token = strtok(NULL,",");
										c.contrasena = (int) strtol(token,NULL,10);
										token = strtok(NULL,",");
										c.telf = (int) strtol(token,NULL,10);
										actuCliente(c.dni, c.nombre, c.num_tarj, c.pais, c.contrasena, c.telf,&confi);

										} while(1);
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha actualizado el cliente.");

								}
								if (strcmp(recvBuff, "BORRAR CLIENTE") == 0){
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha pedido borrar un cliente.");
									do{
										recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
										printf("%s \n",recvBuff);
										if (strcmp(recvBuff, "CLIENTE BORRADO") == 0){
											break;
												}
										c.dni = malloc (sizeof(char)*(strlen(recvBuff)+1));
										strcpy(c.dni,recvBuff);
										borrarClienteDni(c.dni, &confi);

										} while(1);
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha borrado el cliente.");

								}
								if (strcmp(recvBuff, "EXIT") == 0){
									logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se termina de enviar/recivir datos.");
									break;
								}

							} while (1);

							// CLOSING the sockets and cleaning socket...
							closesocket(comm_socket);
							logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha cerrado el socket.");
							WSACleanup();
							logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Se ha vaciado el socket.");
							logger_log(obtenerConfigConcreto(&confi,"logger"),"INFO","Fin del programa.");
							return 0;


}
