import socket

host = socket.gethostname()
port = 2004
BUFFER_SIZE = 2000
MESSAGE = raw_input("tcpClientA: Enter guess (number) to continue or Enter exit:") +".1"

tcpClientA = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpClientA.connect((host, port))

while MESSAGE != 'exit':
    tcpClientA.send(MESSAGE)
    data = tcpClientA.recv(BUFFER_SIZE)
    print " Client1 received data:", data
    if (data == "Your guess is right"):
        print("Wait for the game to end and see the results from the server ")
        break
    MESSAGE = raw_input("tcpClientA: Enter guess (number) to continue or Enter exit:") + ".1"

tcpClientA.close()