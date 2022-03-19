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

struct tipo {
	int errno;
	union {
		float resultado;
	} tipo_u;
};
typedef struct tipo tipo;

#define DIRPROG 0x20000155
#define DIRVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define SUMA 1
extern  tipo * suma_1(operacion , CLIENT *);
extern  tipo * suma_1_svc(operacion , struct svc_req *);
#define RESTA 2
extern  tipo * resta_1(operacion , CLIENT *);
extern  tipo * resta_1_svc(operacion , struct svc_req *);
#define MULTIPLICACION 3
extern  tipo * multiplicacion_1(operacion , CLIENT *);
extern  tipo * multiplicacion_1_svc(operacion , struct svc_req *);
#define DIVISION 4
extern  tipo * division_1(operacion , CLIENT *);
extern  tipo * division_1_svc(operacion , struct svc_req *);
extern int dirprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define SUMA 1
extern  tipo * suma_1();
extern  tipo * suma_1_svc();
#define RESTA 2
extern  tipo * resta_1();
extern  tipo * resta_1_svc();
#define MULTIPLICACION 3
extern  tipo * multiplicacion_1();
extern  tipo * multiplicacion_1_svc();
#define DIVISION 4
extern  tipo * division_1();
extern  tipo * division_1_svc();
extern int dirprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operacion (XDR *, operacion*);
extern  bool_t xdr_tipo (XDR *, tipo*);

#else /* K&R C */
extern bool_t xdr_operacion ();
extern bool_t xdr_tipo ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DIR_H_RPCGEN */
