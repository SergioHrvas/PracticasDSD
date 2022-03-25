
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


  struct matriz{
 	float v1<>;
	 int v1_f;
	 int v1_c;
 };

 struct matrices{
	 float v1<>;
	 int v1_f;
	 int v1_c;
	 float v2<>;
	 int v2_f;
	 int v2_c;
 };
 	
 struct matrizyescalar{
	 float v1<>;
	 int v1_f;
	 int v1_c;
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

union tipo_matriz switch (int errno){
	case 0:
		matriz m;
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
		tipo_matriz SUMA_MATRICES(matrices) = 10;
		tipo_matriz RESTA_MATRICES(matrices) = 11;
		tipo_matriz PRODUCTO_MATRICES(matrices) = 12;
		tipo_matriz MULTI_MATRIZ_ESCALAR(matrizyescalar) = 13;
		tipo_matriz DIVI_MATRIZ_ESCALAR(matrizyescalar) = 14;

	} =1;
} = 0x20000155;
