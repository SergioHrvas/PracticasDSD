import java.rmi.registry.LocateRegistry;
import java.rmi.*;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
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

            // Pide el número de réplicas para poder pedirle a alguna de ellas
            // (aleatoriamente) el registro
            int num_replicas = ((IDonaciones) mireg.lookup("Replica0")).getNumReplicas();
            Random r = new Random();
            int i = r.nextInt(num_replicas);
            IDonaciones donaciones = (IDonaciones) mireg.lookup("Replica" + i);
            int opcion = -1;
            Scanner in = new Scanner(System.in); // Create a Scanner object
            int donado = 0;
            int n_replica = 0;
            System.out.println("===== SERVIDOR DE DONACIONES =====");
            System.out.println("Introduzca su número de cliente: ");
            int n_cliente = in.nextInt();
            while (n_cliente < 0) {
                System.out.println("Introduzca un número válido de cliente: ");
                n_cliente = in.nextInt();
            }
            while (opcion != 0) {
                System.out.println("Seleccione una de las siguientes opciones: ");
                System.out.println("--> Registrarse en el sistema: 1");
                System.out.println("--> Realizar una donación: 2");
                System.out.println("--> Suscribirse: 3");
                System.out.println("--> Desuscribirse: 4");
                System.out.println("--> Consultar cantidad que ha donado: 5");
                System.out.println("--> Consultar donado en total: 6");
                System.out.println("--> Consultar mayor donador: 7");
                System.out.println("--> Salir: 0");
                opcion = in.nextInt();
                while (opcion < 0 || opcion > 7) {
                    System.out.println("Introduzca una opción correcta: ");
                    System.out.println("--> Registrarse en el sistema: 1");
                    System.out.println("--> Realizar una donación: 2");
                    System.out.println("--> Suscribirse: 3");
                    System.out.println("--> Desuscribirse: 4");
                    System.out.println("--> Consultar cantidad que ha donado: 5");
                    System.out.println("--> Consultar donado en total: 6");
                    System.out.println("--> Consultar mayor donador: 7");
                    System.out.println("--> Salir: 0");
                    opcion = in.nextInt();
                }

                switch (opcion) {
                    case 1: // REGISTRARSE

                        n_replica = donaciones.estaRegistrado(n_cliente);
                        // Registro del usuario
                        if (n_replica < 0) {

                            System.out.println("Petición a réplica " + i);
                            n_replica = donaciones.Registrar(n_cliente);
                            System.out.println(n_replica);
                        }
                        // Cambio de ŕéplica a la que está registrado
                        donaciones = (IDonaciones) mireg.lookup("Replica" + n_replica);

                        break;
                    case 2: // DONAR
                        System.out.println("Introduzca la cantidad que desea donar: ");
                        int cantidad = in.nextInt();
                        donaciones.solicitar();

                        // Donación
                        System.out.println("Registrado en Réplica " + n_replica);
                        boolean hedonado = donaciones.Donar(n_cliente, cantidad);
                        if (hedonado) {
                            System.out.println("Donación de " + cantidad + "€ realizada");
                        } else {
                            System.out.println("La donación no ha sido realizada.");
                        }
                        donaciones.liberar();
                        break;
                    case 3: // Suscribirse
                        System.out.println("Introduzca la cantidad con la que se desea suscribir: ");
                        cantidad = in.nextInt();
                        boolean hasuscrito = donaciones.suscribirse(n_cliente, cantidad);
                        if (hasuscrito) {
                            System.out.println("Suscripción realizada con éxito");
                        } else {
                            System.out.println("La suscripción no ha sido realizada.");
                        }
                        break;
                    case 4: // Desuscribirse
                        boolean hadesuscrito = donaciones.desuscribirse(n_cliente);
                        if (hadesuscrito) {
                            System.out.println("Desuscripción realizada con éxito");
                        } else {
                            System.out.println("La desuscripción no ha sido realizada");
                        }
                        break;
                    case 5: // Consultar cantidad que ha donado
                        donaciones.solicitar();
                        donado = donaciones.getDonado(n_cliente);
                        donaciones.liberar();
                        System.out.println("He donado a la causa " + donado + "€ en total");

                        break;
                    case 6: // Consultar cantidad total donada en el servidor
                        donaciones.solicitar();
                        donado = donaciones.getTotalDonado();
                        donaciones.liberar();
                        System.out.println("En total se han donado " + donado + "€ en el servidor");
                        break;
                    case 7: // Consultar quién es el mayor donador

                        donaciones.solicitar();
                        ArrayList<Integer> mayorDonacion = donaciones.mayorDonacion();
                        donaciones.liberar();
                        System.out.println(
                                "Mayor donacion hecha por " + mayorDonacion.get(0) + " de " + mayorDonacion.get(1));
                        break;
                }
            }

        } catch (NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
}