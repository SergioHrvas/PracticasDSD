import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

public interface IDonaciones extends Remote {

    // Método para donar una cantidad
    Boolean Donar(int id, int donado) throws RemoteException;

    // Método para registrar al usuario en el sistema
    int Registrar(int valor) throws RemoteException, NotBoundException;

    // Método para comprobar si el usuario está registrado en el servidor
    public int estaRegistrado(int id) throws RemoteException, NotBoundException;

    // Método para consultar lo donado por el usuario en el sistema
    public int getDonado(int id) throws RemoteException;

    // Método para comprobar el total donado en todo el servidor
    public int getTotalDonado() throws RemoteException, NotBoundException;

    // Método para obtener el número de réplicas del servidor
    int getNumReplicas() throws RemoteException, NotBoundException;

    // Método para suscribirse (donación periódica)
    public boolean suscribirse(int id, int cantidad) throws RemoteException, NotBoundException;

    // Método para desuscribirse
    public boolean desuscribirse(int id) throws RemoteException, NotBoundException;

    // Método para solicitar la exclusión mutua
    public void solicitar() throws RemoteException, NotBoundException;

    // Método para salir de la exclusión mutua
    public void liberar() throws RemoteException, NotBoundException;

    // Método para consultar la mayor donación realizada en todo el servidor
    public ArrayList<Integer> mayorDonacion() throws RemoteException, NotBoundException;
}