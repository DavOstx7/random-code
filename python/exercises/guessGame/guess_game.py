import socket
from threading import Thread
from SocketServer import ThreadingMixIn
import random

# Multithreaded Python server : TCP Server Socket Thread Pool
class ClientThread(Thread):

    def __init__(self,ip,port,conn,x,count_list,finish_list):
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.conn=conn
        self.x = x
        self.count_list = count_list
        self.finish_list = finish_list

        print "[+] New server socket thread started for " + ip + ":" + str(port)

    def run(self):
            while(True):
                data = self.conn.recv(2048)
                if(data == ""):
                    break

                index = int(data.split(".")[1])
                data = data.split(".")[0]
                
                if data == 'exit':
                    break

                print ""
                print("The guess from client" + str(index) + " is: " + data)
                data = int(data)
                
                if(data > self.x):
                    self.conn.send("Your guess is higher")
                    self.count_list[index]+=1

                if(data < self.x):
                    self.conn.send("Your guess is lower")
                    self.count_list[index] += 1

                if (data == self.x):
                    self.conn.send("Your guess is right")
                    self.count_list[index] += 1
                    self.finish_list[index] = True

                if (self.finish_list[1] == True and self.finish_list[2] == True and self.finish_list[3] == True):
                    print ""
                    print("Guest1 took: " + str(self.count_list[1]) + " times to guess the number")
                    print("Guest2 took: " + str(self.count_list[2]) + " times to guess the number")
                    print("Guest3 took: " + str(self.count_list[3]) + " times to guess the number")
                    winner = "Guest1 "
                    value = self.count_list[1]
                    for i in range(2,4):
                        if(self.count_list[i] == value):
                            winner+= "and Guest" + str(i) + " "
                        if(self.count_list[i] < value):
                            winner = "Guest" + str(i) + " "
                            value = self.count_list[i]
                    winner+= "won"
                    print (str(winner))

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

    x = random.randint(0,100)
    print ("random number: " + str(x))
    count_list = [10000000,0,0,0]
    finish_list = [False, False, False, False]
    while True:
        tcpServer.listen(3)
        print "Multithreaded Python server : Waiting for connections from TCP clients..."
        (conn, (ip,port)) = tcpServer.accept()
        newthread = ClientThread(ip,port,conn, x,count_list,finish_list)
        newthread.start()
        threads.append(newthread)


if __name__ == "__main__":
    main()