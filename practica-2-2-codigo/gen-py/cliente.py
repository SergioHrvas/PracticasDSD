from calculadora import Calculadora

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def operacionesSimples():
        resultado = 0
        continuo = "s"
        primeravez = 1
        interactivo = 0
        if (opcion == 's'):
            interactivo = 0
        else:
            interactivo = 1

        while (continuo != "n"):

            if (primeravez != 1 and interactivo == 1):
                operando1 = resultado
                print(operando1)

            if (primeravez or interactivo == 0):
                print("Introduzca la operacion (ej: '4 + 5'):")
                operando1 = int(input())
                primeravez = 0

            operacion = input()

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

            print("\n¿Desea continuar?: ('s' para si | 'n' para no)")
            continuo = input()
            while(continuo != "s" and continuo != "n"):
                print("\n¿Desea continuar?: ('s' para si | 'n' para no)")
                continuo = input()




def operacionesVectores():
    print("Introduzca la operación que desea realizar:")
    print("> Suma: +")
    print("> Resta: -")
    print("> Producto escalar: *")
    print("> Multiplicación por escalar: m")
    print("> División por escalar: d")
    operacion = input()
    while ((operacion != "+") and (operacion != "-") and (operacion != "*") and (operacion != "m") and (operacion != "d")):
        print("Introduzca una operacion correcta: ")
        operacion = input()
		
    if (operacion != "m" and operacion != "d"):
        print("Introduzca el tamaño de los vectores:")
    else:
        print("Introduzca el tamaño del vector:")

    tam = int(input())
    while (tam <= 0):
        print("Tamaño incorrecto, debe ser mayor que 0. Vuelva a intentarlo")
        tam = input()

    if(operacion != "m" and operacion != "d"):
        print("Introduzca los elementos del primer vector:")
    else:
        print("Introduzca los elementos del vector:")

    vector1 = []
    vector2 = []

    for k in range(tam):
        vector1.append(float(input()))


    if (operacion != "m" and operacion != "d"):
        print("Introduzca los elementos del segundo vector:")
        for k in range(tam):
            vector2.append(float(input()))
    else:
        print("Introduzca un número:")
        escalar = float(input())


    if (operacion == "+"):
        resultado = client.suma_vectores(vector1, vector2)
    elif(operacion == "-"):
        resultado = client.resta_vectores(vector1, vector2)
    elif(operacion == "*"):
        resultado = client.producto_escalar(vector1, vector2)
    elif(operacion == "m"):
        resultado = client.multi_vector_escalar(vector1, escalar)
    elif(operacion == "d"):
        resultado = client.division_vector_escalar(vector1, escalar)

    if(operacion!="*"):
        for k in range(tam):
            print(f"{resultado[k]}")
    else:
        print(f"{resultado}")


