import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;

public interface SDonaciones extends Remote {
    
    public int estaRegistrado(int id) throws RemoteException, NotBoundException;

    public boolean estaRegistradoAqui(int id) throws RemoteException, NotBoundException;

    public int getNumeroClientes() throws RemoteException;

    public void registroDirecto(int id) throws RemoteException;

    public int getNumReplica() throws RemoteException;

    public int getReplicaRegistro(int id) throws RemoteException, NotBoundException;

    public void setRegistro(Registry reg) throws RemoteException;
};
