import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.util.ArrayList;

public interface SDonaciones extends Remote {

    //Método para comprobar si un cliente está registrado en una réplica específica
    public boolean estaRegistradoAqui(int id) throws RemoteException, NotBoundException;

    //Método para obtener el número de clientes que hay registrados
    public int getNumeroClientes() throws RemoteException;

    //Método para realizar el registro en una réplica
    public void registroDirecto(int id) throws RemoteException;

    //Método para obtener el número de la réplica
    public int getNumReplica() throws RemoteException;

    //Método para obtener la réplica donde está registrado el cliente
    public int getReplicaRegistro(int id) throws RemoteException, NotBoundException;

    //Método para obtener la cantidad total donada en una réplica
    public int getTotalDonadoReplica() throws RemoteException, NotBoundException;

    //Establecer token
    public void setToken(boolean tk) throws RemoteException, NotBoundException;

    //Establecer variable estaOperando
    public void setOperando(boolean eo) throws RemoteException, NotBoundException;

    //Verificar si están todas las réplicas activas
    public void estanTodas() throws RemoteException, NotBoundException;

    //Obtener si la réplica tiene el token
    public boolean getTieneToken()  throws RemoteException, NotBoundException;

    //Obtener si la réplica está operando
    public boolean getEstaOperando()  throws RemoteException, NotBoundException;

    //Obtener si están todas las réplicas activas
    public boolean getEstanTodas() throws RemoteException, NotBoundException;

    //Solicitar la exclusión mutua
    public void solicitar() throws RemoteException, NotBoundException;

    //Salir de la exclusión mutua
    public void liberar() throws RemoteException, NotBoundException;

    //Obtener la mayor donación en la réplica (id del usuario y cantidad donada)
    public ArrayList<Integer> mayorDonacionLocal() throws RemoteException, NotBoundException;
};
