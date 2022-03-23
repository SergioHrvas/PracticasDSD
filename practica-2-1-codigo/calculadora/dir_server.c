#include "dir.h"

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
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v1.v1_len);
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
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v1.v1_len);
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
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v.v_len);

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
	result.tipo_vector_u.resultado.resultado_val = (float*) malloc(arg1.v.v_len);

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
	result.tipo_matriz_u.m.v1.v1_val = (float*) malloc(result.tipo_matriz_u.m.v1.v1_len);

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
	result.tipo_matriz_u.m.v1.v1_val = (float*) malloc(result.tipo_matriz_u.m.v1.v1_len);

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
	static tipo_matriz  result;
	if(arg1.v1_c == arg1.v2_f){
		result.tipo_matriz_u.m.v1_c = arg1.v2_c;
		result.tipo_matriz_u.m.v1_f = arg1.v1_f;
	}

		result.tipo_matriz_u.m.v1.v1_len = result.tipo_matriz_u.m.v1_c*result.tipo_matriz_u.m.v1_f;
		result.tipo_matriz_u.m.v1.v1_val = (float*) malloc(result.tipo_matriz_u.m.v1.v1_len);
		float suma;
		for(int f = 0; f < arg1.v1_f; f++){
			for(int c = 0; c < arg1.v2_c; c++){
				suma = 0;
				for(int k = 0; k < arg1.v1_c; k++){
					suma += arg1.v1.v1_val[f*arg1.v1_c+k] * arg1.v2.v2_val[k*arg1.v2_c + c];
				}
				result.tipo_matriz_u.m.v1.v1_val[f*result.tipo_matriz_u.m.v1_c+c] = suma;
			}
		}

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_simple *
determinante_1_svc(matriz arg1,  struct svc_req *rqstp)
{
	static tipo_simple  result;

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_matriz *
multi_matriz_escalar_1_svc(matrizyescalar arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  result;

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_matriz *
divi_matriz_escalar_1_svc(matrizyescalar arg1,  struct svc_req *rqstp)
{
	static tipo_matriz  result;

	/*
	 * insert server code here
	 */

	return &result;
}
