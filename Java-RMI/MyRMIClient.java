import java.rmi.Naming;

public class MyRMIClient {
    public static void main(String[] args) {
        try {
            MyRemoteInterface remoteObject = (MyRemoteInterface) Naming.lookup("//localhost/MyRemoteObject");

            String response = remoteObject.sayHello();
            System.out.println("Response from server: " + response);
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
