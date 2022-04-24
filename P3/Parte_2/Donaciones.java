import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map.Entry;

import java.util.*;

public class Donaciones extends UnicastRemoteObject implements IDonaciones, SDonaciones, Runnable{
    private int suma;
    private Map<Integer, Integer> registro = new HashMap<Integer, Integer>();
    private Map<Integer, Integer> suscripciones = new HashMap<Integer, Integer>();
    private boolean tieneToken, estaOperando;
    private int n_replica = -1;
    private static Registry reg;
    private boolean estanTodas;
    private int n_replicas;

    public Donaciones(int i, int n_rep) throws RemoteException {
        suma = 0;
        n_replica = i;
        n_replicas = n_rep;

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
        if (n_replica == n_replicas-1) {
            for (int i = 0; i < n_replicas; i++) {
                if (i != n_replicas-1) {
                    SDonaciones s;
                    try {
                        s = (SDonaciones) reg.lookup("Replica" + i);
                        s.estanTodas();

                    } catch (RemoteException | NotBoundException e) {
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

    public synchronized Boolean Donar(int id, int donado) throws RemoteException {
        Boolean hadonado = false, estaRegistrado = registro.containsKey(id);
        if (estaRegistrado) {
            System.out.println("Cliente " + id + " dona " + donado + "( + " + suma + " = " + (suma+donado) + ")");
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
        for (int k = 0; k < n_replicas; k++) {
            System.out.println(k);
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
        for (int k = 0; k < n_replicas && !registrado; k++) {
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
        for (int i = 0; i < n_replicas; i++) {
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

    @Override
    public void run() {
        System.out.println("Buscando el objeto remoto");
        try {
            int i = 0;
            while (true) {
                boolean tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
                boolean esta = ((SDonaciones) reg.lookup("Replica" + n_replica)).getEstaOperando();


                if (i == 10) {
                    while(!tiene){
                        tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
                    }
                    Iterator<Integer> it = suscripciones.keySet().iterator();
                    while(esta){
                        esta = ((SDonaciones) reg.lookup("Replica" + n_replica)).getEstaOperando();
                    }
                    ((SDonaciones) reg.lookup("Replica" + n_replica)).setOperando(true);
                    while (it.hasNext()) {
                        Integer indice = (Integer) it.next();
                        Donar(indice, suscripciones.get(indice));
                    }
                    ((SDonaciones) reg.lookup("Replica" + n_replica)).setOperando(false);

                    i = 0;
                }
                if (tiene && !esta) {
                    ((SDonaciones) reg.lookup("Replica" + n_replica)).setToken(false);
                    ((SDonaciones) reg.lookup("Replica" + (n_replica + 1) % n_replicas)).setToken(true);
                }
                Thread.sleep(200);
                System.out.println("Termino de dormir");
                i++;

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

    public void solicitar() throws AccessException, RemoteException, NotBoundException {
        boolean tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
        while (tiene == false) {
            tiene = ((SDonaciones) reg.lookup("Replica" + n_replica)).getTieneToken();
        }
        ((SDonaciones) reg.lookup("Replica" + n_replica)).setOperando(true);
    }

    public void liberar() throws RemoteException, NotBoundException {
        ((SDonaciones) reg.lookup("Replica" + n_replica)).setOperando(false);
    }

    public ArrayList<Integer> mayorDonacionLocal(){
        Iterator<Integer> it = registro.keySet().iterator();
        int mayor = 0, mayor_cantidad = 0;

        while (it.hasNext()) {
            Integer indice = (Integer) it.next();
            int cantidad = registro.get(indice);
            if(cantidad > mayor_cantidad){
                mayor_cantidad = cantidad;
                mayor = indice;
            }
        }
        ArrayList<Integer> pair = new ArrayList<>();
        pair.add(mayor);
        pair.add(mayor_cantidad);
        
        return pair;
    }
    public ArrayList<Integer> mayorDonacion() throws RemoteException, NotBoundException{
        int mayor = 0, mayor_cantidad = 0;

        for (int i = 0 ; i < n_replicas; i++) {
            ArrayList<Integer> pair = ((SDonaciones) reg.lookup("Replica"+i)).mayorDonacionLocal();
            int cantidad = pair.get(1);
            if(cantidad > mayor_cantidad){
                mayor_cantidad = cantidad;
                mayor = pair.get(0);
            }
    }
        ArrayList<Integer> resultado = new ArrayList<>();
        resultado.add(mayor);
        resultado.add(mayor_cantidad);
        
        return resultado;
    }
}