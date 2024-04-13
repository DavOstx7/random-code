import socket

host = socket.gethostname()
port = 2004
BUFFER_SIZE = 2000
MESSAGE = raw_input("tcpClientB: Enter guess (number) to continue or Enter exit:") +".2"

tcpClientB = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpClientB.connect((host, port))

while MESSAGE != 'exit':
    tcpClientB.send(MESSAGE)
    data = tcpClientB.recv(BUFFER_SIZE)
    print " Client2 received data:", data
    if (data == "Your guess is right"):
        print("Wait for the game to end and see the results from the server ")
        break
    MESSAGE = raw_input("tcpClientB: Enter guess (number) to continue or Enter exit:") +".2"

tcpClientB.close()