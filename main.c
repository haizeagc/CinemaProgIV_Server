#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "administrador.h"
#include "estructuras.h"
#include "config.h"
#include "info.h"
#include "logger.h"
#include "sqlite3.h"
#include "baseDatos.h"

int main(void){

	HashMap configu;
	obtenerConfig(&configu);
	int elecccion = (int) strtol(obtenerConfigConcreto(&configu, "reinicio"), NULL, 10);
	if (elecccion == 1){
		reiniciar(&configu);
		subirPeliculaBase(&configu);
		subirClienteBase(&configu);
		subirEntradaBase(&configu);
		subirAdminBase(&configu);
	}
	iniciarLogger(obtenerConfigConcreto(&configu, "logger"));
	Arrays a;

	obtenerPeliculaBase(&a, &configu);
	obtenerClienteBase(&a, &configu);
	obtenerEntradaBase(&a, &configu);
	obtenerAdminBase(&a, &configu);

	starting(&a,&configu);

	fflush(stdout);

	return 0;

}
