from calculadora import Calculadora

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

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
    operacion = input()
    if(operacion == 's'):
        resultado = client.suma(1, 1)
        print("1 + 1 = " + str(resultado))
        resultado = client.resta(1, 1)
        print("1 - 1 = " + str(resultado))
    
    
    
    
    print("")
    opcion = input()


transport.close()

