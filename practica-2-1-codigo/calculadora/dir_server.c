#include "dir.h"
#include "dir2.h"
#include "math.h"

tipo_simple *
suma_1_svc(operacion arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	result.tipo_simple_u.resultado = arg1.firstparam + arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
resta_1_svc(operacion arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	result.tipo_simple_u.resultado = arg1.firstparam - arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
multiplicacion_1_svc(operacion arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	result.tipo_simple_u.resultado = arg1.firstparam * arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
division_1_svc(operacion arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	result.tipo_simple_u.resultado = arg1.firstparam / arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
potencia_1_svc(operacion_2 arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	result.tipo_simple_u.resultado = pow(arg1.firstparam, arg1.secondparam);
	//se podria implementar con un bucle for pero aprovecho que he utilizado las librerias para la raiz 
	return &result;
}

tipo_simple *
raiz_1_svc(operacion_2 arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	if(arg1.secondparam != 0)
		result.tipo_simple_u.resultado = pow((float)arg1.firstparam, (1/(float)arg1.secondparam));
	else
		result.tipo_simple_u.resultado = 0;
	return &result;
}

double funcionRepeticion(double x,int i) {
    double r = 1.0;
    for(i; i > 0; i--)
		r *= x;
    return r;
}

tipo_simple *
logaritmo_1_svc(operacion_2 arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	//int b,double n
	double n = arg1.firstparam;
	int b = arg1.secondparam;

    double variable = 0;
    int i, precision = 10,repeticiones=0;
    while(n != 1 && precision >= 0) {
        for(i = 0; n >= b; i++)
			n /= b;
            n = funcionRepeticion(n,10);
            variable = 10*(variable+i);
            precision--; repeticiones++;
    }
    result.tipo_simple_u.resultado = (double)variable/funcionRepeticion(10,repeticiones);


	return &result;
}


tipo_vector *
suma_vectores_1_svc(vectores arg1, struct svc_req *rqstp)
{
	static tipo_vector result;
	result.tipo_vector_u.resultado.resultado_val = (float *)malloc(arg1.v1.v1_len * sizeof(float));
	result.tipo_vector_u.resultado.resultado_len = 0;

	for (int k = 0; k < arg1.v1.v1_len; k++)
	{
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v1.v1_val[k] + arg1.v2.v2_val[k];
		result.tipo_vector_u.resultado.resultado_len++;
	}

	return &result;
}

tipo_vector *
resta_vectores_1_svc(vectores arg1, struct svc_req *rqstp)
{
	static tipo_vector result;
	result.tipo_vector_u.resultado.resultado_val = (float *)malloc(arg1.v1.v1_len * sizeof(float));
	result.tipo_vector_u.resultado.resultado_len = 0;

	for (int k = 0; k < arg1.v1.v1_len; k++)
	{
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v1.v1_val[k] - arg1.v2.v2_val[k];
		result.tipo_vector_u.resultado.resultado_len++;
	}

	return &result;
}

tipo_simple *
producto_escalar_1_svc(vectores arg1, struct svc_req *rqstp)
{
	static tipo_simple result;
	result.tipo_simple_u.resultado;
	for (int k = 0; k < arg1.v1.v1_len; k++)
	{
		result.tipo_simple_u.resultado += arg1.v1.v1_val[k] * arg1.v2.v2_val[k];
	}

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_vector *
multi_vector_escalar_1_svc(vectoryescalar arg1, struct svc_req *rqstp)
{
	static tipo_vector result;
	result.tipo_vector_u.resultado.resultado_len = 0;
	result.tipo_vector_u.resultado.resultado_val = (float *)malloc(arg1.v.v_len * sizeof(float));

	/*
	 * insert server code here
	 */
	for (int k = 0; k < arg1.v.v_len; k++)
	{
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v.v_val[k] * arg1.num;
		result.tipo_vector_u.resultado.resultado_len++;
	}
	return &result;
}

tipo_vector *
divi_vector_escalar_1_svc(vectoryescalar arg1, struct svc_req *rqstp)
{
	static tipo_vector result;
	result.tipo_vector_u.resultado.resultado_len = 0;
	result.tipo_vector_u.resultado.resultado_val = (float *)malloc(arg1.v.v_len * sizeof(float));

	/*
	 * insert server code here
	 */
	for (int k = 0; k < arg1.v.v_len; k++)
	{
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v.v_val[k] / arg1.num;
		result.tipo_vector_u.resultado.resultado_len++;
	}
	return &result;
}

tipo_matriz *
suma_matrices_1_svc(matrices arg1, struct svc_req *rqstp)
{
	static tipo_matriz result;
	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;
	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c * result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float *)malloc(result.tipo_matriz_u.m.v1.v1_len * sizeof(float));

	for (int f = 0; f < result.tipo_matriz_u.m.v1_f; f++)
	{
		for (int c = 0; c < result.tipo_matriz_u.m.v1_c; c++)
		{
			result.tipo_matriz_u.m.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] = arg1.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] + arg1.v2.v2_val[f * result.tipo_matriz_u.m.v1_c + c];
		}
	}

	return &result;
}

tipo_matriz *
resta_matrices_1_svc(matrices arg1, struct svc_req *rqstp)
{
	static tipo_matriz result;
	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;
	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c * result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float *)malloc(result.tipo_matriz_u.m.v1.v1_len * sizeof(float));

	for (int f = 0; f < result.tipo_matriz_u.m.v1_f; f++)
	{
		for (int c = 0; c < result.tipo_matriz_u.m.v1_c; c++)
		{
			result.tipo_matriz_u.m.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] = arg1.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] - arg1.v2.v2_val[f * result.tipo_matriz_u.m.v1_c + c];
		}
	}

	return &result;
}

