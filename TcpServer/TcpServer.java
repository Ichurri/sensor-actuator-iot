import java.io.*;
import java.net.*;
import java.util.Scanner;

public class TcpServer {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        Socket sensorSocket = null;
        Socket actuatorSocket = null;
        final Scanner scanner = new Scanner(System.in);  // Mark scanner as final

        try {
            // Get the server's IP address
            String serverIP = InetAddress.getLocalHost().getHostAddress();
            System.out.println("Server IP Address: " + serverIP);

            // Start the server on port 12345
            serverSocket = new ServerSocket(12345);
            System.out.println("Server started on port 12345");

            // Wait for connections from both ESP32 devices
            sensorSocket = serverSocket.accept();
            System.out.println("Connected to ESP32 sensor");
            actuatorSocket = serverSocket.accept();
            System.out.println("Connected to ESP32 actuator");

            // Create streams for communication
            BufferedReader sensorInput = new BufferedReader(new InputStreamReader(sensorSocket.getInputStream()));
            PrintWriter actuatorOutput = new PrintWriter(actuatorSocket.getOutputStream(), true);

            // Start a thread to handle manual input from the PC
            new Thread(() -> {
                while (true) {
                    System.out.println("Enter command (ON/OFF): ");
                    String command = scanner.nextLine();  // Allow use of scanner
                    actuatorOutput.println(command);
                }
            }).start();

            // Process data from the sensor
            String sensorData;
            while ((sensorData = sensorInput.readLine()) != null) {
                System.out.println("Received distance: " + sensorData + " cm");
                double distance = Double.parseDouble(sensorData);

                // Make decisions based on the distance
                if (distance < 15.0) {
                    actuatorOutput.println("RED");  // Turn on red LED
                } else if (distance < 35.0) {
                    actuatorOutput.println("YELLOW");  // Turn on yellow LED
                } else if (distance < 60.0) {
                    actuatorOutput.println("GREEN");  // Turn on green LED
                } else {
                    actuatorOutput.println("OFF");  // Turn off all LEDs
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            // Close all resources
            try {
                if (sensorSocket != null && !sensorSocket.isClosed()) {
                    sensorSocket.close();
                }
                if (actuatorSocket != null && !actuatorSocket.isClosed()) {
                    actuatorSocket.close();
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
