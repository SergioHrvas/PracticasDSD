from calculadora import Calculadora

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol



def operacionesSimples():
        resultado = 0
        continuo = 's'
        primeravez = 1
        while (continuo != 'n'):
            if (primeravez != 1):
                operando1 = resultado
                print(operando1)

            if (primeravez):
                print("Introduzca la operacion (ej: '4 + 5'):\n");
                operando1 = int(input())
                primeravez = 0

            operacion =input()

            operando2 = int(input())
            if (operacion == "+"):
                resultado = client.suma(operando1, operando2)
            elif (operacion == "-"):
                resultado = client.resta(operando1, operando2)
            elif (operacion == "*"):
                resultado = client.multiplicacion(operando1, operando2)
            elif (operacion == "/"):
                resultado = client.division(operando1, operando2)

            print(f"{operando1} {operacion} {operando2} = {resultado}")

            print("\n¿Desea continuar?: ('s' para si | 'n' para no)\n");
            continuo = input()
            while(continuo != 's' and continuo != 'n'):
                print("\n¿Desea continuar?: ('s' para si | 'n' para no)\n");
                continuo = input()




    

transport = TSocket.TSocket("localhost", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)

transport.open()

print("hacemos ping al server")
client.ping()

opcion = input();
while (opcion != 's'):
    print("=======CALCULADORA========")
    print("Operaciones simples: s")
    print("Operaciones con polinomios: p")
    print("Operaciones con vectores: v")
    print("Operaciones con matrices: m")
    print("Salir: q\n")
    opcion = input()
    while(opcion != 's' and opcion != 'p' and opcion!= 'v' and opcion != 'm' and opcion != 'q'):
        print("Introduzca una opción correcta:")
        print("Operaciones simples: s")
        print("Operaciones con polinomios: p")
        print("Operaciones con vectores: v")
        print("Operaciones con matrices: m")
        print("Salir: q\n")
        opcion = input()
    
        
    if(opcion == 's'):
        operacionesSimples()        
    


transport.close()


'''    opcion = input()
    if(opcion == 's'):
        resultado = client.suma(1, 1)
        print("1 + 1 = " + str(resultado))
        resultado = client.resta(1, 1)
        print("1 - 1 = " + str(resultado))'''