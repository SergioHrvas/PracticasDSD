service Calculadora{
   void ping(),
   double suma(1:double num1, 2:double num2),
   double resta(1:double num1, 2:double num2),
   double multiplicacion(1:double num1, 2:double num2);
   double division(1:double num1, 2:double num2);
   list<double> suma_vectores(1:list<double> vector1, 2:list<double> vector2);
   list<double> resta_vectores(1:list<double> vector1, 2:list<double> vector2);
   list<double> multiplicacion_vectores(1:list<double> vector1, 2:list<double> vector2);
   list<double> division_vectores(1:list<double> vector1, 2:list<double> vector2);

}
