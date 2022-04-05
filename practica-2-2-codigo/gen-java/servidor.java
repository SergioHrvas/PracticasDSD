import java.util.ArrayList;
import java.util.List;

import org.apache.thrift.TException;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;

// Implementar clase handler ( en este u en otro fichero )
class CalculadoraHandler implements Calculadora.Iface {
	TTransport transport;
	TProtocol protocol;
	Calculadora.Client client;


	CalculadoraHandler(){
		try {
			  this.transport = new TSocket("localhost", 9093);

			TProtocol protocol = new  TBinaryProtocol(transport);
			this.client = new Calculadora.Client(protocol);
	  	  
		  } catch (TException x) {
			x.printStackTrace();
		  } 
	}

	public void ping() throws TException {
		System.out.println("Me han hecho ping (Java)");
		this.transport.open();
		this.client.ping();
		this.transport.close();
	}

	public double resta(double a, double b) {
		System.out.println("He restado");
		return a - b;
	}

	public double suma(double a, double b) {
		System.out.println("He sumado");

		return a + b;
	}

	public double multiplicacion(double a, double b) {
		System.out.println("He multiplicado");

		return a * b;
	}

	public double division(double a, double b) {
		System.out.println("He dividido");

		return a / b;
	}

	public double potencia(double a, int b){
		System.out.println("He hecho una potencia");

		return Math.pow(a, b);
	}

	public double raices(double a, int b){
		System.out.println("He hecho una raíz n-sima");

		return Math.pow((double)a,1/(double)b);
	}

	private double funcionRepeticion(double x, int i){

		double r = 1.0;
		for (int k = i; k > 0; k--)
			r *= x;
		return r;
	}

	public double logaritmo(double n, int b){
		System.out.println("He hecho un logaritmo");
		double resultado = 0;

	
		double variable = 0;
		int i, precision = 10, repeticiones = 0;
		while (n != 1 && precision >= 0)
		{
			for (i = 0; n >= b; i++)
				n /= b;
			n = funcionRepeticion(n, 10);
			variable = 10 * (variable + i);
			precision--;
			repeticiones++;
		}
		resultado = (double)variable / funcionRepeticion(10, repeticiones);
		return resultado;
	}

	public List<Double> suma_vectores(List<Double> vector1, List<Double> vector2) {
		System.out.println("He sumado vectores");
		List<Double> resultado = new ArrayList<Double>();
		int tam = vector1.size();
		for (int i = 0; i < tam; i++) {
			resultado.add(vector1.get(i) + vector2.get(i));
		}
		return resultado;
	}

	public List<Double> resta_vectores(List<Double> vector1, List<Double> vector2) {
		System.out.println("He restado vectores");
		List<Double> resultado = new ArrayList<Double>();
		int tam = vector1.size();
		for (int i = 0; i < tam; i++) {
			resultado.add(vector1.get(i) - vector2.get(i));
		}
		return resultado;
	}

	public double producto_escalar(List<Double> vector1, List<Double> vector2) {
		System.out.println("He hecho el producto escalar");
		double resultado = 0;
		int tam = vector1.size();
		for (int i = 0; i < tam; i++) {
			resultado += vector1.get(i) * vector2.get(i);
		}
		return resultado;
	}

	public List<Double> multi_vector_escalar(List<Double> vector1, double escalar) {
		System.out.println("He multiplicado vector por escalar");
		List<Double> resultado = new ArrayList<Double>();
		int tam = vector1.size();
		for (int i = 0; i < tam; i++) {
			resultado.add(vector1.get(i) * escalar);
		}
		return resultado;
	}

	public List<Double> division_vector_escalar(List<Double> vector1, double escalar) {
		System.out.println("He dividido vector entre escalar");
		List<Double> resultado = new ArrayList<Double>();
		int tam = vector1.size();
		for (int i = 0; i < tam; i++) {
			resultado.add(vector1.get(i) / escalar);
		}
		return resultado;
	}

	public List<List<Double>> suma_matrices(List<List<Double>> matriz1, List<List<Double>> matriz2) throws TException {
		System.out.println("Llamo a la suma de matrices");
		this.transport.open();

		List <List<Double>> resultado = this.client.suma_matrices(matriz1, matriz2);
		
		this.transport.close();

		return resultado;
	}

