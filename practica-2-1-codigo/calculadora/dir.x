
struct operacion {
	float firstparam; /* nombre de la entrada de directorio */
	float secondparam; /* siguiente entrada */
};

/* Declaramos los vectores */
struct vectores {
	float v1<>;
	float v2<>;
};
 
/* la siguiente union se utiliza para discriminar entre llamadas con exito y llamadas con errores */
union tipo_simple switch (int errno) {
	case 0:
		float resultado; /* sin error: listado del directorio */
	default:
		void; /* con error: nada */
};

union tipo_vector switch (int errno){
	case 0:
		float resultado<>;
	default:
		void;
};

program DIRPROG {
	version DIRVER {
		tipo_simple SUMA(operacion) = 1;
		tipo_simple RESTA(operacion) = 2;
		tipo_simple MULTIPLICACION(operacion) = 3;
		tipo_simple DIVISION(operacion) = 4;
		tipo_vector SUMA_VECTORES(vectores) = 5;
		tipo_vector RESTA_VECTORES(vectores) = 6;
		tipo_vector MULTIPLICACION_VECTORES(vectores) = 7;
		tipo_vector DIVISION_VECTORES(vectores) = 8;

	} =1;
} = 0x20000155;
