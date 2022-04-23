import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;
import java.util.*;

public class Donaciones extends UnicastRemoteObject implements iDonaciones, SDonaciones, Runnable {
    private int suma;
    private Map<Integer, Integer> registro = new HashMap<Integer, Integer>();
    private Map<Integer, Integer> suscripciones = new HashMap<Integer, Integer>();
    private boolean tieneToken, estaOperando;
    private int n_replica = -1;
    private static Registry reg;
    private boolean estanTodas;
    private boolean a = false;

    public Donaciones(int i) throws RemoteException {
        suma = 0;
        n_replica = i;
        estanTodas = false;
        if (n_replica == 0) {
            tieneToken = true;
        } else {
            tieneToken = false;
        }
        estaOperando = false;

    }

    public void estanTodas() {
        estanTodas = true;
        if (n_replica == 2) {
            for (int i = 0; i < 3; i++) {
                if (i != 2) {
                    SDonaciones s;
                    try {
                        s = (SDonaciones) reg.lookup("Replica" + i);
                        s.estanTodas();

                    } catch (RemoteException | NotBoundException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                }
            }

        }

    }

    public boolean getEstanTodas() {
        return estanTodas;
    }

    public void setRegistro(Registry reg) throws RemoteException, NotBoundException {
        Donaciones.reg = reg;

    }

    public void setToken(boolean tk) {
        tieneToken = tk;
    }

    public Boolean Donar(int id, int donado) throws RemoteException {
        Boolean hadonado = false, estaRegistrado = registro.containsKey(id);
        if (estaRegistrado) {
            suma += donado;
            registro.put(id, registro.get(id) + donado);
            hadonado = true;
        }
        return hadonado;
    }

    public int Registrar(int codigo) throws RemoteException, NotBoundException {
        Registry reg = LocateRegistry.getRegistry("127.0.0.1", 1099);
        SDonaciones d, min_d = (SDonaciones) this;
        int n_reg = -1, n_clientes = 0, min_clientes = Integer.MAX_VALUE;
        for (int k = 0; k < 3; k++) {
            if (k != n_replica) {
                d = (SDonaciones) reg.lookup("Replica" + k);
                n_clientes = d.getNumeroClientes();
            } else {
                d = (SDonaciones) this;
                n_clientes = getNumeroClientes();
            }
            if (n_clientes < min_clientes) {
                min_d = d;
                min_clientes = n_clientes;
            }
        }
        min_d.registroDirecto(codigo);
        n_reg = min_d.getNumReplica();
        return n_reg;
    }

    public int getNumReplica() {
        return n_replica;
    }

    public boolean getTieneToken() {
        return tieneToken;
    }

    public boolean getEstaOperando() {
        return estaOperando;
    }

    public void registroDirecto(int id) {
        System.out.println("Soy replica" + n_replica + " y registro al cliente " + id);
        registro.put(id, 0);

    }

    public int getNumeroClientes() {
        return registro.size();
    }

    public int consultarDonado(int id) throws RemoteException {
        return registro.get(id);
    }

    public int estaRegistrado(int id) throws RemoteException, NotBoundException {
        int n_reg = -1;
        if (estaRegistradoAqui(id)) {
            n_reg = n_replica;
        } else {
            n_reg = getReplicaRegistro(id);
        }
        return n_reg;
    }

    public int getReplicaRegistro(int id) throws RemoteException, NotBoundException {
        boolean registrado = false;
        int n_reg = -1;
        for (int k = 0; k < 3 && !registrado; k++) {
            if (k != n_replica) {
                SDonaciones d = (SDonaciones) reg.lookup("Replica" + k);
                registrado = d.estaRegistradoAqui(id);
                if (registrado) {
                    n_reg = k;
                }
            }
        }
        return n_reg;
    }

    public boolean estaRegistradoAqui(int id) {
        return registro.containsKey(id);
    }

    public int getTotalDonado() throws RemoteException, NotBoundException {
        int sumaTotal = 0;
        for (int i = 0; i < 3; i++) {
            if (i != n_replica) {
                SDonaciones d = (SDonaciones) reg.lookup("Replica" + i);
                sumaTotal += d.getTotalDonadoReplica();
            } else {
                sumaTotal += getTotalDonadoReplica();
            }
        }
        return sumaTotal;
    }

    public int getTotalDonadoReplica() {
        return suma;
    }

    public boolean getV() {
        return a;
    }

    @Override
    public void run() {
        System.out.println("Buscando el objeto remoto");
        try {

            while (true) {
                boolean tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
                boolean esta = ((SDonaciones) reg.lookup("Replica" + n_replica)).getEstaOperando();
                System.out.println("fuera:" + tiene + "- " + esta + "\n");
                while (esta) {
                    esta = ((SDonaciones) reg.lookup("Replica" + n_replica)).getEstaOperando();
                }
                /*
                 * for(int i = 0; i < 3; i++){
                 * System.out.println("| L | Tiene Token Replica " + i + " :"
                 * +((SDonaciones)reg.lookup("Replica"+i)).getTieneToken());
                 * }
                 */
                System.out.println("tras:" + tiene + "- " + esta + "\n");
                if (tiene && !esta) {
                    // System.out.println("AAAAAAA");
                    ((SDonaciones) reg.lookup("Replica" + n_replica)).setToken(false);
                    tieneToken = false;

                    ((SDonaciones) reg.lookup("Replica" + (n_replica + 1) % 3)).setToken(true);
                }
                /*
                 * Iterator it = suscripciones.keySet().iterator();
                 * while (it.hasNext()) {
                 * Integer indice = (Integer) it.next();
                 * Donar(indice, suscripciones.get(indice));
                 * }
                 */
                Random r = new Random();
                Thread.sleep(r.nextInt(2000 - 400 + 1) + 400);
                System.out.println("Termino de dormir");

            }
        } catch (Exception e) {
            System.err.println("Ejemplo_I exception:");
            e.printStackTrace();
        }
    }

    public boolean suscribirse(int id, int cantidad) throws RemoteException, NotBoundException {
        boolean suscrito = false;
        int dondeEstaRegistrado = estaRegistrado(id);
        if (dondeEstaRegistrado >= 0) {
            suscripciones.put(id, cantidad);
            suscrito = true;

            // implementacion de suscripcion
        }
        return suscrito;
    }

    public boolean estaSuscritoAqui(int id) {
        return suscripciones.containsKey(id);

    }

    public boolean desuscribirse(int id) throws RemoteException, NotBoundException {
        boolean desuscrito = false;
        int dondeEstaRegistrado = estaRegistrado(id);
        boolean estasuscrito = estaSuscritoAqui(id);
        if (dondeEstaRegistrado >= 0 && estasuscrito) {
            suscripciones.remove(id);
            desuscrito = true;

        }
        return desuscrito;
    }

    public void setOperando(boolean eo) {
        estaOperando = eo;
    }

    public void setA(boolean ax) {
        a = ax;
    }

    public void solicitar() throws AccessException, RemoteException, NotBoundException {
        System.out.println("| S | Esta Operando Replica " + n_replica + " :"
                + ((SDonaciones) reg.lookup("Replica" + n_replica)).getEstaOperando());
        System.out.println("| S | Tiene Token Replica " + n_replica + " :"
                + ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken());
        boolean tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
        while (tiene == false) {
            tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
        }
        // ((SDonaciones)reg.lookup("Replica"+n_replica)).setToken(true);
        ((SDonaciones) reg.lookup("Replica" + n_replica)).setOperando(true);

    }

    public void liberar() throws RemoteException, NotBoundException {
        ((SDonaciones) reg.lookup("Replica" + n_replica)).setA(true);

        System.out.println("| L | Esta Operando Replica " + n_replica + " :"
                + ((SDonaciones) reg.lookup("Replica" + n_replica)).getEstaOperando());
        System.out.println("| L | Tiene Token Replica " + n_replica + " :"
                + ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken());

        ((SDonaciones) reg.lookup("Replica" + n_replica)).setToken(false);
        ((SDonaciones) reg.lookup("Replica" + n_replica)).setOperando(false);
        ((SDonaciones) reg.lookup("Replica" + n_replica)).setA(false);
    }

}