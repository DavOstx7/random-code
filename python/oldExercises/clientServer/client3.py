import socket
import threading
import time
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    BLACK = '\33[30m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    WHITE = '\33[37m'
    UNDERLINE = '\033[4m'


IP = '127.0.0.1'
PORT = 8080

socket = socket.socket()
socket.connect((IP, PORT))
print(bcolors.HEADER + f"[+] Opened connection to ({IP},{PORT})" + bcolors.ENDC)

discard = False
MENU = """
-d    to discard broadcast messages
-ud   to recieve broadcast messages (ON by default)
"""

print(socket)
print(MENU)
def send():
    global discard
    print(bcolors.OKCYAN + f"Waiting for input to send: " + bcolors.ENDC)
    while True:
        message_to_send = input()
        if(message_to_send == "-d"):
            discard = True
        elif(message_to_send == "-ud"):
            discard = False
        else:
            socket.send(message_to_send.encode())
            time.sleep(0.5)


def recieve():

    while True:
        data = socket.recv(1024).decode()
        if (data):
            if("enter your name:" in data):
                print(data)
                name = input()
                socket.send(name.encode())
                t = threading.Thread(target=send)
                t.start()
            else:
                if(not discard):
                    print(data)
        time.sleep(0.5)


recieve()
socket.close()
