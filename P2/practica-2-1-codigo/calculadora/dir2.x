

 struct matrices_ult{
	 float v1<>;
	 int v1_f;
	 int v1_c;
	 float v2<>;
	 int v2_f;
	 int v2_c;
 };
 	
 struct matrizyescalar_ult{
	 float v1<>;
	 int v1_f;
	 int v1_c;
	 float num;
 };
 
  struct matriz_ult{
 	float v1<>;
	 int v1_f;
	 int v1_c;
 };


union tipo_matriz_ult switch (int errno){
	case 0:
		matriz_ult m;
	default:
		void;
};


program DIRPROG_ULT {
	version DIRVER {
		tipo_matriz_ult SUMA_MATRICES_ULT(matrices_ult) = 1;
		tipo_matriz_ult RESTA_MATRICES_ULT(matrices_ult) = 2;	
		tipo_matriz_ult PRODUCTO_MATRICES_ULT(matrices_ult) = 3;
		tipo_matriz_ult MULTI_MATRIZ_ESCALAR_ULT(matrizyescalar_ult) = 4;
		tipo_matriz_ult DIVI_MATRIZ_ESCALAR_ULT(matrizyescalar_ult) = 5;

	} =1;
} = 0x20000156;

