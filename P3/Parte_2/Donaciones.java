import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;
import java.util.*;
import java.net.MalformedURLException;

public class Donaciones extends UnicastRemoteObject implements iDonaciones, SDonaciones, Runnable {
    private int suma;
    private Map<Integer, Integer> registro = new HashMap<Integer, Integer>();
    private Map<Integer, Integer> suscripciones = new HashMap<Integer, Integer>();

    private int n_replica = -1;
    private static Registry reg;

    public Donaciones(int i) throws RemoteException {
        suma = 0;
        n_replica = i;

    }

    public void setRegistro(Registry reg) throws RemoteException {
        Donaciones.reg = reg;
    }

    public Boolean Donar(int id, int donado) throws RemoteException {
        Boolean hadonado = false;
        Boolean estaRegistrado = registro.containsKey(id);
        if (estaRegistrado) {
            suma += donado;
            registro.put(id, registro.get(id) + donado);
            hadonado = true;
        }
        return hadonado;
    }

    public int Registrar(int codigo) throws RemoteException, NotBoundException {
        Registry reg = LocateRegistry.getRegistry("127.0.0.1", 1099);
        SDonaciones d;
        SDonaciones min_d = (SDonaciones) this;
        int n_reg = -1;

        int n_clientes = 0, min_clientes = Integer.MAX_VALUE;
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

    public void registroDirecto(int id) {
        System.out.println("Soy replica" + n_replica + " y registro al cliente " + id);
        registro.put(id, 0);

    }

    public int getNumeroClientes() {
        return registro.size();
    }

    public int ConsultarDonado(int id) throws RemoteException {
        return registro.get(id);
    }

    public int estaRegistrado(int id) throws RemoteException, NotBoundException {
        int n_reg = -1;
        if (registro.containsKey(id)) {
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
            }
            else{
                sumaTotal += getTotalDonadoReplica();
            }
        }

        return sumaTotal;
    }

    public int getTotalDonadoReplica() {
        return suma;
    }
    
    @Override
    public void run(){
        System.out.println("Buscando el objeto remoto");
        try {
            while(true){
            Iterator it = suscripciones.keySet().iterator();
            while(it.hasNext()){
                Integer indice = (Integer) it.next();
                Donar(indice, suscripciones.get(indice));
            }
            Thread.sleep(2000);
            System.out.println("Termino de dormir");
        }
        } catch (Exception e) {
            System.err.println("Ejemplo_I exception:");
            e.printStackTrace();
        }
    }

    public boolean suscribirse(int id, int cantidad) throws RemoteException, NotBoundException{
        boolean suscrito = false;
        int dondeEstaRegistrado = estaRegistrado(id);
        if(dondeEstaRegistrado>=0){
            suscripciones.put(id, cantidad);
            suscrito = true;
            

            //implementacion de suscripcion
        }
        return suscrito;
    }

    public boolean estaSuscritoAqui(int id){
        return suscripciones.containsKey(id);

    }
    public boolean desuscribirse(int id) throws RemoteException, NotBoundException{
        boolean desuscrito = false;
        int dondeEstaRegistrado = estaRegistrado(id);
        boolean estasuscrito = estaSuscritoAqui(id); 
        if(dondeEstaRegistrado>=0 && estasuscrito){
            suscripciones.remove(id);
            desuscrito = true;
            
        }
        return desuscrito;
    }
}