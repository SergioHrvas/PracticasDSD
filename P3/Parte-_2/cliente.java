import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.*;
import java.rmi.registry.Registry;
import java.util.Random;

public class cliente {
    public static void main(String[] args) {
        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            // Crea el stub para el cliente especificando el nombre del servidor
            Registry mireg = LocateRegistry.getRegistry("127.0.0.1", 1099);
            Random r = new Random();
            int i = r.nextInt(2);
            iDonaciones donaciones = (iDonaciones) mireg.lookup("Replica" + i);

            int n_replica = donaciones.estaRegistrado(Integer.parseInt(args[0]));
            if (n_replica < 0) {

                System.out.println("Petición a réplica" + i);
                n_replica = donaciones.Registrar(Integer.parseInt(args[0]));
            }
            System.out.println(n_replica);
            donaciones = (iDonaciones) mireg.lookup("Replica" + n_replica);

            System.out.println("Registrado en replica" + n_replica);
            System.out.println(donaciones.Donar(Integer.parseInt(args[0]), 100));

            int donado = donaciones.ConsultarDonado(Integer.parseInt(args[0]));
            System.out.println(donado);

        } catch (NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
}