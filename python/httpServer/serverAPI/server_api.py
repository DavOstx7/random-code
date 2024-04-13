from serverAPI.server_client_handler import IClientHandler
import socket
import threading
from typing import List

IP = "0.0.0.0"
PORT = 8080
CONCURRENT_CLIENTS_NUMBER = 10


class ServerAPI:
    def __init__(self, listen_ip: str, listen_port: int) -> None:
        listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        listen_socket.bind((listen_ip, listen_port))
        self.listen_socket = listen_socket
        self.working_sockets: List[socket.socket] = list()

    def handle_new_client(self, client_socket: socket.socket, client_address, client_handler: IClientHandler) -> None:
        try:
            client_handler.handle_client(client_socket, client_address)
        except Exception as e:
            raise Exception(e.args) from e
            print(e)
            self.working_sockets.remove(client_socket)
            print(f"[-] {client_address} disconnected or lost connection from the server ")

    def start_server(self, client_handler: IClientHandler) -> None:
        self.listen_socket.listen(CONCURRENT_CLIENTS_NUMBER)
        print(f"[+] Started server! listening on {self.listen_socket}")
        while True:
            client_socket, address = self.listen_socket.accept()
            thread = threading.Thread(target=self.handle_new_client, args=(client_socket, address, client_handler))
            thread.start()
            self.working_sockets.append(client_socket)

