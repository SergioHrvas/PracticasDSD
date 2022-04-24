import java.rmi.registry.LocateRegistry;
import java.rmi.*;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Map;
import java.util.Random;
import java.util.Map.Entry;

import javax.xml.crypto.dsig.keyinfo.KeyValue;

/*
java -cp . -Djava.security.policy=server.policy servidor 0
java -cp . -Djava.security.policy=server.policy servidor 1
java -cp . -Djava.security.policy=server.policy servidor 2

java -cp . -Djava.security.policy=server.policy cliente 0
java -cp . -Djava.security.policy=server.policy cliente 1

*/
public class Cliente {
    public static void main(String[] args) throws InterruptedException {
        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            // Crea el stub para el cliente especificando el nombre del servidor
            Registry mireg = LocateRegistry.getRegistry("127.0.0.1", 1099);
            Random r = new Random();
            int i = r.nextInt(2);
            IDonaciones donaciones = (IDonaciones) mireg.lookup("Replica" + i);

            int n_replica = donaciones.estaRegistrado(Integer.parseInt(args[0]));
            if (n_replica < 0) {

                System.out.println("Petición a réplica " + i);
                n_replica = donaciones.Registrar(Integer.parseInt(args[0]));
                System.out.println(n_replica);
            }
            donaciones = (IDonaciones) mireg.lookup("Replica" + n_replica);
            donaciones.solicitar();

            System.out.println("Registrado en Réplica " + n_replica);
            boolean hedonado = donaciones.Donar(Integer.parseInt(args[0]), 100);
            if (hedonado) {
                System.out.println("Donación realizada");
            }

            int donado = donaciones.consultarDonado(Integer.parseInt(args[0]));
            System.out.println("He donado " + donado + "€");

            int totalDonado = donaciones.getTotalDonado();

            System.out.println("En total se han donado " + totalDonado + "€ en el servidor");
            Thread.sleep(5000);
            donaciones.liberar();

            // SUSCRIPCION
            System.out.println("Me suscribo");
            donaciones.suscribirse(Integer.parseInt(args[0]), 100);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);
            Thread.sleep(3000);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);
            Thread.sleep(3000);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);
            Thread.sleep(3000);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            Thread.sleep(3000);
            donaciones.desuscribirse(Integer.parseInt(args[0]));
            System.out.println("Me desuscribo");
            totalDonado = donaciones.getTotalDonado();

            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            Thread.sleep(3000);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);
            Thread.sleep(3000);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);
            Thread.sleep(3000);
            totalDonado = donaciones.getTotalDonado();
            donado = donaciones.consultarDonado(Integer.parseInt(args[0]));

            System.out.println("He donado " + donado);
            System.out.println("Se han donado " + totalDonado);

            ArrayList<Integer> mayorDonacion = donaciones.mayorDonacion();
            System.out.println("Mayor donacion hecha por " + mayorDonacion.get(0) + " de " + mayorDonacion.get(1));
        } catch (NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
}