import socket

host = socket.gethostname()
port = 2004
BUFFER_SIZE = 2000
MESSAGE = raw_input("tcpClientC: Enter guess (number) to continue or Enter exit:") +".3"

tcpClientC = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpClientC.connect((host, port))

while MESSAGE != 'exit':
    tcpClientC.send(MESSAGE)
    data = tcpClientC.recv(BUFFER_SIZE)
    print " Client3 received data:", data
    if (data == "Your guess is right"):
        print("Wait for the game to end and see the results from the server ")
        break
    MESSAGE = raw_input("tcpClientC: Enter guess (number) to continue or Enter exit:") + ".3"

tcpClientC.close()