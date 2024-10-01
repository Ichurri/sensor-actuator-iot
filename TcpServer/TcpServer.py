import socket
import threading

def handle_manual_input(actuator_conn):
    while True:
        command = input("Enter command (ON/OFF): ")
        actuator_conn.sendall(command.encode())

def main():
    # Get the server's IP address and start the server
    host = socket.gethostbyname(socket.gethostname())
    port = 12345
    print(f"Server IP Address: {host}")

    # Create server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(2)
    print(f"Server started on port {port}")

    # Wait for connections from both ESP32 devices
    sensor_conn, sensor_addr = server_socket.accept()
    print(f"Connected to ESP32 sensor from {sensor_addr}")

    actuator_conn, actuator_addr = server_socket.accept()
    print(f"Connected to ESP32 actuator from {actuator_addr}")

    # Start thread for manual input handling
    manual_thread = threading.Thread(target=handle_manual_input, args=(actuator_conn,))
    manual_thread.start()

    try:
        # Process data from the sensor
        while True:
            sensor_data = sensor_conn.recv(1024).decode()
            if not sensor_data:
                break

            print(f"Received distance: {sensor_data} cm")
            try:
                distance = float(sensor_data)

                # Make decisions based on the distance
                if distance < 15.0:
                    actuator_conn.sendall(b"RED")  # Turn on red LED
                elif distance < 35.0:
                    actuator_conn.sendall(b"YELLOW")  # Turn on yellow LED
                elif distance < 60.0:
                    actuator_conn.sendall(b"GREEN")  # Turn on green LED
                else:
                    actuator_conn.sendall(b"OFF")  # Turn off all LEDs

            except ValueError:
                print(f"Invalid distance received: {sensor_data}")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Close all connections
        sensor_conn.close()
        actuator_conn.close()
        server_socket.close()
        print("Server closed.")

if __name__ == "__main__":
    main()
