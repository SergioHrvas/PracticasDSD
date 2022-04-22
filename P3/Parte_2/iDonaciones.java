import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface iDonaciones extends Remote {
    Boolean Donar(int id, int donado) throws RemoteException;

    int Registrar(int valor) throws RemoteException, NotBoundException;

    public int ConsultarDonado(int id) throws RemoteException;

    public int estaRegistrado(int id) throws RemoteException, NotBoundException;

    public int getTotalDonado() throws RemoteException, NotBoundException;

    public boolean suscribirse(int id, int cantidad) throws RemoteException, NotBoundException;

    public void solicitar() throws RemoteException, NotBoundException;

    public void liberar() throws RemoteException, NotBoundException;

    public boolean desuscribirse(int id) throws RemoteException, NotBoundException;
}