def operacionesMatrices():
    print("Introduzca la operación que desea realizar:")
    print("> Suma: +")
    print("> Resta: -")
    print("> Producto: *")
    print("> Multiplicación por escalar: m")
    print("> División por escalar: d")
    operacion = input()
    while ((operacion != "+") and (operacion != "-") and (operacion != "*") and (operacion != "m") and (operacion != "d")):
        print("Introduzca una operacion correcta: ")
        operacion = input()
	
    if (operacion == "+" and operacion == "-"):
        print("Introduzca el tamaño por filas de las matrices:")
    elif(operacion == "*"):
        print("Introduzca el tamaño por filas de la primera matriz:")
    else:
        print("Introduzca el tamaño por filas de la matriz:")
		
    tamfilas1 = int(input())
    while (tamfilas1 <= 0):
        print("Tamaño incorrecto, debe ser mayor que 0. Vuelva a intentarlo")
        tamfilas1 = int(input())

    if (operacion == "+" and operacion == "-"):
        print("Introduzca el tamaño por columnas de las matrices:")
    elif (operacion == "*"):
        print("Introduzca el tamaño por columnas de la primera matriz:")
    else:
        print("Introduzca el tamaño por columnas de la matriz:")

    tamcolumnas1 = int(input())
    while (tamcolumnas1 <= 0):
        print("Tamaño incorrecto, debe ser mayor que 0. Vuelva a intentarlo")
        tamcolumnas1 = int(input())

    if (operacion == "*"):
        print("Introduzca el tamaño por filas de la segunda matriz:")
        tamfilas2 = int(input())
        while (tamfilas2 <= 0):
            print("Tamaño incorrecto, debe ser mayor que 0. Vuelva a intentarlo")
            tamfilas2 = int(input())
        print("Introduzca el tamaño por columnas de la segunda matriz:")
        tamcolumnas2 = int(input())
        while (tamcolumnas2 <= 0):
            print("Tamaño incorrecto, debe ser mayor que 0. Vuelva a intentarlo")
            tamcolumnas2 = int(input())
    elif (operacion == "+" or operacion == "-"):
        tamfilas2 = tamfilas1
        tamcolumnas2 = tamcolumnas1

    if (operacion != "m" and operacion != "d"):
        print("Introduzca los elementos de la primera matriz:")
    else:
        print("Introduzca los elementos de la matriz:")
		
    print("(Fila por fila)")
    matriz1 = []
    matriz2 = []

    for f in range(tamfilas1):
        fila = []
        for c in range(tamcolumnas1):
            fila.append(float(input()))
        matriz1.append(fila)

    if (operacion == "*" or operacion == "+" or operacion == "-"):
        print("Introduzca los elementos de la segunda matriz:")
        print("(Fila por fila)")

        for f in range(tamfilas2):
            fila = []
            for c in range(tamcolumnas2):
                fila.append(float(input()))
            matriz2.append(fila)
        
        for f in range(tamfilasres):
            for c in range(tamcolumnasres):
                print(f"{matriz1[f][c]}", end = ' ')
            print("\n")   

        print("\toperacion")
        
        for f in range(tamfilasres):
            for c in range(tamcolumnasres):
                print(f"{matriz2[f][c]}", end = ' ')
            print("\n")    
 

    elif(operacion == "m" or operacion == "d"):
        print("Introduzca un número: ")
        escalar = float(input())

        for f in range(tamfilasres):
            for c in range(tamcolumnasres):
                print(f"{matriz1[f][c]}", end = ' ')
            print("\n")    

        print(f"\t{operacion}")

        print(f"{escalar}")




            
    tamfilasres=tamfilas1
    tamcolumnasres=tamcolumnas1
    if(operacion=="+"):
        resultado = client.suma_matrices(matriz1, matriz2)
    elif(operacion=="-"):
        resultado = client.resta_matrices(matriz1, matriz2)
    elif(operacion=="*"):
        resultado = client.producto_matrices(matriz1, matriz2)
        tamfilasres=tamfilas1
        tamcolumnasres=tamcolumnas2
    elif(operacion=="m"):
        resultado = client.multi_matriz_escalar(matriz1, escalar)
    elif(operacion=="d"):
        resultado = client.division_matriz_escalar(matriz1, escalar)
    print("=============")
    for f in range(tamfilasres):
        for c in range(tamcolumnasres):
            print(f"{resultado[f][c]}", end = ' ')
        print("\n")    







transport = TSocket.TSocket("localhost", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)

transport.open()

print("hacemos ping al server")
client.ping()

opcion = ''
while (opcion != 'q'):
    print("=======CALCULADORA========")
    print("Operaciones simples: s")
    print("Operaciones simples (interactivo): i")
    print("Operaciones con fracciones: p")
    print("Operaciones con vectores: v")
    print("Operaciones con matrices: m")
    print("Salir: q\n")
    opcion = input()
    while(opcion != 'i' and opcion != 's' and opcion != 'p' and opcion!= 'v' and opcion != 'm' and opcion != 'q'):
        print("Introduzca una opción correcta:")
        print("Operaciones simples: s")
        print("Operaciones simples (interactivo): i")
        print("Operaciones con fracciones: p")
        print("Operaciones con vectores: v")
        print("Operaciones con matrices: m")
        print("Salir: q\n")
        opcion = input()
    
        
    if(opcion == 's' or opcion == 'i'):
        operacionesSimples()        
    elif(opcion == 'v'):
        operacionesVectores()
    elif(opcion == 'm'):
        operacionesMatrices()

transport.close()


'''    opcion = input()
    if(opcion == 's'):
        resultado = client.suma(1, 1)
        print("1 + 1 = " + str(resultado))
        resultado = client.resta(1, 1)
        print("1 - 1 = " + str(resultado))'''