import socket
import threading

# Definir los estados
states = {
    'STATE_RED': 'RED',
    'STATE_YELLOW': 'YELLOW',
    'STATE_GREEN': 'GREEN',
    'STATE_BLUE': 'BLUE'
}

current_state = None  # Estado actual

def handle_sensor(sensor_conn, actuator_conn):
    global current_state  # Hacer la variable global

    try:
        while True:
            print("Esperando datos del sensor...")  # Depuración adicional
            data = sensor_conn.recv(1024)  # Recibe los datos del sensor
            if not data:
                print("Sensor desconectado.")
                break  # Sale del bucle cuando el sensor se desconecta

            state = data.decode().strip()  # Decodificar los datos recibidos
            print(f"Estado recibido del sensor: {state}")

            # Solo enviar el nuevo estado al actuador si es diferente del actual
            if state != current_state:
                print(f"Nuevo estado detectado: {state}. Enviando al actuador.")
                actuator_conn.sendall(state.encode())
                current_state = state

    except Exception as e:
        print(f"Error en el manejo del sensor: {e}")
    finally:
        print("Cerrando conexión del sensor.")
        sensor_conn.close()

def handle_actuator(actuator_conn):
    try:
        while True:
            print("Esperando datos del actuador...")  # Depuración adicional
            state = actuator_conn.recv(1024).decode().strip()
            if not state:
                break
            print(f"Actuador recibió: {state}")
    except Exception as e:
        print(f"Error en el manejo del actuador: {e}")
    finally:
        print("Cerrando conexión del actuador.")
        actuator_conn.close()

def main():
    host = socket.gethostbyname(socket.gethostname())  # Obtener la IP del servidor
    port = 1234
    print(f"Dirección IP del servidor: {host}")

    # Crear el socket del servidor
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Reutilizar la dirección del socket
    server_socket.bind((host, port))
    server_socket.listen(2)
    print(f"Servidor iniciado en el puerto {port}")

    # Conectar el sensor
    sensor_conn, sensor_addr = server_socket.accept()
    print(f"Conectado al sensor desde {sensor_addr}")

    # Conectar el actuador
    actuator_conn, actuator_addr = server_socket.accept()
    print(f"Conectado al actuador desde {actuator_addr}")

    # Manejar la comunicación con el sensor y el actuador en threads separados
    sensor_thread = threading.Thread(target=handle_sensor, args=(sensor_conn, actuator_conn))
    actuator_thread = threading.Thread(target=handle_actuator, args=(actuator_conn,))
    
    sensor_thread.start()
    actuator_thread.start()

    # Esperar a que ambos threads terminen
    sensor_thread.join()
    actuator_thread.join()

    server_socket.close()

if __name__ == "__main__":
    main()
