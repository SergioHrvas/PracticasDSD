struct Fraccion {
   1: required i32 num,
   2: required i32 den
}

service Calculadora{
   void ping(),
   double suma(1:double num1, 2:double num2),
   double resta(1:double num1, 2:double num2),
   double multiplicacion(1:double num1, 2:double num2);
   double division(1:double num1, 2:double num2);
   double raices(1:double num1, 2:i32 num2);
   double potencia(1:double num1, 2:i32 num2);
   double logaritmo(1:double num1, 2:i32 num2);
   list<double> suma_vectores(1:list<double> vector1, 2:list<double> vector2);
   list<double> resta_vectores(1:list<double> vector1, 2:list<double> vector2);
   double producto_escalar(1:list<double> vector1, 2:list<double> vector2);
   list<double> multi_vector_escalar(1:list<double> vector1, 2:double escalar);
   list<double> division_vector_escalar(1:list<double> vector1, 2:double escalar);
   list<list<double>> suma_matrices(1:list<list<double>> matriz1, 2:list<list<double>> matriz2);
   list<list<double>> resta_matrices(1:list<list<double>> matriz1, 2:list<list<double>> matriz2);
   list<list<double>> producto_matrices(1:list<list<double>> matriz1, 2:list<list<double>> matriz2);
   list<list<double>> multi_matriz_escalar(1:list<list<double>> matriz1, 2:double escalar);
   list<list<double>> division_matriz_escalar(1:list<list<double>> matriz1, 2:double escalar);
   Fraccion suma_fracciones(1:Fraccion f1, 2:Fraccion f2);
   Fraccion resta_fracciones(1:Fraccion f1, 2:Fraccion f2);
   Fraccion multiplicacion_fracciones(1:Fraccion f1, 2:Fraccion f2);
   Fraccion division_fracciones(1:Fraccion f1, 2:Fraccion f2);
   Fraccion simplificacion_fracciones(1:Fraccion f1);
}