	public List<List<Double>> resta_matrices(List<List<Double>> matriz1, List<List<Double>> matriz2) throws TException  {
		System.out.println("Llamo a la resta de matrices");
		this.transport.open();

		List <List<Double>> resultado = this.client.resta_matrices(matriz1, matriz2);
		
		this.transport.close();

		return resultado;
	}

	public List<List<Double>> producto_matrices(List<List<Double>> matriz1, List<List<Double>> matriz2) throws TException {
		System.out.println("Llamo al producto de matrices");
		this.transport.open();

		List <List<Double>> resultado = this.client.producto_matrices(matriz1, matriz2);
		
		this.transport.close();

		return resultado;
	}

	public List<List<Double>> multi_matriz_escalar(List<List<Double>> matriz1, double escalar) throws TException {
		System.out.println("Llamo al producto de matriz por escalar");
		this.transport.open();

		List <List<Double>> resultado = this.client.multi_matriz_escalar(matriz1, escalar);
		
		this.transport.close();

		return resultado;
	}

	public List<List<Double>> division_matriz_escalar(List<List<Double>> matriz1, double escalar) throws TException {
		System.out.println("Llamo a la divisón de matriz por escalar");
		
		this.transport.open();

		List <List<Double>> resultado = this.client.division_matriz_escalar(matriz1, escalar);
		
		this.transport.close();

		return resultado;
	}

	private int maximo_comun_divisor(int a, int b){
		System.out.println("Realizando máximo común divisor");

		int n1 = Math.abs(a);
		int n2 = Math.abs(b);
		if (n2 == 0)
		{
			return n1;
		}
	
		int resto;
		while (n2 != 0)
		{
			resto = n1 % n2;
			n1 = n2;
			n2 = resto;
		}
	
		return n1;
	}

	public Fraccion suma_fracciones(Fraccion f1, Fraccion f2){
		System.out.println("He hecho suma de fracciones");
		Fraccion resultado = new Fraccion();
		if(f1.den == f2.den){
			resultado.den = f1.den;
			resultado.num = f1.num + f1.num;
		}
		else{
			resultado.den = f1.den * f2.den;
			resultado.num = f1.num * f2.den + f2.num * f1.den;
		}

		int mcd = maximo_comun_divisor(resultado.num, resultado.den);
		resultado.den = resultado.den / mcd;
		resultado.num = resultado.num / mcd;
		System.out.println(""+resultado.num+"   "+resultado.den+"\n");
		return resultado;
	}

	public Fraccion resta_fracciones(Fraccion f1, Fraccion f2){
		System.out.println("He hecho resta de fracciones");

		Fraccion resultado = new Fraccion();
		if(f1.den == f2.den){
			resultado.den = f1.den;
			resultado.num = f1.num - f1.num;
		}
		else{
			resultado.den = f1.den * f2.den;
			resultado.num = f1.num * f2.den - f2.num * f1.den;
		}

		int mcd = maximo_comun_divisor(resultado.num, resultado.den);
		resultado.den = resultado.den / mcd;
		resultado.num = resultado.num / mcd;
		return resultado;
	}

	public Fraccion multiplicacion_fracciones(Fraccion f1, Fraccion f2){
		System.out.println("He hecho multiplicación de fracciones");

		Fraccion resultado = new Fraccion();
		resultado.num = f1.num * f2.num;
		resultado.den = f1.den * f2.den;
		return resultado;
	}

	public Fraccion division_fracciones(Fraccion f1, Fraccion f2){
		System.out.println("He hecho división de fracciones");

		Fraccion resultado = new Fraccion();
		resultado.num = f1.num * f2.den;
		resultado.den = f1.den * f2.num;
		return resultado;
	}

	public Fraccion simplificacion_fracciones(Fraccion f1){
		System.out.println("He hecho simplificación de fracciones");

		Fraccion resultado = new Fraccion();
		int mcd = maximo_comun_divisor(f1.num, f1.den);
		resultado.num = f1.num / mcd;
		resultado.den = f1.den / mcd;
		return resultado;
	}
}

