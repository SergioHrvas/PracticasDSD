

#include <memory.h> /* for memset */
#include "dir.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

tipo_simple *
suma_1(operacion arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA,
		(xdrproc_t) xdr_operacion, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
resta_1(operacion arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA,
		(xdrproc_t) xdr_operacion, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
multiplicacion_1(operacion arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MULTIPLICACION,
		(xdrproc_t) xdr_operacion, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
division_1(operacion arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, DIVISION,
		(xdrproc_t) xdr_operacion, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
potencia_1(operacion_2 arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, POTENCIA,
		(xdrproc_t) xdr_operacion_2, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
raiz_1(operacion_2 arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RAIZ,
		(xdrproc_t) xdr_operacion_2, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
logaritmo_1(operacion_2 arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, LOGARITMO,
		(xdrproc_t) xdr_operacion_2, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_vector *
suma_vectores_1(vectores arg1,  CLIENT *clnt)
{
	static tipo_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA_VECTORES,
		(xdrproc_t) xdr_vectores, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_vector *
resta_vectores_1(vectores arg1,  CLIENT *clnt)
{
	static tipo_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA_VECTORES,
		(xdrproc_t) xdr_vectores, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_simple *
producto_escalar_1(vectores arg1,  CLIENT *clnt)
{
	static tipo_simple clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, PRODUCTO_ESCALAR,
		(xdrproc_t) xdr_vectores, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_simple, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_vector *
multi_vector_escalar_1(vectoryescalar arg1,  CLIENT *clnt)
{
	static tipo_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MULTI_VECTOR_ESCALAR,
		(xdrproc_t) xdr_vectoryescalar, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_vector *
divi_vector_escalar_1(vectoryescalar arg1,  CLIENT *clnt)
{
	static tipo_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, DIVI_VECTOR_ESCALAR,
		(xdrproc_t) xdr_vectoryescalar, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_matriz *
suma_matrices_1(matrices arg1,  CLIENT *clnt)
{
	static tipo_matriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA_MATRICES,
		(xdrproc_t) xdr_matrices, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_matriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_matriz *
resta_matrices_1(matrices arg1,  CLIENT *clnt)
{
	static tipo_matriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA_MATRICES,
		(xdrproc_t) xdr_matrices, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_matriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_matriz *
producto_matrices_1(matrices arg1,  CLIENT *clnt)
{
	static tipo_matriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, PRODUCTO_MATRICES,
		(xdrproc_t) xdr_matrices, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_matriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_matriz *
multi_matriz_escalar_1(matrizyescalar arg1,  CLIENT *clnt)
{
	static tipo_matriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MULTI_MATRIZ_ESCALAR,
		(xdrproc_t) xdr_matrizyescalar, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_matriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_matriz *
divi_matriz_escalar_1(matrizyescalar arg1,  CLIENT *clnt)
{
	static tipo_matriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, DIVI_MATRIZ_ESCALAR,
		(xdrproc_t) xdr_matrizyescalar, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_matriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_fraccion *
suma_fracciones_1(fracciones arg1,  CLIENT *clnt)
{
	static tipo_fraccion clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA_FRACCIONES,
		(xdrproc_t) xdr_fracciones, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_fraccion, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_fraccion *
resta_fracciones_1(fracciones arg1,  CLIENT *clnt)
{
	static tipo_fraccion clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA_FRACCIONES,
		(xdrproc_t) xdr_fracciones, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_fraccion, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_fraccion *
multi_fracciones_1(fracciones arg1,  CLIENT *clnt)
{
	static tipo_fraccion clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MULTI_FRACCIONES,
		(xdrproc_t) xdr_fracciones, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_fraccion, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_fraccion *
divi_fracciones_1(fracciones arg1,  CLIENT *clnt)
{
	static tipo_fraccion clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, DIVI_FRACCIONES,
		(xdrproc_t) xdr_fracciones, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_fraccion, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

tipo_fraccion *
simplificar_fraccion_1(fraccion arg1,  CLIENT *clnt)
{
	static tipo_fraccion clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SIMPLIFICAR_FRACCION,
		(xdrproc_t) xdr_fraccion, (caddr_t) &arg1,
		(xdrproc_t) xdr_tipo_fraccion, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
