import socket
import threading

username = input("Enter your name / username: ")

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 55555))

def recieve():
    while True:
        try:
            message = client_socket.recv(1024).decode('ascii')
            if message == 'USER':
                client_socket.send(username.encode('ascii'))
            elif message == '':
                print("left the chat, closing connection!")
                client_socket.close()
                break
            else:
                print(message)
        except:
            print("An error has occured (you might have been kicked), closing connection!")
            client_socket.close()
            break

def write():
    while True:
        message = f'{input("")}'
        client_socket.send(message.encode('ascii'))

receive_thread = threading.Thread(target = recieve)
receive_thread.start()


write_thread = threading.Thread(target = write)
write_thread.start()

receive_thread.join()
