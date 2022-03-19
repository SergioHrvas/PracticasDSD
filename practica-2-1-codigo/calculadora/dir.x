
struct operacion {
	float firstparam; /* nombre de la entrada de directorio */
	float secondparam; /* siguiente entrada */
};

struct vector {
	int v<>;
}

struct 
/* la siguiente union se utiliza para discriminar entre llamadas con exito y llamadas con errores */
union tipo switch (int errno) {
	case 0:
		float resultado; /* sin error: listado del directorio */
	default:
		void; /* con error: nada */
};

program DIRPROG {
	version DIRVER {
		tipo SUMA(operacion) = 1;
		tipo RESTA(operacion) = 2;
		tipo MULTIPLICACION(operacion) = 3;
		tipo DIVISION(operacion) = 4;

	} =1;
} = 0x20000155;
