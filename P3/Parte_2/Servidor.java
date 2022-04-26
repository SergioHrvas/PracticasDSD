import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

//import contador.contador;
public class Servidor {
    public static void main(String[] args) throws AlreadyBoundException, InterruptedException, NotBoundException {
        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            Registry reg;
            int n_replicas = Integer.parseInt(args[1]);

            if (Integer.parseInt(args[0]) < n_replicas && Integer.parseInt(args[0]) >= 0) {

                //Creo u obtengo el registro
                if (Integer.parseInt(args[0]) != 0)
                    reg = LocateRegistry.getRegistry("127.0.0.1", 1099);
                else {
                    reg = LocateRegistry.createRegistry(1099);
                }

                //Creo la réplica y la añado al registro
                Donaciones d = new Donaciones(Integer.parseInt(args[0]), n_replicas);
                reg.bind("Replica" + args[0], d);
                d.setRegistro(reg);
                if (Integer.parseInt(args[0]) == n_replicas - 1)
                    d.estanTodas();

                // Creo y lanzo hebra para la suscripción y para el intercambio del token
                Thread hebra = new Thread(d, "Hebra" + args[0]);
                SDonaciones don = (SDonaciones) reg.lookup("Replica" + args[0]);
                boolean estan = don.getEstanTodas();
                while (!estan) {
                    don = (SDonaciones) reg.lookup("Replica" + args[0]);
                    estan = don.getEstanTodas();
                }

                hebra.start();

                System.out.println("Servidor Donaciones | MalformedURLExceptiondor preparado");

                //Espero a que lleguen las hebras
                hebra.join();
            } else {
                System.out.println("Argumentos no válidos.");
            }
        } catch (RemoteException e) {
            System.out.println("Exception: " + e);
        }

    }
}
