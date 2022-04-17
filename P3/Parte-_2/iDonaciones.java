import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface iDonaciones extends Remote {
    Boolean Donar(int id, int donado) throws RemoteException;

    int Registrar(int valor) throws RemoteException, NotBoundException;

    public int ConsultarDonado(int id) throws RemoteException;

    public int estaRegistrado(int id) throws RemoteException, NotBoundException;

}