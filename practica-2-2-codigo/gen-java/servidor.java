import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.apache.thrift.TException;
import org.apache.thrift.transport.TSSLTransportFactory;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TSSLTransportFactory.TSSLTransportParameters;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;

// Importar cosas

// Implementar clase handler ( en este u en otro fichero )
class CalculadoraHandler implements Calculadora.Iface {
	TTransport transport;
	TProtocol protocol;
	Calculadora.Client client;


	CalculadoraHandler(){
		try {
			  this.transport = new TSocket("localhost", 9092);

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

	public List<List<Double>> resta_matrices(List<List<Double>> matriz1, List<List<Double>> matriz2) {
		System.out.println("He hecho la resta de matrices");

		List<List<Double>> resultado = new ArrayList<List<Double>>();
		for (int i = 0; i < matriz1.size(); i++) {
			resultado.add(new ArrayList<Double>());
		}

		int tamfilas = matriz1.size();
		int tamcolumnas = matriz1.get(0).size();

		for (int f = 0; f < tamfilas; f++) {
			for (int c = 0; c < tamcolumnas; c++) {
				resultado.get(f).add(matriz1.get(f).get(c) - matriz2.get(f).get(c));
			}
		}
		return resultado;
	}

	public List<List<Double>> producto_matrices(List<List<Double>> matriz1, List<List<Double>> matriz2) {
		System.out.println("He hecho el producto de matrices");
		List<List<Double>> resultado = new ArrayList<List<Double>>();
		int tamfilas = 0, tamcolumnas = 0;

		if (matriz1.get(0).size() == matriz2.size()) {
			tamcolumnas = matriz2.get(0).size();
			tamfilas = matriz1.size();
		}
		System.out.println("f" + tamfilas);
		System.out.println("c" + tamcolumnas);
		for (int i = 0; i < tamfilas; i++) {
			resultado.add(new ArrayList<Double>());
		}

		double suma = 0;

		for (int f = 0; f < tamfilas; f++) {
			for (int c = 0; c < tamcolumnas; c++) {
				suma = 0;
				for (int k = 0; k < matriz1.get(0).size(); k++) {
					suma += matriz1.get(f).get(k) * matriz2.get(k).get(c);
				}
				resultado.get(f).add(suma);
			}
		}
		/*
		 * for(int f = 0; f < matriz1.size(); f++){
		 * for(int c = 0; c < matriz2.get(0).size(); c++){
		 * System.out.println(resultado.get(f).get(c) + " ");
		 * }
		 * System.out.println("\n");
		 * }
		 */
		return resultado;
	}

	public List<List<Double>> multi_matriz_escalar(List<List<Double>> matriz1, double matriz2) {
		System.out.println("He hecho el producto escalar");

		List<List<Double>> resultado = new ArrayList<List<Double>>();
		for (int i = 0; i < matriz1.size(); i++) {
			resultado.add(new ArrayList<Double>());
		}

		int tamfilas = matriz1.size();
		int tamcolumnas = matriz1.get(0).size();

		for (int f = 0; f < tamfilas; f++) {
			for (int c = 0; c < tamcolumnas; c++) {
				resultado.get(c).add(matriz1.get(f).get(c));
			}
		}
		return resultado;
	}

	public List<List<Double>> division_matriz_escalar(List<List<Double>> matriz1, double matriz2) {
		System.out.println("He hecho el producto escalar");

		List<List<Double>> resultado = new ArrayList<List<Double>>();
		for (int i = 0; i < matriz1.size(); i++) {
			resultado.add(new ArrayList<Double>());
		}

		int tamfilas = matriz1.size();
		int tamcolumnas = matriz1.get(0).size();

		for (int f = 0; f < tamfilas; f++) {
			for (int c = 0; c < tamcolumnas; c++) {
				resultado.get(c).add(matriz1.get(f).get(c));
			}
		}
		return resultado;
	}
}
