
#include "dir2.h"


tipo_matriz_ult *
suma_matrices_ult_1_svc(matrices_ult arg1,  struct svc_req *rqstp)
{
	static tipo_matriz_ult  result;

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_matriz_ult *
resta_matrices_ult_1_svc(matrices_ult arg1,  struct svc_req *rqstp)
{
	static tipo_matriz_ult  result;

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_matriz_ult * producto_matrices_ult_1_svc(matrices_ult arg1,  struct svc_req *rqstp)
{
	static tipo_matriz_ult  result;
	if(arg1.v1_c == arg1.v2_f){
		result.tipo_matriz_ult_u.m.v1_c = arg1.v2_c;
		result.tipo_matriz_ult_u.m.v1_f = arg1.v1_f;


		result.tipo_matriz_ult_u.m.v1.v1_len = result.tipo_matriz_ult_u.m.v1_c*result.tipo_matriz_ult_u.m.v1_f;
		result.tipo_matriz_ult_u.m.v1.v1_val = (float*) malloc(result.tipo_matriz_ult_u.m.v1.v1_len*sizeof(float));
		float suma;
		for(int f = 0; f < arg1.v1_f; f++){
			for(int c = 0; c < arg1.v2_c; c++){
				suma = 0;
				for(int k = 0; k < arg1.v1_c; k++){
					suma += arg1.v1.v1_val[f*arg1.v1_c+k] * arg1.v2.v2_val[k*arg1.v2_c + c];
				}
				result.tipo_matriz_ult_u.m.v1.v1_val[f*result.tipo_matriz_ult_u.m.v1_c+c] = suma;
			}
		}
	}
	return &result;
}

tipo_matriz_ult *
multi_matriz_escalar_ult_1_svc(matrizyescalar_ult arg1,  struct svc_req *rqstp)
{
	static tipo_matriz_ult  result;

	/*
	 * insert server code here
	 */

	return &result;
}

tipo_matriz_ult *
divi_matriz_escalar_ult_1_svc(matrizyescalar_ult arg1,  struct svc_req *rqstp)
{
	static tipo_matriz_ult  result;

	/*
	 * insert server code here
	 */

	return &result;
}
