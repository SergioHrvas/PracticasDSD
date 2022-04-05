import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TServerTransport;

public class Main { 
    public static void main(String[] args){
        // Lanzar el servidor en el static void main ()
        try {
            TServerTransport serverTransport = new TServerSocket (9091);
            TServer server = new TSimpleServer ( new TServer.Args (serverTransport).processor( new Calculadora.Processor<>(new CalculadoraHandler()) ));
            
            System.out.println( " Iniciando servidor ... " );
            server.serve();
        } catch ( Exception e ) {
            e.printStackTrace ();	}
    }
    
    
    }