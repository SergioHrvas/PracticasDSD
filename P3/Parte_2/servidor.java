import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;

//import contador.contador;
public class servidor {
    public static void main(String[] args) throws AlreadyBoundException, InterruptedException, NotBoundException {
        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            Registry reg;
            Donaciones d = new Donaciones(Integer.parseInt(args[0]));

            if (Integer.parseInt(args[0]) < 3 && Integer.parseInt(args[0]) >= 0) {
                // Crea una instancia de contador

                if (Integer.parseInt(args[0]) != 0)
                    reg = LocateRegistry.getRegistry("127.0.0.1", 1099);
                else {
                    reg = LocateRegistry.createRegistry(1099);
                }

                // suma = 0;
                reg.bind("Replica" + args[0], d);
                d.setRegistro(reg);
                if(Integer.parseInt(args[0]) == 2)
                    d.estanTodas();
                // Hebras suscriptoras
                Thread hebra = new Thread(d, "adsdf");

                while(!d.getEstanTodas()){
                    System.out.println("Soy replica" + args[0] + " y " + d.getEstanTodas());

                }

                hebra.start();

                System.out.println("Servidor Donaciones | MalformedURLExceptiondor preparado");
                hebra.join();
            } else {
                System.out.println("Argumentos no válidos.");
            }
        } catch (RemoteException e) {
            System.out.println("Exception: " + e);
        }

    }
}
