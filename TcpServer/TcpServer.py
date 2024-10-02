import socket
import threading

states = {
    'STATE_RED': 'RED',
    'STATE_YELLOW': 'YELLOW',
    'STATE_GREEN': 'GREEN',
    'STATE_BLUE': 'BLUE'
}

current_state = None  

def handle_sensor(sensor_conn, actuator_conn):
    global current_state  

    try:
        while True:
            data = sensor_conn.recv(1024)  
            if not data:
                print("Sensor disconnected.")
                break  

            print(f"State received from sensor: {state}")

            if state != current_state:
                print(f"New state detected: {state}. Sending to actuator.")
                actuator_conn.sendall(state.encode())
                current_state = state

    except Exception as e:
        print(f"Error handling sensor: {e}")
    finally:
        print("Closing sensor connection.")
        sensor_conn.close()

def handle_actuator(actuator_conn):
    try:
        while True:
            state = actuator_conn.recv(1024).decode().strip()
            if not state:
                break
            print(f"Actuator received: {state}")
    except Exception as e:
        print(f"Error handling actuator: {e}")
    finally:
        print("Closing actuator connection.")
        actuator_conn.close()

def main():
    host = socket.gethostbyname(socket.gethostname())  
    port = 1234
    print(f"Server IP address: {host}")

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 
    server_socket.bind((host, port))
    server_socket.listen(2)
    print(f"Server started on port {port}")

    sensor_conn, sensor_addr = server_socket.accept()
    print(f"Connected to sensor from {sensor_addr}")

    actuator_conn, actuator_addr = server_socket.accept()
    print(f"Connected to actuator from {actuator_addr}")

    sensor_thread = threading.Thread(target=handle_sensor, args=(sensor_conn, actuator_conn))
    actuator_thread = threading.Thread(target=handle_actuator, args=(actuator_conn,))
    
    sensor_thread.start()
    actuator_thread.start()

    sensor_thread.join()
    actuator_thread.join()

    server_socket.close()

main()
