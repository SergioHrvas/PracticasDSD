
#include "dir.h"

void dirprog_1(char *host)
{
	CLIENT *clnt;
	tipo_simple *result_1;
	operacion suma_1_arg1;
	tipo_simple *result_2;
	operacion resta_1_arg1;
	tipo_simple *result_3;
	operacion multiplicacion_1_arg1;
	tipo_simple *result_4;
	operacion division_1_arg1;
	tipo_vector *result_5;
	vectores suma_vectores_1_arg1;
	tipo_vector *result_6;
	vectores resta_vectores_1_arg1;
	tipo_simple *result_7;
	vectores producto_escalar_1_arg1;
	tipo_vector *result_8;
	vectoryescalar multi_vector_escalar_1_arg1;
	tipo_vector *result_9;
	vectoryescalar divi_vector_escalar_1_arg1;
	tipo_matriz *result_10;
	matrices suma_matrices_1_arg1;
	tipo_matriz *result_11;
	matrices resta_matrices_1_arg1;
	tipo_matriz *result_12;
	matrices producto_matrices_1_arg1;
	tipo_matriz *result_13;
	matrizyescalar multi_matriz_escalar_1_arg1;
	tipo_matriz *result_14;
	matrizyescalar divi_matriz_escalar_1_arg1;
	float escalar = 0;
	char operacion;
	float operando1, operando2;
	char opcion;
	char continuo = 's';
	int primeravez = 1;
	float resultado = 0;
	int interactivo = 0;
	int tam = 2;

#ifndef DEBUG
	clnt = clnt_create(host, DIRPROG, DIRVER, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */

	while (opcion != 'q')
	{
		printf("=======CALCULADORA========\n");
		printf("Operaciones simples: s\n");
		printf("Operaciones simples (interactivo): i\n");
		printf("Operaciones con polinomios: p\n");
		printf("Operaciones con vectores: v\n");
		printf("Operaciones con matrices: m\n");
		printf("Salir: q\n");
		scanf("%c", &opcion);
		while (opcion == ' ' || opcion == '\n')
		{
			scanf("%c", &opcion);
		}

		while (opcion != 's' && opcion != 'p' && opcion != 'v' && opcion != 'm' && opcion != 'q' && opcion != 'i')
		{
			printf("\nIntroduzca una opción correcta\n");
			printf("Operaciones simples: s\n");
			printf("Operaciones simples (interactivo): i\n");
			printf("Operaciones con polinomios: p\n");
			printf("Operaciones con vectores: v\n");
			printf("Operaciones con matrices: m\n");
			printf("Salir: q\n");
			scanf("%c", &opcion);
			while (opcion == ' ' || opcion == '\n')
			{
				scanf("%c", &opcion);
			}
		}
		switch (opcion)
		{
		case 'i':
		case 's':
			if(opcion == 's'){
				interactivo = 0;
			}
			else{
				interactivo = 1;
			}
			while (continuo != 'n')
			{

				if (primeravez != 1 && interactivo == 1)
				{
					operando1 = resultado;
					printf("%f", operando1);
				}

				if (primeravez || interactivo == 0)
				{
					printf("Introduzca la operacion (ej: '4 + 5'):\n");
					scanf("%f", &operando1);
					while ((operando1 == '\n' || operando1 == ' '))
					{
						scanf("%f", &operando1);
					}

					primeravez = 0;
				}

				scanf("%c", &operacion);
				while (operacion == '\n' || operacion == ' ')
				{
					scanf("%c", &operacion);
				}

				scanf("%f", &operando2);
				while (operando2 == '\n' || operando2 == ' ')
				{
					scanf("%f", &operando2);
				}

				printf("--->%f %c %f\n", operando1, operacion, operando2);
				if (operacion == '+')
				{
					suma_1_arg1.firstparam = operando1;
					suma_1_arg1.secondparam = operando2;
					result_1 = suma_1(suma_1_arg1, clnt);
					if (result_1 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_1).tipo_simple_u.resultado;
				}

				else if (operacion == '-')
				{
					resta_1_arg1.firstparam = operando1;
					resta_1_arg1.secondparam = operando2;
					result_2 = resta_1(resta_1_arg1, clnt);
					if (result_2 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_2).tipo_simple_u.resultado;
				}

				else if (operacion == '*')
				{
					multiplicacion_1_arg1.firstparam = operando1;
					multiplicacion_1_arg1.secondparam = operando2;
					result_3 = multiplicacion_1(multiplicacion_1_arg1, clnt);
					if (result_3 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_3).tipo_simple_u.resultado;
				}
				else if (operacion == '/')
				{
					division_1_arg1.firstparam = operando1;
					division_1_arg1.secondparam = operando2;
					result_4 = division_1(division_1_arg1, clnt);
					if (result_4 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_4).tipo_simple_u.resultado;
				}

				printf("%f ", resultado);
				printf("\n¿Desea continuar?: ('s' para si | 'n' para no)\n");
				scanf("%c", &continuo);
				while (continuo != 's' && continuo != 'n')
				{
					scanf("%c", &continuo);
				}
			}
			primeravez = 1;
			continuo = 0;
			printf("\n");
			break;

		case 'v':
			printf("Introduzca la operación que desea realizar:\n");
			printf("> Suma: +\n");
			printf("> Resta: -\n");
			printf("> Producto escalar: *\n");
			printf("> Multiplicación por escalar: m\n");
			printf("> División por escalar: d\n");

			scanf("%c", &operacion);
			while ((operacion == '\n' || operacion == ' ') || (operacion != '+') && (operacion != '-') && (operacion != '*') && (operacion != 'm') && (operacion != 'd'))
			{
				scanf("%c", &operacion);
			}

			if (operacion != 'm' && operacion != 'd')
				printf("Introduzca el tamaño de los vectores:\n");
			else
			{
				printf("Introduzca el tamaño del vector:\n");
			}

			scanf("%d", &tam);
			while ((tam == '\n' || tam == ' ') || (tam <= 0))
			{
				scanf("%d", &tam);
			}
			float *vector1 = (float *)malloc(tam * sizeof(float));

			if (operacion != 'm' && operacion != 'd')
				printf("Introduzca los elementos del primer vector:\n");
			else
			{
				printf("Introduzca los elementos del vector:\n");
			}
			for (int k = 0; k < tam; k++)
			{
				scanf("%f", &vector1[k]);
				while (vector1[k] == '\n' || vector1[k] == ' ')
				{
					scanf("%f", &vector1[k]);
				}
			}
			float *vector2;
			if (operacion != 'm' && operacion != 'd')
			{

				vector2 = (float *)malloc(tam * sizeof(float));

				printf("Introduzca los elementos del segundo vector:\n");
				for (int k = 0; k < tam; k++)
				{
					scanf("%f", &vector2[k]);
					while (vector2[k] == '\n' || vector2[k] == ' ')
					{
						scanf("%f", &vector2[k]);
					}
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", vector1[k]);
				}
				printf("] %c [ ", operacion);
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", vector2[k]);
				}
				printf("] = ");
			}
			else
			{
				printf("Introduzca un número: \n");
				scanf("%f", &escalar);
				while (escalar == '\n' || escalar == ' ')
				{
					scanf("%f", &escalar);
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", vector1[k]);
				}
				printf("] ");
				if (operacion == 'm')
					printf(" * ");
				else
					printf(" / ");
				printf("%f = ", escalar);
			}
			switch (operacion)
			{
			case '+':
				suma_vectores_1_arg1.v1.v1_val = vector1;
				suma_vectores_1_arg1.v2.v2_val = vector2;
				suma_vectores_1_arg1.v2.v2_len = tam;
				suma_vectores_1_arg1.v1.v1_len = tam;
				result_5 = suma_vectores_1(suma_vectores_1_arg1, clnt);
				if (result_5 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", (*result_5).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_5->tipo_vector_u.resultado.resultado_val);
				break;
			case '-':
				resta_vectores_1_arg1.v1.v1_val = vector1;
				resta_vectores_1_arg1.v2.v2_val = vector2;
				resta_vectores_1_arg1.v2.v2_len = tam;
				resta_vectores_1_arg1.v1.v1_len = tam;
				result_6 = resta_vectores_1(resta_vectores_1_arg1, clnt);
				if (result_6 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", (*result_6).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_6->tipo_vector_u.resultado.resultado_val);

				break;
			case '*':
				producto_escalar_1_arg1.v1.v1_val = vector1;
				producto_escalar_1_arg1.v2.v2_val = vector2;
				producto_escalar_1_arg1.v2.v2_len = tam;
				producto_escalar_1_arg1.v1.v1_len = tam;
				result_7 = producto_escalar_1(producto_escalar_1_arg1, clnt);
				if (result_7 == (tipo_simple *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				printf("%f ", (*result_7).tipo_simple_u.resultado);
				break;
			case 'm':
				multi_vector_escalar_1_arg1.v.v_val = vector1;
				multi_vector_escalar_1_arg1.num = escalar;
				multi_vector_escalar_1_arg1.v.v_len = tam;
				result_8 = multi_vector_escalar_1(multi_vector_escalar_1_arg1, clnt);
				if (result_8 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", (*result_8).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_8->tipo_vector_u.resultado.resultado_val);
				break;

			case 'd':
				divi_vector_escalar_1_arg1.v.v_val = vector1;
				divi_vector_escalar_1_arg1.num = escalar;
				divi_vector_escalar_1_arg1.v.v_len = tam;
				result_9 = divi_vector_escalar_1(divi_vector_escalar_1_arg1, clnt);
				if (result_9 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%f ", (*result_9).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_9->tipo_vector_u.resultado.resultado_val);
				break;
			}
			printf("\n");
			free(vector1);
			free(vector2);
			break;

		case 'm':
			printf("Introduzca la operación que desea realizar:\n");
			printf("> Suma: +\n");
			printf("> Resta: -\n");
			printf("> Producto: *\n");
			printf("> Matriz por escalar: m\n");
			printf("> Matriz entre escalar: d\n");

			scanf("%c", &operacion);
			while ((operacion == '\n' || operacion == ' ') || (operacion != '+') && (operacion != '-') && (operacion != '*') && (operacion != 'd') && (operacion != 'm'))
			{
				scanf("%c", &operacion);
			}

			if (operacion == '+' && operacion == '-')
				printf("Introduzca el tamaño por filas de las matrices:\n");
			else if (operacion == '*')
			{
				printf("Introduzca el tamaño por filas de la primera matriz: \n");
			}
			else
			{
				printf("Introduzca el tamaño por filas de la matriz:\n");
			}
			int tamfilas1 = 1;
			int tamcolumnas1 = 1;
			int tamfilas2 = 1;
			int tamcolumnas2 = 1;
			scanf("%d", &tamfilas1);
			while ((tamfilas1 == '\n' || tamfilas1 == ' ') || (tamfilas1 <= 0))
			{
				scanf("%d", &tamfilas1);
			}

			if (operacion == '+' && operacion == '-')
				printf("Introduzca el tamaño por columnas de las matrices:\n");
			else if (operacion == '*')
				printf("Introduzca el tamaño por columnas de la primera matriz: \n");
			else
				printf("Introduzca el tamaño por columnas de la matriz:\n");

			scanf("%d", &tamcolumnas1);
			while ((tamcolumnas1 == '\n' || tamcolumnas1 == ' ') || (tamcolumnas1 <= 0))
			{
				scanf("%d", &tamcolumnas1);
			}
			printf("%d %d\n", tamfilas1, tamcolumnas1);
			float *matriz1 = (float *)malloc(tamfilas1 * tamcolumnas1 * sizeof(float));
			float *matriz2;

			if (operacion == '*')
			{

				printf("Introduzca el tamaño por filas de la segunda matriz: \n");

				scanf("%d", &tamfilas2);
				while ((tamfilas2 == '\n' || tamfilas2 == ' ') || (tamfilas2 <= 0))
				{
					scanf("%d", &tamfilas2);
				}

				printf("Introduzca el tamaño por columnas de la segunda matriz: \n");

				scanf("%d", &tamcolumnas2);
				while ((tamcolumnas2 == '\n' || tamcolumnas2 == ' ') || (tamcolumnas2 <= 0))
				{
					scanf("%d", &tamcolumnas2);
				}
				matriz2 = (float *)malloc(tamfilas2 * tamcolumnas2 * sizeof(float));
			}
			else if (operacion == '+' || operacion == '-')
			{
				tamfilas2 = tamfilas1;
				tamcolumnas2 = tamcolumnas1;
				matriz2 = (float *)malloc(tamfilas2 * tamcolumnas2 * sizeof(float));
			}

			if (operacion != 'm' && operacion != 'd')
				printf("Introduzca los elementos de la primera matriz:\n");
			else
			{
				printf("Introduzca los elementos de la matriz:\n");
			}
			printf("(Fila por fila)\n");
			for (int f = 0; f < tamfilas1; f++)
			{
				for (int c = 0; c < tamcolumnas1; c++)
				{
					scanf("%f", &matriz1[f * tamcolumnas1 + c]);
					while (matriz1[f * tamcolumnas1 + c] == '\n' || matriz1[f * tamcolumnas1 + c] == ' ')
					{
						scanf("%f", &matriz1[f * tamcolumnas1 + c]);
					}
				}
			}

			if (operacion == '*' || operacion == '+' || operacion == '-')
			{
				printf("Introduzca los elementos de la segunda matriz:\n");
				printf("(Fila por fila)\n");

				for (int f = 0; f < tamfilas2; f++)
				{
					for (int c = 0; c < tamcolumnas2; c++)
					{
						scanf("%f", &matriz2[f * tamcolumnas2 + c]);
						while (matriz2[f * tamcolumnas2 + c] == '\n' || matriz2[f * tamcolumnas2 + c] == ' ')
						{
							scanf("%f", &matriz2[f * tamcolumnas2 + c]);
						}
					}
				}
				printf("\n ");
				for (int f = 0; f < tamfilas1; f++)
				{
					for (int c = 0; c < tamcolumnas1; c++)
					{
						printf("%f ", matriz1[f * tamcolumnas1 + c]);
					}
					printf("\n");
				}
				for (int f = 0; f < tamfilas2; f++)
				{
					for (int c = 0; c < tamcolumnas2; c++)
					{
						printf("%f ", matriz2[f * tamcolumnas2 + c]);
					}
					printf("\n");
				}
				printf("=======\n");
			}
			else if (operacion == 'm' || operacion == 'd')
			{
				printf("Introduzca un número: \n");
				scanf("%f", &escalar);
				while (escalar == '\n' || escalar == ' ')
				{
					scanf("%f", &escalar);
				}
				for (int f = 0; f < tamfilas1; f++)
				{
					for (int c = 0; c < tamcolumnas1; c++)
					{
						printf("%f ", matriz1[f * tamcolumnas1 + c]);
					}
					printf("\n");
				}
				if (operacion == 'm')
					printf(" * ");
				else
					printf(" / ");
				printf("\n %f = \n", escalar);
			}
			switch (operacion)
			{
			case '+':
				suma_matrices_1_arg1.v1.v1_val = matriz1;
				suma_matrices_1_arg1.v2.v2_val = matriz2;
				suma_matrices_1_arg1.v1_c = tamcolumnas1;
				suma_matrices_1_arg1.v1_f = tamfilas1;
				suma_matrices_1_arg1.v2_c = tamcolumnas2;
				suma_matrices_1_arg1.v2_f = tamfilas2;

				suma_matrices_1_arg1.v1.v1_len = tamcolumnas1 * tamfilas1;
				suma_matrices_1_arg1.v2.v2_len = tamcolumnas2 * tamfilas2;

				result_10 = suma_matrices_1(suma_matrices_1_arg1, clnt);
				if (result_10 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				for (int f = 0; f < result_10->tipo_matriz_u.m.v1_f; f++)
				{
					for (int c = 0; c < result_10->tipo_matriz_u.m.v1_c; c++)
					{
						printf("%f ", result_10->tipo_matriz_u.m.v1.v1_val[f * tamcolumnas1 + c]);
					}
					printf("\n");
				}
				free(result_10->tipo_matriz_u.m.v1.v1_val);
				break;
			case '-':
				resta_matrices_1_arg1.v1.v1_val = matriz1;
				resta_matrices_1_arg1.v2.v2_val = matriz2;
				resta_matrices_1_arg1.v1_c = tamcolumnas1;
				resta_matrices_1_arg1.v1_f = tamfilas1;
				resta_matrices_1_arg1.v2_c = tamcolumnas2;
				resta_matrices_1_arg1.v2_f = tamfilas2;

				resta_matrices_1_arg1.v1.v1_len = tamcolumnas1 * tamfilas1;
				resta_matrices_1_arg1.v2.v2_len = tamcolumnas2 * tamfilas2;

				result_11 = resta_matrices_1(resta_matrices_1_arg1, clnt);
				if (result_11 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				for (int f = 0; f < result_11->tipo_matriz_u.m.v1_f; f++)
				{
					for (int c = 0; c < result_11->tipo_matriz_u.m.v1_c; c++)
					{
						printf("%f ", result_11->tipo_matriz_u.m.v1.v1_val[f * result_11->tipo_matriz_u.m.v1_c + c]);
					}
					printf("\n");
				}
				free(result_11->tipo_matriz_u.m.v1.v1_val);
				break;
			case '*':
				producto_matrices_1_arg1.v1.v1_val = matriz1;
				producto_matrices_1_arg1.v2.v2_val = matriz2;
				producto_matrices_1_arg1.v1_c = tamcolumnas1;
				producto_matrices_1_arg1.v1_f = tamfilas1;
				producto_matrices_1_arg1.v2_c = tamcolumnas2;
				producto_matrices_1_arg1.v2_f = tamfilas2;

				producto_matrices_1_arg1.v1.v1_len = tamcolumnas1 * tamfilas1;
				producto_matrices_1_arg1.v2.v2_len = tamcolumnas2 * tamfilas2;

				result_12 = producto_matrices_1(producto_matrices_1_arg1, clnt);
				if (result_12 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				for (int f = 0; f < result_12->tipo_matriz_u.m.v1_f; f++)
				{
					for (int c = 0; c < result_12->tipo_matriz_u.m.v1_c; c++)
					{
						printf("%f ", result_12->tipo_matriz_u.m.v1.v1_val[f * result_12->tipo_matriz_u.m.v1_c + c]);
					}
					printf("\n");
				}
				free(result_12->tipo_matriz_u.m.v1.v1_val);
				break;
			case 'm':
				multi_matriz_escalar_1_arg1.v1.v1_val = matriz1;
				multi_matriz_escalar_1_arg1.num = escalar;
				multi_matriz_escalar_1_arg1.v1_c = tamcolumnas1;
				multi_matriz_escalar_1_arg1.v1_f = tamfilas1;
				multi_matriz_escalar_1_arg1.v1.v1_len = multi_matriz_escalar_1_arg1.v1_f * multi_matriz_escalar_1_arg1.v1_c;
				result_13 = multi_matriz_escalar_1(multi_matriz_escalar_1_arg1, clnt);
				if (result_13 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				for (int f = 0; f < result_13->tipo_matriz_u.m.v1_f; f++)
				{
					for (int c = 0; c < result_13->tipo_matriz_u.m.v1_c; c++)
					{
						printf("%f ", result_13->tipo_matriz_u.m.v1.v1_val[f * result_13->tipo_matriz_u.m.v1_c + c]);
					}
					printf("\n");
				}
				free(result_13->tipo_matriz_u.m.v1.v1_val);
				break;

			case 'd':
				divi_matriz_escalar_1_arg1.v1.v1_val = matriz1;
				divi_matriz_escalar_1_arg1.num = escalar;
				divi_matriz_escalar_1_arg1.v1_c = tamcolumnas1;
				divi_matriz_escalar_1_arg1.v1_f = tamfilas1;
				divi_matriz_escalar_1_arg1.v1.v1_len = divi_matriz_escalar_1_arg1.v1_f * divi_matriz_escalar_1_arg1.v1_c;
				result_14 = divi_matriz_escalar_1(divi_matriz_escalar_1_arg1, clnt);
				if (result_14 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				for (int f = 0; f < result_14->tipo_matriz_u.m.v1_f; f++)
				{
					for (int c = 0; c < result_14->tipo_matriz_u.m.v1_c; c++)
					{
						printf("%f ", result_14->tipo_matriz_u.m.v1.v1_val[f * result_14->tipo_matriz_u.m.v1_c + c]);
					}
					printf("\n");
				}
				free(result_14->tipo_matriz_u.m.v1.v1_val);
				break;
			}
			printf("\n");
			free(matriz1);
			free(matriz2);

			break;
		}
	}


#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	dirprog_1(host);
	exit(0);
}