tipo_matriz *
producto_matrices_1_svc(matrices arg1, struct svc_req *rqstp)
{
	static tipo_matriz result;
	tipo_matriz_ult *result_3;
	CLIENT *clnt = clnt_create("localhost", DIRPROG_ULT, DIRVER, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror("localhost");
		exit(1);
	}
	static matrices_ult mu;
	mu.v1.v1_len = arg1.v1.v1_len;
	mu.v2.v2_len = arg1.v2.v2_len;
	mu.v1.v1_val = arg1.v1.v1_val;
	mu.v2.v2_val = arg1.v2.v2_val;
	mu.v1_c = arg1.v1_c;
	mu.v1_f = arg1.v1_f;
	mu.v2_c = arg1.v2_c;
	mu.v2_f = arg1.v2_f;
	result_3 = producto_matrices_ult_1(mu, clnt);

	if (result_3 == (tipo_matriz_ult *)NULL)
	{
		clnt_perror(clnt, "call faisdled");
	}
	result.tipo_matriz_u.m.v1.v1_len = result_3->tipo_matriz_ult_u.m.v1.v1_len;
	result.tipo_matriz_u.m.v1.v1_val = result_3->tipo_matriz_ult_u.m.v1.v1_val;
	result.tipo_matriz_u.m.v1_c = result_3->tipo_matriz_ult_u.m.v1_c;
	result.tipo_matriz_u.m.v1_f = result_3->tipo_matriz_ult_u.m.v1_f;

	return &result;
}
tipo_matriz *
multi_matriz_escalar_1_svc(matrizyescalar arg1, struct svc_req *rqstp)
{
	static tipo_matriz result;

	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;

	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c * result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float *)malloc(result.tipo_matriz_u.m.v1.v1_len * sizeof(float));

	for (int f = 0; f < arg1.v1_f; f++)
	{
		for (int c = 0; c < arg1.v1_c; c++)
		{
			result.tipo_matriz_u.m.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] = arg1.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] * arg1.num;
		}
	}

	return &result;
}

tipo_matriz *
divi_matriz_escalar_1_svc(matrizyescalar arg1, struct svc_req *rqstp)
{
	static tipo_matriz result;

	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;

	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c * result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float *)malloc(result.tipo_matriz_u.m.v1.v1_len * sizeof(float));

	for (int f = 0; f < arg1.v1_f; f++)
	{
		for (int c = 0; c < arg1.v1_c; c++)
		{
			result.tipo_matriz_u.m.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] = arg1.v1.v1_val[f * result.tipo_matriz_u.m.v1_c + c] / arg1.num;
		}
	}

	return &result;
}


tipo_fraccion *
suma_fracciones_1_svc(fracciones arg1,  struct svc_req *rqstp)
{
	static tipo_fraccion  result;
	if(arg1.f1.den == arg1.f2.den){
		result.tipo_fraccion_u.f.den = arg1.f1.den;
		result.tipo_fraccion_u.f.num = arg1.f1.num + arg1.f2.num;
	}
	else{
		result.tipo_fraccion_u.f.den = arg1.f1.den * arg1.f2.den;
		result.tipo_fraccion_u.f.num = arg1.f1.num * arg1.f2.den + arg1.f2.num * arg1.f1.den;
	}

	

	return &result;
}

tipo_fraccion *
resta_fracciones_1_svc(fracciones arg1,  struct svc_req *rqstp)
{
	static tipo_fraccion  result;
	if(arg1.f1.den == arg1.f2.den){
		result.tipo_fraccion_u.f.den = arg1.f1.den;
		result.tipo_fraccion_u.f.num = arg1.f1.num - arg1.f2.num;
	}
	else{
		result.tipo_fraccion_u.f.den = arg1.f1.den * arg1.f2.den;
		result.tipo_fraccion_u.f.num = arg1.f1.num * arg1.f2.den - arg1.f2.num * arg1.f1.den;
	}


	return &result;
}

tipo_fraccion *
multi_fracciones_1_svc(fracciones arg1,  struct svc_req *rqstp)
{
	static tipo_fraccion  result;

		result.tipo_fraccion_u.f.den = arg1.f1.den * arg1.f2.den;
		result.tipo_fraccion_u.f.num = arg1.f1.num * arg1.f2.num;



	return &result;
}

tipo_fraccion *
divi_fracciones_1_svc(fracciones arg1,  struct svc_req *rqstp)
{
	static tipo_fraccion  result;

		result.tipo_fraccion_u.f.num = arg1.f1.num * arg1.f2.den;
		result.tipo_fraccion_u.f.den = arg1.f1.den * arg1.f2.num;

	return &result;
}