from calculadora import Calculadora
from calculadora import ttypes

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
                print("Introduzca la operacion (ej: '4 + 5'):");
                print("Operaciones posibles: + | - | * | / | ^ | l | r");
                print("Formato: ( 3 ^ 4 ) para 3 elevado a 4");
                print("Formato: ( 3 l 4 ) para logaritmo de 3 en base 4");
                print("Formato: ( 3 r 4 ) para raiz cuarta de 3");
                operando1 = int(input())
                primeravez = 0

            operacion = input()

            if(operacion == "^" or operacion == "l" or operacion == "r"):
                operando2 = int(input())
            else:
                operando2 = input()
                
            if (operacion == "+"):
                resultado = client.suma(operando1, operando2)
            elif (operacion == "-"):
                resultado = client.resta(operando1, operando2)
            elif (operacion == "*"):
                resultado = client.multiplicacion(operando1, operando2)
            elif (operacion == "/"):
                resultado = client.division(operando1, operando2)
            elif (operacion == "l"):
                resultado = client.logaritmo(operando1, operando2)
            elif (operacion == "^"):
                resultado = client.potencia(operando1, operando2)
            elif (operacion == "r"):
                resultado = client.raices(operando1, operando2)

            print(f"{operando1} {operacion} {operando2} = {resultado}")

            print("\n¿Desea continuar?: ('s' para si | 'n' para no)")
            continuo = input()
            while(continuo != "s" and continuo != "n"):
                print("\n¿Desea continuar?: ('s' para si | 'n' para no)")
                continuo = input()




def operacionesFracciones():
    f1 = Calculadora.Fraccion()

    print("Introduzca la operación que desea realizar:")
    print("> Suma: +")
    print("> Resta: -")
    print("> Multiplicación: *")
    print("> División: /")
    print("> Simplificar: s")
    operacion = input()
    while ((operacion != "+") and (operacion != "-") and (operacion != "*") and (operacion != "/") and (operacion != "s")):
        print("Introduzca una operacion correcta: ")
        operacion = input()
		
    if (operacion != "s"):
        print("Introduzca el numerador de la primera fraccion:")
    else:
        print("Introduzca el numerador de la fraccion:")
    f1.num  = int(input())
    
    if (operacion != "s"):
        print("Introduzca el denominador de la segunda fraccion:")
    else:
        print("Introduzca el denominador de la fraccion:")
    f1.den = int(input())

    f2 = Calculadora.Fraccion()
    if (operacion != "s"):
        print("Introduzca el numerador de la segunda fracción:")
        f2.num = int(input())

        print("Introduzca el denominador de la segunda fracción:")
        f2.den = int(input())

    fres = Calculadora.Fraccion()
    if (operacion == "+"):
        fres = client.suma_fracciones(f1, f2)
    elif(operacion == "-"):
        fres = client.resta_fracciones(f1, f2)
    elif(operacion == "*"):
        fres = client.multiplicacion_fracciones(f1, f2)
    elif(operacion == "/"):
        fres = client.division_fracciones(f1, f2)
    elif(operacion == "s"):
        fres = client.simplificacion_fracciones(f1)

    if(operacion!="s"):
        print(f"        {f1.num}                 {f2.num}                       {fres.num}")
        print(f" ------------   {operacion} ----------------  ======  ------------")
        print(f"        {f1.den}                 {f2.den}                       {fres.den}")
    else:
        print(f"   {f1.num}                            {fres.num}")
        print(f"  ------------    ======   ------------")
        print(f"   {f1.den}                            {fres.den}")



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







transport = TSocket.TSocket("localhost", 9091)
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
    print("Operaciones con fracciones: f")
    print("Operaciones con vectores: v")
    print("Operaciones con matrices: m")
    print("Salir: q\n")
    opcion = input()
    while(opcion != 'i' and opcion != 's' and opcion != 'f' and opcion!= 'v' and opcion != 'm' and opcion != 'q'):
        print("Introduzca una opción correcta:")
        print("Operaciones simples: s")
        print("Operaciones simples (interactivo): i")
        print("Operaciones con fracciones: f")
        print("Operaciones con vectores: v")
        print("Operaciones con matrices: m")
        print("Salir: q\n")
        opcion = input()
    
        
    if(opcion == 's' or opcion == 'i'):
        operacionesSimples()        
    elif(opcion == 'v'):
        operacionesVectores()
    elif(opcion == 'v'):
        operacionesVectores()
    elif(opcion == 'f'):
        operacionesFracciones()
    elif(opcion == 'm'):
        operacionesMatrices()

transport.close()


'''    opcion = input()
    if(opcion == 's'):
        resultado = client.suma(1, 1)
        print("1 + 1 = " + str(resultado))
        resultado = client.resta(1, 1)
        print("1 - 1 = " + str(resultado))'''