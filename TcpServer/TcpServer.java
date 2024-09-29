import java.io.*;
import java.net.*;
import java.util.Scanner;

public class TcpServer {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        Socket sensorSocket = null;
        Socket actuadorSocket = null;
        final Scanner scanner = new Scanner(System.in);  // Hacer final

        try {
            // Iniciar el servidor en el puerto 12345
            serverSocket = new ServerSocket(12345);
            System.out.println("Servidor iniciado en el puerto 12345");

            // Esperar conexiones de ambos ESP32
            sensorSocket = serverSocket.accept();
            System.out.println("Conectado al ESP32 sensor");
            actuadorSocket = serverSocket.accept();
            System.out.println("Conectado al ESP32 actuador");

            // Flujos para la comunicación
            BufferedReader sensorInput = new BufferedReader(new InputStreamReader(sensorSocket.getInputStream()));
            PrintWriter actuadorOutput = new PrintWriter(actuadorSocket.getOutputStream(), true);

            // Iniciar un thread para manejar entradas manuales desde la PC
            new Thread(() -> {
                while (true) {
                    System.out.println("Ingrese comando (ON/OFF): ");
                    String command = scanner.nextLine();  // Ya se puede usar scanner
                    actuadorOutput.println(command);
                }
            }).start();

            // Procesar datos del sensor
            String sensorData;
            while ((sensorData = sensorInput.readLine()) != null) {
                System.out.println("Distancia recibida: " + sensorData + " cm");
                double distance = Double.parseDouble(sensorData);

                // Tomar decisiones basadas en la distancia
                if (distance < 20.0) {
                    actuadorOutput.println("ON"); // Encender actuador si la distancia es menor a 20 cm
                } else {
                    actuadorOutput.println("OFF"); // Apagar actuador si la distancia es mayor a 20 cm
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            // Cerrar todos los recursos
            try {
                if (sensorSocket != null && !sensorSocket.isClosed()) {
                    sensorSocket.close();
                }
                if (actuadorSocket != null && !actuadorSocket.isClosed()) {
                    actuadorSocket.close();
                }
                if (serverSocket != null && !serverSocket.isClosed()) {
                    serverSocket.close();
                }
                if (scanner != null) {
                    scanner.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
