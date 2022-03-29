from calculadora import Calculadora

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol



def operacionesSimples():
        resultado = 0
        continuo = 0
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

            print(f"{operando1} {operacion} {operando2} = {resultado}")

'''      else if (operacion == '*')
            {
                multiplicacion_1_arg1.firstparam = operando1;
                multiplicacion_1_arg1.secondparam = operando2;
                result_3 = multiplicacion_1(multiplicacion_1_arg1, clnt);
                if (result_3 == (tipo_simple *)NULL)
                {
                    clnt_perror(clnt, "call failed");
                }
                resultado = (*result_3).tipo_simple_u.resultado;
            }
            else if (operacion == '/')
            {
                division_1_arg1.firstparam = operando1;
                division_1_arg1.secondparam = operando2;
                result_4 = division_1(division_1_arg1, clnt);
                if (result_4 == (tipo_simple *)NULL)
                {
                    clnt_perror(clnt, "call failed");
                }
                resultado = (*result_4).tipo_simple_u.resultado;
            }

            printf("%f", resultado);
            printf("\n¿Desea continuar?: ('s' para si | 'n' para no)\n");
            scanf("%c", &continuo);
            while (continuo != 's' && continuo != 'n')
            {
                scanf("%c", &continuo);
            }

        primeravez = 1;
        continuo = 0;
        printf("\n");
        break;'''

    

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