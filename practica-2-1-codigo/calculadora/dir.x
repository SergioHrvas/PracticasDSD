
struct operacion {
	float firstparam; /* nombre de la entrada de directorio */
	float secondparam; /* siguiente entrada */
};

/* Declaramos los vectores */
struct vectores {
	float v1<>;
	float v2<>;
};
 
 struct vectoryescalar{
	 float v<>;
	 float num;
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
		tipo_simple PRODUCTO_ESCALAR(vectores) = 7;
		tipo_vector MULTI_VECTOR_ESCALAR(vectoryescalar) = 8;
		tipo_vector DIVI_VECTOR_ESCALAR(vectoryescalar) = 9;

	} =1;
} = 0x20000155;
