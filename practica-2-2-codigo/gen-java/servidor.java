// Importar cosas


// Implementar clase handler ( en este u en otro fichero )
class CalculadoraHandler implements Calculadora.Iface {
public void ping (){
	System.out.println ( " Me han hecho ping " );
}

public int resta(int a, int b){
	return a-b;
}

public int suma ( int a , int b ){
	return a + b ;
}
}
