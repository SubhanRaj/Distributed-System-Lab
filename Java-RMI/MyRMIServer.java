import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;

public class MyRMIServer extends UnicastRemoteObject implements MyRemoteInterface {
    protected MyRMIServer() throws RemoteException {
        super();
    }

    public String sayHello() throws RemoteException {
        return "Hello from the server!";
    }

    public static void main(String[] args) {
        try {
            MyRemoteInterface remoteObject = new MyRMIServer();

            // Create and start a registry on port 1098
            LocateRegistry.createRegistry(1098);

            // Bind the remote object's stub in the registry
            Naming.rebind("MyRemoteObject", remoteObject);

            System.out.println("Server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
