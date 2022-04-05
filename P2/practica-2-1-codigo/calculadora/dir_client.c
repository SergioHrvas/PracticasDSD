

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
	tipo_simple *result_5;
	operacion_2 potencia_1_arg1;
	tipo_simple *result_6;
	operacion_2 raiz_1_arg1;
	tipo_simple *result_7;
	operacion_2 logaritmo_1_arg1;
	tipo_vector *result_8;
	vectores suma_vectores_1_arg1;
	tipo_vector *result_9;
	vectores resta_vectores_1_arg1;
	tipo_simple *result_10;
	vectores producto_escalar_1_arg1;
	tipo_vector *result_11;
	vectoryescalar multi_vector_escalar_1_arg1;
	tipo_vector *result_12;
	vectoryescalar divi_vector_escalar_1_arg1;
	tipo_matriz *result_13;
	matrices suma_matrices_1_arg1;
	tipo_matriz *result_14;
	matrices resta_matrices_1_arg1;
	tipo_matriz *result_15;
	matrices producto_matrices_1_arg1;
	tipo_matriz *result_16;
	matrizyescalar multi_matriz_escalar_1_arg1;
	tipo_matriz *result_17;
	matrizyescalar divi_matriz_escalar_1_arg1;
	tipo_fraccion *result_18;
	fracciones suma_fracciones_1_arg1;
	tipo_fraccion *result_19;
	fracciones resta_fracciones_1_arg1;
	tipo_fraccion *result_20;
	fracciones multi_fracciones_1_arg1;
	tipo_fraccion *result_21;
	fracciones divi_fracciones_1_arg1;
	tipo_fraccion *result_22;
	fraccion simplificar_fraccion_1_arg1;
	float escalar = 0;
	char operacion;
	float operando1, operando2;
	char opcion;
	char continuo = 's';
	int primeravez = 1;
	float resultado = 0;
	int interactivo = 0;
	int tam = 2, operando2_int = 0;
	int num1 = 1, den1 = 1, num2 = 1, den2 = 1;

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
		printf("Operaciones con fracciones: f\n");
		printf("Operaciones con vectores: v\n");
		printf("Operaciones con matrices: m\n");
		printf("Salir: q\n");
		scanf("%c", &opcion);
		while (opcion == ' ' || opcion == '\n')
		{
			scanf("%c", &opcion);
		}

		while (opcion != 's' && opcion != 'f' && opcion != 'v' && opcion != 'm' && opcion != 'q' && opcion != 'i')
		{
			printf("\nIntroduzca una opción correcta\n");
			printf("Operaciones simples: s\n");
			printf("Operaciones simples (interactivo): i\n");
			printf("Operaciones con fracciones: f\n");
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
			if (opcion == 's')
			{
				interactivo = 0;
			}
			else
			{
				interactivo = 1;
			}
			while (continuo != 'n')
			{

				if (primeravez != 1 && interactivo == 1)
				{
					operando1 = resultado;
					printf("%g ", operando1);
				}

				if (primeravez || interactivo == 0)
				{
					printf("Introduzca la operacion (ej: '4 + 5'):\n");
					printf("Operaciones posibles: + | - | * | / | ^ | l | r\n");
					printf("Formato: ( 3 ^ 4 ) para 3 elevado a 4\n");
					printf("Formato: ( 3 l 4 ) para logaritmo de 3 en base 4\n");
					printf("Formato: ( 3 r 4 ) para raiz cuarta de 3\n");

					scanf("%f", &operando1);

					primeravez = 0;
				}

				scanf("%c", &operacion);
				while (operacion == '\n' || operacion == ' ')
				{
					scanf("%c", &operacion);
				}

				scanf("%f", &operando2);

				if (operacion == '^' || operacion == 'l' || operacion == 'r')
				{
					operando2_int = (int)operando2;
					printf("---> %g %c %d = ", operando1, operacion, operando2_int);
				}
				else
				{
					printf("---> %g %c %g = ", operando1, operacion, operando2);
				}

				switch (operacion)
				{
				case '+':
					suma_1_arg1.firstparam = operando1;
					suma_1_arg1.secondparam = operando2;
					result_1 = suma_1(suma_1_arg1, clnt);
					if (result_1 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_1).tipo_simple_u.resultado;
					break;

				case '-':
					resta_1_arg1.firstparam = operando1;
					resta_1_arg1.secondparam = operando2;
					result_2 = resta_1(resta_1_arg1, clnt);
					if (result_2 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_2).tipo_simple_u.resultado;
					break;
				case '*':
					multiplicacion_1_arg1.firstparam = operando1;
					multiplicacion_1_arg1.secondparam = operando2;
					result_3 = multiplicacion_1(multiplicacion_1_arg1, clnt);
					if (result_3 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_3).tipo_simple_u.resultado;
					break;
				case '/':
					division_1_arg1.firstparam = operando1;
					division_1_arg1.secondparam = operando2;
					result_4 = division_1(division_1_arg1, clnt);
					if (result_4 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_4).tipo_simple_u.resultado;
					break;
				case '^':
					potencia_1_arg1.firstparam = operando1;
					potencia_1_arg1.secondparam = operando2_int;
					result_5 = potencia_1(potencia_1_arg1, clnt);
					if (result_5 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_5).tipo_simple_u.resultado;

					break;
				case 'l':
					logaritmo_1_arg1.firstparam = operando1;
					logaritmo_1_arg1.secondparam = operando2_int;
					result_6 = logaritmo_1(logaritmo_1_arg1, clnt);
					if (result_6 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_6).tipo_simple_u.resultado;

					break;
				case 'r':
					raiz_1_arg1.firstparam = operando1;
					raiz_1_arg1.secondparam = operando2_int;
					result_7 = raiz_1(raiz_1_arg1, clnt);
					if (result_7 == (tipo_simple *)NULL)
					{
						clnt_perror(clnt, "call failed");
					}
					resultado = (*result_7).tipo_simple_u.resultado;
					break;
				}
				printf("%g ", resultado);
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
			while (tam <= 0)
			{
				printf("El tamaño del vector debe ser mayor que 0. Vuelva a intentarlo: \n");
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
			}
			float *vector2;
			if (operacion != 'm' && operacion != 'd')
			{

				vector2 = (float *)malloc(tam * sizeof(float));

				printf("Introduzca los elementos del segundo vector:\n");
				for (int k = 0; k < tam; k++)
				{
					scanf("%f", &vector2[k]);
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", vector1[k]);
				}
				printf("] %c [ ", operacion);
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", vector2[k]);
				}
				printf("] = ");
			}
			else
			{
				printf("Introduzca un número: \n");
				scanf("%f", &escalar);

				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", vector1[k]);
				}
				printf("] ");
				if (operacion == 'm')
					printf(" * ");
				else
					printf(" / ");
				printf("%g = ", escalar);
			}
			switch (operacion)
			{
			case '+':
				suma_vectores_1_arg1.v1.v1_val = vector1;
				suma_vectores_1_arg1.v2.v2_val = vector2;
				suma_vectores_1_arg1.v2.v2_len = tam;
				suma_vectores_1_arg1.v1.v1_len = tam;
				result_8 = suma_vectores_1(suma_vectores_1_arg1, clnt);
				if (result_8 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", (*result_8).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_8->tipo_vector_u.resultado.resultado_val);
				break;
			case '-':
				resta_vectores_1_arg1.v1.v1_val = vector1;
				resta_vectores_1_arg1.v2.v2_val = vector2;
				resta_vectores_1_arg1.v2.v2_len = tam;
				resta_vectores_1_arg1.v1.v1_len = tam;
				result_9 = resta_vectores_1(resta_vectores_1_arg1, clnt);
				if (result_9 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", (*result_9).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_9->tipo_vector_u.resultado.resultado_val);

				break;
			case '*':
				producto_escalar_1_arg1.v1.v1_val = vector1;
				producto_escalar_1_arg1.v2.v2_val = vector2;
				producto_escalar_1_arg1.v2.v2_len = tam;
				producto_escalar_1_arg1.v1.v1_len = tam;
				result_10 = producto_escalar_1(producto_escalar_1_arg1, clnt);
				if (result_10 == (tipo_simple *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				printf("%g ", (*result_10).tipo_simple_u.resultado);
				break;
			case 'm':
				multi_vector_escalar_1_arg1.v.v_val = vector1;
				multi_vector_escalar_1_arg1.num = escalar;
				multi_vector_escalar_1_arg1.v.v_len = tam;
				result_11 = multi_vector_escalar_1(multi_vector_escalar_1_arg1, clnt);
				if (result_11 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", (*result_11).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_11->tipo_vector_u.resultado.resultado_val);
				break;

			case 'd':
				divi_vector_escalar_1_arg1.v.v_val = vector1;
				divi_vector_escalar_1_arg1.num = escalar;
				divi_vector_escalar_1_arg1.v.v_len = tam;
				result_12 = divi_vector_escalar_1(divi_vector_escalar_1_arg1, clnt);
				if (result_12 == (tipo_vector *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				printf("[ ");
				for (int k = 0; k < tam; k++)
				{
					printf("%g ", (*result_12).tipo_vector_u.resultado.resultado_val[k]);
				}
				printf("]");
				free(result_12->tipo_vector_u.resultado.resultado_val);
				break;
			}
			printf("\n");
			free(vector1);
			if (operacion != 'd' && operacion != 'm')
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
			while (tamfilas1 <= 0)
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
			while (tamcolumnas1 <= 0)
			{
				scanf("%d", &tamcolumnas1);
			}

			float *matriz1 = (float *)malloc(tamfilas1 * tamcolumnas1 * sizeof(float));
			float *matriz2;

			if (operacion == '*')
			{

				printf("Introduzca el tamaño por filas de la segunda matriz: \n");
				scanf("%d", &tamfilas2);
				while(tamfilas2 != tamcolumnas1){
					printf("Error. El tamaño de las filas de la segunda matriz debe ser igual al de las columnas de la primera matriz: \n");
					scanf("%d", &tamfilas2);
				}

				printf("Introduzca el tamaño por columnas de la segunda matriz: \n");

				scanf("%d", &tamcolumnas2);
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
					}
				}
				printf("\n");
				for (int f = 0; f < tamfilas1; f++)
				{
					for (int c = 0; c < tamcolumnas1; c++)
					{
						printf("%g\t", matriz1[f * tamcolumnas1 + c]);
					}
					printf("\n");
				}
				printf("\n\t%c\n\n",operacion);
				for (int f = 0; f < tamfilas2; f++)
				{
					for (int c = 0; c < tamcolumnas2; c++)
					{
						printf("%g\t", matriz2[f * tamcolumnas2 + c]);
					}
					printf("\n");
				}
				printf("=============\n");
			}
			else if (operacion == 'm' || operacion == 'd')
			{
				printf("Introduzca un número: \n");
				scanf("%f", &escalar);

				for (int f = 0; f < tamfilas1; f++)
				{
					for (int c = 0; c < tamcolumnas1; c++)
					{
						printf("%g\t", matriz1[f * tamcolumnas1 + c]);
					}
					printf("\n");
				}
				if (operacion == 'm')
					printf(" * ");
				else
					printf(" / ");
				printf("\n %g\n", escalar);
				printf("=============\n");

			}
			tipo_matriz * mresultado;
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

				result_13 = suma_matrices_1(suma_matrices_1_arg1, clnt);
				if (result_13 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				mresultado = result_13;
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

				result_14 = resta_matrices_1(resta_matrices_1_arg1, clnt);
				if (result_14 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				mresultado = result_14;
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

				result_15 = producto_matrices_1(producto_matrices_1_arg1, clnt);
				if (result_15 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				mresultado = result_15;
				break;
			case 'm':
				multi_matriz_escalar_1_arg1.v1.v1_val = matriz1;
				multi_matriz_escalar_1_arg1.num = escalar;
				multi_matriz_escalar_1_arg1.v1_c = tamcolumnas1;
				multi_matriz_escalar_1_arg1.v1_f = tamfilas1;
				multi_matriz_escalar_1_arg1.v1.v1_len = multi_matriz_escalar_1_arg1.v1_f * multi_matriz_escalar_1_arg1.v1_c;
				result_16 = multi_matriz_escalar_1(multi_matriz_escalar_1_arg1, clnt);
				if (result_16 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				mresultado = result_16;
				break;

			case 'd':
				divi_matriz_escalar_1_arg1.v1.v1_val = matriz1;
				divi_matriz_escalar_1_arg1.num = escalar;
				divi_matriz_escalar_1_arg1.v1_c = tamcolumnas1;
				divi_matriz_escalar_1_arg1.v1_f = tamfilas1;
				divi_matriz_escalar_1_arg1.v1.v1_len = divi_matriz_escalar_1_arg1.v1_f * divi_matriz_escalar_1_arg1.v1_c;
				result_17 = divi_matriz_escalar_1(divi_matriz_escalar_1_arg1, clnt);
				if (result_17 == (tipo_matriz *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}

				mresultado = result_17;

				break;
			}
				for (int f = 0; f < mresultado->tipo_matriz_u.m.v1_f; f++)
				{
					for (int c = 0; c < mresultado->tipo_matriz_u.m.v1_c; c++)
					{
						printf("%g\t", mresultado->tipo_matriz_u.m.v1.v1_val[f * mresultado->tipo_matriz_u.m.v1_c + c]);
					}
					printf("\n");
				}
			printf("\n");
			free(matriz1);
			if (operacion != 'd' && operacion != 'm')
				free(matriz2);
			
			free(mresultado->tipo_matriz_u.m.v1.v1_val);

			break;

		case 'f':

			printf("Introduzca la operación que desea realizar:\n");
			printf("> Suma: +\n");
			printf("> Resta: -\n");
			printf("> Multiplicación: *\n");
			printf("> División: /\n");
			printf("> Simplificar: s\n");

			scanf("%c", &operacion);
			while ((operacion == '\n' || operacion == ' ') || (operacion != '+') && (operacion != '-') && (operacion != '*') && (operacion != '/') && (operacion != 's'))
			{
				scanf("%c", &operacion);
			}

			if (operacion != 's')
				printf("Introduzca el numerador de la primera fracción:\n");
			else
				printf("Introduzca el numerador de la fracción:\n");
			scanf("%d", &num1);

			if (operacion != 's')
				printf("Introduzca el denominador de la primera fracción:\n");
			else
				printf("Introduzca el denominador de la fracción:\n");

			scanf("%d", &den1);

			if (operacion != 's')
			{

				printf("Introduzca el numerador de la segunda fracción:\n");
				scanf("%d", &num2);

				printf("Introduzca el denominador de la segunda fracción:\n");
				scanf("%d", &den2);
			}
			int num_res = 1, den_res = 1;
			switch (operacion)
			{
			case '+':
				suma_fracciones_1_arg1.f1.den = den1;
				suma_fracciones_1_arg1.f1.num = num1;
				suma_fracciones_1_arg1.f2.den = den2;
				suma_fracciones_1_arg1.f2.num = num2;
				result_18 = suma_fracciones_1(suma_fracciones_1_arg1, clnt);
				if (result_18 == (tipo_fraccion *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				num_res = result_18->tipo_fraccion_u.f.num;
				den_res = result_18->tipo_fraccion_u.f.den;

				break;
			case '-':
				resta_fracciones_1_arg1.f1.den = den1;
				resta_fracciones_1_arg1.f1.num = num1;
				resta_fracciones_1_arg1.f2.den = den2;
				resta_fracciones_1_arg1.f2.num = num2;
				result_19 = resta_fracciones_1(resta_fracciones_1_arg1, clnt);
				if (result_19 == (tipo_fraccion *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				num_res = result_19->tipo_fraccion_u.f.num;
				den_res = result_19->tipo_fraccion_u.f.den;
				break;
			case '*':
				multi_fracciones_1_arg1.f1.den = den1;
				multi_fracciones_1_arg1.f1.num = num1;
				multi_fracciones_1_arg1.f2.den = den2;
				multi_fracciones_1_arg1.f2.num = num2;
				result_20 = multi_fracciones_1(multi_fracciones_1_arg1, clnt);
				if (result_20 == (tipo_fraccion *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				num_res = result_20->tipo_fraccion_u.f.num;
				den_res = result_20->tipo_fraccion_u.f.den;
				break;
			case '/':
				divi_fracciones_1_arg1.f1.den = den1;
				divi_fracciones_1_arg1.f1.num = num1;
				divi_fracciones_1_arg1.f2.den = den2;
				divi_fracciones_1_arg1.f2.num = num2;
				result_21 = divi_fracciones_1(divi_fracciones_1_arg1, clnt);
				if (result_21 == (tipo_fraccion *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				num_res = result_21->tipo_fraccion_u.f.num;
				den_res = result_21->tipo_fraccion_u.f.den;
				break;
			case 's':
				simplificar_fraccion_1_arg1.den = den1;
				simplificar_fraccion_1_arg1.num = num1;
				result_22 = simplificar_fraccion_1(simplificar_fraccion_1_arg1, clnt);
				if (result_22 == (tipo_fraccion *)NULL)
				{
					clnt_perror(clnt, "call failed");
				}
				num_res = result_22->tipo_fraccion_u.f.num;
				den_res = result_22->tipo_fraccion_u.f.den;
				break;
			}
			if (operacion != 's')
			{
				printf("\n   %d           %d             %d\n", num1, num2, num_res);
				printf(" ------  %c   ------   ===    ------\n", operacion);
				printf("   %d           %d              %d\n", den1, den2, den_res);
			}
			else
			{
				printf("\n   %d                  %d   \n", num1, num_res);
				printf(" ------    ===    --------\n");
				printf("   %d                 %d   \n", den1, den_res);
			}

			break;
		}
		printf("\n");
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
