#include "dir.h"
#include "dir2.h"
tipo_simple *
suma_1_svc(operacion arg1,  struct svc_req *rqstp)
{
	static tipo_simple  result;
	result.tipo_simple_u.resultado = arg1.firstparam + arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
resta_1_svc(operacion arg1,  struct svc_req *rqstp)
{
	static tipo_simple  result;
	result.tipo_simple_u.resultado = arg1.firstparam - arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
multiplicacion_1_svc(operacion arg1,  struct svc_req *rqstp)
{
	static tipo_simple  result;
	result.tipo_simple_u.resultado = arg1.firstparam * arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
division_1_svc(operacion arg1,  struct svc_req *rqstp)
{
	static tipo_simple  result;
	result.tipo_simple_u.resultado = arg1.firstparam / arg1.secondparam;
	/*
	 * insert server code here
	 */

	return &result;
}

tipo_vector *
suma_vectores_1_svc(vectores arg1,  struct svc_req *rqstp)
{
	static tipo_vector  result;
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v1.v1_len*sizeof(float));
		result.tipo_vector_u.resultado.resultado_len = 0;

	for(int k = 0; k < arg1.v1.v1_len; k++){
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v1.v1_val[k] + arg1.v2.v2_val[k];
		result.tipo_vector_u.resultado.resultado_len++;
	}

	return &result;
}

tipo_vector *
resta_vectores_1_svc(vectores arg1,  struct svc_req *rqstp)
{
	static tipo_vector  result;
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v1.v1_len*sizeof(float));
		result.tipo_vector_u.resultado.resultado_len = 0;

	for(int k = 0; k < arg1.v1.v1_len; k++){
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v1.v1_val[k] - arg1.v2.v2_val[k];
		result.tipo_vector_u.resultado.resultado_len++;
	}

	return &result;
}


tipo_simple *
producto_escalar_1_svc(vectores arg1,  struct svc_req *rqstp)
{
	static tipo_simple  result;
	result.tipo_simple_u.resultado;
	for(int k = 0; k < arg1.v1.v1_len; k++){
		result.tipo_simple_u.resultado += arg1.v1.v1_val[k] * arg1.v2.v2_val[k];
	}

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_vector *
multi_vector_escalar_1_svc(vectoryescalar arg1,  struct svc_req *rqstp)
{
	static tipo_vector  result;
 	result.tipo_vector_u.resultado.resultado_len = 0;
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v.v_len*sizeof(float));

	/*
	 * insert server code here
	 */
	for(int k = 0; k < arg1.v.v_len; k++){
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v.v_val[k] * arg1.num;
		result.tipo_vector_u.resultado.resultado_len++;
	}
	return &result;
}

tipo_vector *
divi_vector_escalar_1_svc(vectoryescalar arg1,  struct svc_req *rqstp)
{
	static tipo_vector  result;
 	result.tipo_vector_u.resultado.resultado_len = 0;
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v.v_len*sizeof(float));

	/*
	 * insert server code here
	 */
	for(int k = 0; k < arg1.v.v_len; k++){
		result.tipo_vector_u.resultado.resultado_val[k] = arg1.v.v_val[k] / arg1.num;
		result.tipo_vector_u.resultado.resultado_len++;
	}
	return &result;
}


tipo_matriz *
suma_matrices_1_svc(matrices arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  result;
	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;
	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c*result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float*) malloc(result.tipo_matriz_u.m.v1.v1_len*sizeof(float));

	for(int f = 0; f < result.tipo_matriz_u.m.v1_f; f++){
		for(int c = 0; c < result.tipo_matriz_u.m.v1_c; c++){
			result.tipo_matriz_u.m.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] = arg1.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] + arg1.v2.v2_val[f*result.tipo_matriz_u.m.v1_c+c];
		}
	}


	return &result;
}


tipo_matriz *
resta_matrices_1_svc(matrices arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  result;
	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;
	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c*result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float*) malloc(result.tipo_matriz_u.m.v1.v1_len*sizeof(float));

	for(int f = 0; f < result.tipo_matriz_u.m.v1_f; f++){
		for(int c = 0; c < result.tipo_matriz_u.m.v1_c; c++){
			result.tipo_matriz_u.m.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] = arg1.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] - arg1.v2.v2_val[f*result.tipo_matriz_u.m.v1_c+c];
		}
	}

	return &result;
}

tipo_matriz *
producto_matrices_1_svc(matrices arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  *result_3;
	CLIENT * clnt = clnt_create ("localhost", DIRPROG_ULT, DIRVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror ("localhost");
		exit (1);
	}
	result_3 = producto_matrices_ult_1(arg1, clnt);
	if (result_3 == (tipo_matriz *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	/*
	 * insert server code here
	 */

	return result_3;
}
tipo_matriz *
multi_matriz_escalar_1_svc(matrizyescalar arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  result;

	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;

	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c * result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float *)malloc(result.tipo_matriz_u.m.v1.v1_len*sizeof(float));

	for (int f = 0; f < arg1.v1_f; f++)
	{
		for (int c = 0; c < arg1.v1_c; c++)
		{
			 result.tipo_matriz_u.m.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] = arg1.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c]*arg1.num;
		}
	}

	return &result;
}

tipo_matriz *
divi_matriz_escalar_1_svc(matrizyescalar arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  result;

	result.tipo_matriz_u.m.v1_c = arg1.v1_c;
	result.tipo_matriz_u.m.v1_f = arg1.v1_f;

	result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c * result.tipo_matriz_u.m.v1_f;
	result.tipo_matriz_u.m.v1.v1_val = (float *)malloc(result.tipo_matriz_u.m.v1.v1_len*sizeof(float));

	for (int f = 0; f < arg1.v1_f; f++)
	{
		for (int c = 0; c < arg1.v1_c; c++)
		{
			 result.tipo_matriz_u.m.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] = arg1.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c]/arg1.num;
		}
	}

	return &result;
}
