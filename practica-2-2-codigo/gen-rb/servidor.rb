require 'thrift'

require './calculadora'
require './calculadora_types'
require './calculadora_constants'

class CalculadoraHandler
  def initialize()


    end

  def ping()
    puts "Me han hecho ping (Ruby)"
  end

    def suma_matrices(n1, n2)
        puts "Servidor de ruby suma las matrices"

        resultado = Array.new(n1.length())

        for i in (0..n1.size()-1)
            resultado[i] = Array.new(n1[0].length())
        end

        tamfilas = n1.size();
        tamcolumnas = n1[0].size();

        for f in (0..tamfilas-1)
            for c in (0..tamcolumnas-1) 
                resultado[f][c] = n1[f][c] + n2[f][c]
            end
        end

        return resultado

    end

    def resta_matrices(n1, n2)
        puts "Servidor de ruby resta las matrices"

        resultado = Array.new(n1.length())

        for i in (0..n1.size()-1)
            resultado[i] = Array.new(n1[0].length())
        end

        tamfilas = n1.size();
        tamcolumnas = n1[0].size();

        for f in (0..tamfilas-1)
            for c in (0..tamcolumnas-1) 
                resultado[f][c] = n1[f][c] - n2[f][c]
            end
        end

        return resultado

    end

    def producto_matrices(n1, n2)
        puts "Servidor de ruby suma las matrices"

        resultado = Array.new(n1.length())

        for i in (0..n1.size()-1)
            resultado[i] = Array.new(n1[0].length())
        end

        tamfilas = n1.size();
        tamcolumnas = n1[0].size();

        for f in (0..tamfilas-1)
            for c in (0..tamcolumnas-1) 
                resultado[f][c] = n1[f][c] + n2[f][c]
            end
        end

        return resultado

    end

    def matriz_por_escalar(n1, n2)
        puts "Servidor de ruby suma las matrices"

        resultado = Array.new(n1.length())

        for i in (0..n1.size()-1)
            resultado[i] = Array.new(n1[0].length())
        end

        tamfilas = n1.size();
        tamcolumnas = n1[0].size();

        for f in (0..tamfilas-1)
            for c in (0..tamcolumnas-1) 
                resultado[f][c] = n1[f][c] * n2
            end
        end

        return resultado

    end

    def matriz_entre_escalar(n1, n2)
        puts "Servidor de ruby suma las matrices"

        resultado = Array.new(n1.length())

        for i in (0..n1.size()-1)
            resultado[i] = Array.new(n1[0].length())
        end

        tamfilas = n1.size();
        tamcolumnas = n1[0].size();

        for f in (0..tamfilas-1)
            for c in (0..tamcolumnas-1) 
                resultado[f][c] = n1[f][c] / n2
            end
        end

        return resultado

    end

end

handler = CalculadoraHandler.new()
processor = Calculadora::Processor.new(handler)
transport = Thrift::ServerSocket.new(9092)
transportFactory = Thrift::BufferedTransportFactory.new()
server = Thrift::SimpleServer.new(processor, transport, transportFactory)

puts "Servidor 2 iniciando..."
server.serve()
puts "done."
