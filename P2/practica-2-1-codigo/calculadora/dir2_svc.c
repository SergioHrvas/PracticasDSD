/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "dir2.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static tipo_matriz_ult *
_suma_matrices_ult_1 (matrices_ult  *argp, struct svc_req *rqstp)
{
	return (suma_matrices_ult_1_svc(*argp, rqstp));
}

static tipo_matriz_ult *
_resta_matrices_ult_1 (matrices_ult  *argp, struct svc_req *rqstp)
{
	return (resta_matrices_ult_1_svc(*argp, rqstp));
}

static tipo_matriz_ult *
_producto_matrices_ult_1 (matrices_ult  *argp, struct svc_req *rqstp)
{
	return (producto_matrices_ult_1_svc(*argp, rqstp));
}

static tipo_matriz_ult *
_multi_matriz_escalar_ult_1 (matrizyescalar_ult  *argp, struct svc_req *rqstp)
{
	return (multi_matriz_escalar_ult_1_svc(*argp, rqstp));
}

static tipo_matriz_ult *
_divi_matriz_escalar_ult_1 (matrizyescalar_ult  *argp, struct svc_req *rqstp)
{
	return (divi_matriz_escalar_ult_1_svc(*argp, rqstp));
}

static void
dirprog_ult_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		matrices_ult suma_matrices_ult_1_arg;
		matrices_ult resta_matrices_ult_1_arg;
		matrices_ult producto_matrices_ult_1_arg;
		matrizyescalar_ult multi_matriz_escalar_ult_1_arg;
		matrizyescalar_ult divi_matriz_escalar_ult_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case SUMA_MATRICES_ULT:
		_xdr_argument = (xdrproc_t) xdr_matrices_ult;
		_xdr_result = (xdrproc_t) xdr_tipo_matriz_ult;
		local = (char *(*)(char *, struct svc_req *)) _suma_matrices_ult_1;
		break;

	case RESTA_MATRICES_ULT:
		_xdr_argument = (xdrproc_t) xdr_matrices_ult;
		_xdr_result = (xdrproc_t) xdr_tipo_matriz_ult;
		local = (char *(*)(char *, struct svc_req *)) _resta_matrices_ult_1;
		break;

	case PRODUCTO_MATRICES_ULT:
		_xdr_argument = (xdrproc_t) xdr_matrices_ult;
		_xdr_result = (xdrproc_t) xdr_tipo_matriz_ult;
		local = (char *(*)(char *, struct svc_req *)) _producto_matrices_ult_1;
		break;

	case MULTI_MATRIZ_ESCALAR_ULT:
		_xdr_argument = (xdrproc_t) xdr_matrizyescalar_ult;
		_xdr_result = (xdrproc_t) xdr_tipo_matriz_ult;
		local = (char *(*)(char *, struct svc_req *)) _multi_matriz_escalar_ult_1;
		break;

	case DIVI_MATRIZ_ESCALAR_ULT:
		_xdr_argument = (xdrproc_t) xdr_matrizyescalar_ult;
		_xdr_result = (xdrproc_t) xdr_tipo_matriz_ult;
		local = (char *(*)(char *, struct svc_req *)) _divi_matriz_escalar_ult_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (DIRPROG_ULT, DIRVER);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, DIRPROG_ULT, DIRVER, dirprog_ult_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DIRPROG_ULT, DIRVER, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, DIRPROG_ULT, DIRVER, dirprog_ult_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DIRPROG_ULT, DIRVER, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
