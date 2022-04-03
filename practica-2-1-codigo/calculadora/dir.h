/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DIR_H_RPCGEN
#define _DIR_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct operacion {
	float firstparam;
	float secondparam;
};
typedef struct operacion operacion;

struct operacion_2 {
	float firstparam;
	int secondparam;
};
typedef struct operacion_2 operacion_2;

struct vectores {
	struct {
		u_int v1_len;
		float *v1_val;
	} v1;
	struct {
		u_int v2_len;
		float *v2_val;
	} v2;
};
typedef struct vectores vectores;

struct vectoryescalar {
	struct {
		u_int v_len;
		float *v_val;
	} v;
	float num;
};
typedef struct vectoryescalar vectoryescalar;

struct fraccion {
	int num;
	int den;
};
typedef struct fraccion fraccion;

struct fracciones {
	fraccion f1;
	fraccion f2;
};
typedef struct fracciones fracciones;

struct matriz {
	struct {
		u_int v1_len;
		float *v1_val;
	} v1;
	int v1_f;
	int v1_c;
};
typedef struct matriz matriz;

struct matrices {
	struct {
		u_int v1_len;
		float *v1_val;
	} v1;
	int v1_f;
	int v1_c;
	struct {
		u_int v2_len;
		float *v2_val;
	} v2;
	int v2_f;
	int v2_c;
};
typedef struct matrices matrices;

struct matrizyescalar {
	struct {
		u_int v1_len;
		float *v1_val;
	} v1;
	int v1_f;
	int v1_c;
	float num;
};
typedef struct matrizyescalar matrizyescalar;

struct tipo_simple {
	int errno;
	union {
		float resultado;
	} tipo_simple_u;
};
typedef struct tipo_simple tipo_simple;

struct tipo_vector {
	int errno;
	union {
		struct {
			u_int resultado_len;
			float *resultado_val;
		} resultado;
	} tipo_vector_u;
};
typedef struct tipo_vector tipo_vector;

struct tipo_matriz {
	int errno;
	union {
		matriz m;
	} tipo_matriz_u;
};
typedef struct tipo_matriz tipo_matriz;

struct tipo_fraccion {
	int errno;
	union {
		fraccion f;
	} tipo_fraccion_u;
};
typedef struct tipo_fraccion tipo_fraccion;

