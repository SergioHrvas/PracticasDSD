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

    public void setRegistro(Registry reg) throws RemoteException, NotBoundException;

    public int getTotalDonadoReplica() throws RemoteException, NotBoundException;

    public void run() throws RemoteException, NotBoundException;

    public void setToken(boolean tk) throws RemoteException, NotBoundException;

    public void setOperando(boolean eo) throws RemoteException, NotBoundException;

    public void estanTodas() throws RemoteException, NotBoundException;

    public boolean getTieneToken()  throws RemoteException, NotBoundException;

    public boolean getEstaOperando()  throws RemoteException, NotBoundException;

	public boolean getV()  throws RemoteException, NotBoundException;

	public void setA(boolean b) throws RemoteException, NotBoundException;
};
