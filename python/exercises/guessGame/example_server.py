import socket
from threading import Thread
from SocketServer import ThreadingMixIn

# Multithreaded Python server : TCP Server Socket Thread Pool
class ClientThread(Thread):

    def __init__(self,ip,port,conn):
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.conn=conn
        print "[+] New server socket thread started for " + ip + ":" + str(port)

    def run(self):
        while True :
            data = self.conn.recv(2048)
            print "Server received data:", data           
            self.conn.send(MESSAGE)  # echo
def main():

    # Multithreaded Python server : TCP Server Socket Program Stub
    TCP_IP = '0.0.0.0'
    TCP_PORT = 2004
    BUFFER_SIZE = 20  # Usually 1024, but we need quick response

    tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    ## explain the op code socket
    ##
    tcpServer.bind((TCP_IP, TCP_PORT))
    threads = []

    while True:
        tcpServer.listen(4)
        print "Multithreaded Python server : Waiting for connections from TCP clients..."
        (conn, (ip,port)) = tcpServer.accept()
        newthread = ClientThread(ip,port,conn)
        newthread.start()
        threads.append(newthread)

    for t in threads:
        t.join()

if __name__ == "__main__":
    main()