#define DIRPROG 0x20000155
#define DIRVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define SUMA 1
extern  tipo_simple * suma_1(operacion , CLIENT *);
extern  tipo_simple * suma_1_svc(operacion , struct svc_req *);
#define RESTA 2
extern  tipo_simple * resta_1(operacion , CLIENT *);
extern  tipo_simple * resta_1_svc(operacion , struct svc_req *);
#define MULTIPLICACION 3
extern  tipo_simple * multiplicacion_1(operacion , CLIENT *);
extern  tipo_simple * multiplicacion_1_svc(operacion , struct svc_req *);
#define DIVISION 4
extern  tipo_simple * division_1(operacion , CLIENT *);
extern  tipo_simple * division_1_svc(operacion , struct svc_req *);
#define POTENCIA 5
extern  tipo_simple * potencia_1(operacion_2 , CLIENT *);
extern  tipo_simple * potencia_1_svc(operacion_2 , struct svc_req *);
#define RAIZ 6
extern  tipo_simple * raiz_1(operacion_2 , CLIENT *);
extern  tipo_simple * raiz_1_svc(operacion_2 , struct svc_req *);
#define LOGARITMO 7
extern  tipo_simple * logaritmo_1(operacion_2 , CLIENT *);
extern  tipo_simple * logaritmo_1_svc(operacion_2 , struct svc_req *);
#define SUMA_VECTORES 8
extern  tipo_vector * suma_vectores_1(vectores , CLIENT *);
extern  tipo_vector * suma_vectores_1_svc(vectores , struct svc_req *);
#define RESTA_VECTORES 9
extern  tipo_vector * resta_vectores_1(vectores , CLIENT *);
extern  tipo_vector * resta_vectores_1_svc(vectores , struct svc_req *);
#define PRODUCTO_ESCALAR 10
extern  tipo_simple * producto_escalar_1(vectores , CLIENT *);
extern  tipo_simple * producto_escalar_1_svc(vectores , struct svc_req *);
#define MULTI_VECTOR_ESCALAR 11
extern  tipo_vector * multi_vector_escalar_1(vectoryescalar , CLIENT *);
extern  tipo_vector * multi_vector_escalar_1_svc(vectoryescalar , struct svc_req *);
#define DIVI_VECTOR_ESCALAR 12
extern  tipo_vector * divi_vector_escalar_1(vectoryescalar , CLIENT *);
extern  tipo_vector * divi_vector_escalar_1_svc(vectoryescalar , struct svc_req *);
#define SUMA_MATRICES 13
extern  tipo_matriz * suma_matrices_1(matrices , CLIENT *);
extern  tipo_matriz * suma_matrices_1_svc(matrices , struct svc_req *);
#define RESTA_MATRICES 14
extern  tipo_matriz * resta_matrices_1(matrices , CLIENT *);
extern  tipo_matriz * resta_matrices_1_svc(matrices , struct svc_req *);
#define PRODUCTO_MATRICES 15
extern  tipo_matriz * producto_matrices_1(matrices , CLIENT *);
extern  tipo_matriz * producto_matrices_1_svc(matrices , struct svc_req *);
#define MULTI_MATRIZ_ESCALAR 16
extern  tipo_matriz * multi_matriz_escalar_1(matrizyescalar , CLIENT *);
extern  tipo_matriz * multi_matriz_escalar_1_svc(matrizyescalar , struct svc_req *);
#define DIVI_MATRIZ_ESCALAR 17
extern  tipo_matriz * divi_matriz_escalar_1(matrizyescalar , CLIENT *);
extern  tipo_matriz * divi_matriz_escalar_1_svc(matrizyescalar , struct svc_req *);
#define SUMA_FRACCIONES 18
extern  tipo_fraccion * suma_fracciones_1(fracciones , CLIENT *);
extern  tipo_fraccion * suma_fracciones_1_svc(fracciones , struct svc_req *);
#define RESTA_FRACCIONES 19
extern  tipo_fraccion * resta_fracciones_1(fracciones , CLIENT *);
extern  tipo_fraccion * resta_fracciones_1_svc(fracciones , struct svc_req *);
#define MULTI_FRACCIONES 20
extern  tipo_fraccion * multi_fracciones_1(fracciones , CLIENT *);
extern  tipo_fraccion * multi_fracciones_1_svc(fracciones , struct svc_req *);
#define DIVI_FRACCIONES 21
extern  tipo_fraccion * divi_fracciones_1(fracciones , CLIENT *);
extern  tipo_fraccion * divi_fracciones_1_svc(fracciones , struct svc_req *);
#define SIMPLIFICAR_FRACCION 22
extern  tipo_fraccion * simplificar_fraccion_1(fraccion , CLIENT *);
extern  tipo_fraccion * simplificar_fraccion_1_svc(fraccion , struct svc_req *);
extern int dirprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define SUMA 1
extern  tipo_simple * suma_1();
extern  tipo_simple * suma_1_svc();
#define RESTA 2
extern  tipo_simple * resta_1();
extern  tipo_simple * resta_1_svc();
#define MULTIPLICACION 3
extern  tipo_simple * multiplicacion_1();
extern  tipo_simple * multiplicacion_1_svc();
#define DIVISION 4
extern  tipo_simple * division_1();
extern  tipo_simple * division_1_svc();
#define POTENCIA 5
extern  tipo_simple * potencia_1();
extern  tipo_simple * potencia_1_svc();
#define RAIZ 6
extern  tipo_simple * raiz_1();
extern  tipo_simple * raiz_1_svc();
#define LOGARITMO 7
extern  tipo_simple * logaritmo_1();
extern  tipo_simple * logaritmo_1_svc();
#define SUMA_VECTORES 8
extern  tipo_vector * suma_vectores_1();
extern  tipo_vector * suma_vectores_1_svc();
#define RESTA_VECTORES 9
extern  tipo_vector * resta_vectores_1();
extern  tipo_vector * resta_vectores_1_svc();
#define PRODUCTO_ESCALAR 10
extern  tipo_simple * producto_escalar_1();
extern  tipo_simple * producto_escalar_1_svc();
#define MULTI_VECTOR_ESCALAR 11
extern  tipo_vector * multi_vector_escalar_1();
extern  tipo_vector * multi_vector_escalar_1_svc();
#define DIVI_VECTOR_ESCALAR 12
extern  tipo_vector * divi_vector_escalar_1();
extern  tipo_vector * divi_vector_escalar_1_svc();
#define SUMA_MATRICES 13
extern  tipo_matriz * suma_matrices_1();
extern  tipo_matriz * suma_matrices_1_svc();
#define RESTA_MATRICES 14
extern  tipo_matriz * resta_matrices_1();
extern  tipo_matriz * resta_matrices_1_svc();
#define PRODUCTO_MATRICES 15
extern  tipo_matriz * producto_matrices_1();
extern  tipo_matriz * producto_matrices_1_svc();
#define MULTI_MATRIZ_ESCALAR 16
extern  tipo_matriz * multi_matriz_escalar_1();
extern  tipo_matriz * multi_matriz_escalar_1_svc();
#define DIVI_MATRIZ_ESCALAR 17
extern  tipo_matriz * divi_matriz_escalar_1();
extern  tipo_matriz * divi_matriz_escalar_1_svc();
#define SUMA_FRACCIONES 18
extern  tipo_fraccion * suma_fracciones_1();
extern  tipo_fraccion * suma_fracciones_1_svc();
#define RESTA_FRACCIONES 19
extern  tipo_fraccion * resta_fracciones_1();
extern  tipo_fraccion * resta_fracciones_1_svc();
#define MULTI_FRACCIONES 20
extern  tipo_fraccion * multi_fracciones_1();
extern  tipo_fraccion * multi_fracciones_1_svc();
#define DIVI_FRACCIONES 21
extern  tipo_fraccion * divi_fracciones_1();
extern  tipo_fraccion * divi_fracciones_1_svc();
#define SIMPLIFICAR_FRACCION 22
extern  tipo_fraccion * simplificar_fraccion_1();
extern  tipo_fraccion * simplificar_fraccion_1_svc();
extern int dirprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operacion (XDR *, operacion*);
extern  bool_t xdr_operacion_2 (XDR *, operacion_2*);
extern  bool_t xdr_vectores (XDR *, vectores*);
extern  bool_t xdr_vectoryescalar (XDR *, vectoryescalar*);
extern  bool_t xdr_fraccion (XDR *, fraccion*);
extern  bool_t xdr_fracciones (XDR *, fracciones*);
extern  bool_t xdr_matriz (XDR *, matriz*);
extern  bool_t xdr_matrices (XDR *, matrices*);
extern  bool_t xdr_matrizyescalar (XDR *, matrizyescalar*);
extern  bool_t xdr_tipo_simple (XDR *, tipo_simple*);
extern  bool_t xdr_tipo_vector (XDR *, tipo_vector*);
extern  bool_t xdr_tipo_matriz (XDR *, tipo_matriz*);
extern  bool_t xdr_tipo_fraccion (XDR *, tipo_fraccion*);

#else /* K&R C */
extern bool_t xdr_operacion ();
extern bool_t xdr_operacion_2 ();
extern bool_t xdr_vectores ();
extern bool_t xdr_vectoryescalar ();
extern bool_t xdr_fraccion ();
extern bool_t xdr_fracciones ();
extern bool_t xdr_matriz ();
extern bool_t xdr_matrices ();
extern bool_t xdr_matrizyescalar ();
extern bool_t xdr_tipo_simple ();
extern bool_t xdr_tipo_vector ();
extern bool_t xdr_tipo_matriz ();
extern bool_t xdr_tipo_fraccion ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DIR_H_RPCGEN */
