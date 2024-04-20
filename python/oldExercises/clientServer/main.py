import socket
import threading
import time
import os
import sqlite3
import logging

logging.basicConfig(filename=".log_users_messages.txt",
                    filemode='a',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%H:%M:%S',
                    level=logging.DEBUG)

db_path = ".server.db"

db_exists = False
if(os.path.exists(db_path)):
    db_exists = True

sqldb = sqlite3.connect(db_path, check_same_thread=False)

if(db_exists and os.stat(db_path)):
    cursor = sqldb.execute("""SELECT ID FROM USERS ORDER BY ID DESC LIMIT 1;""")
    ID_LIST = cursor.fetchall() #returns rows
    if(ID_LIST):
        GLOBAL_ID = ID_LIST[0][0] + 1 #first [0] is to get the row, second [0] is to fetch the ID
    else:
        GLOBAL_ID = 1
else:
    sqldb.execute("""CREATE TABLE USERS
    (ID INT PRIMARY KEY     NOT NULL,
    IP              TEXT    NOT NULL,
    PORT            INT     NOT NULL,
    NAME            TEXT);""")
    GLOBAL_ID = 1


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

IP = '0.0.0.0'
PORT = 8080

socket = socket.socket()
socket.bind((IP, PORT))

socket.listen(5)

print(socket)
print(bcolors.HEADER + f"[+] Listening on ({IP},{PORT})" + bcolors.ENDC)

lock = threading.Lock()
connection_list = []



print(bcolors.HEADER + f"[+] Opened a data base at {db_path} contain ID,IP,PORT,NAME" + bcolors.ENDC)


def fetch_info(id):
    lock.acquire()
    cursor = sqldb.execute(f"""SELECT IP, PORT, NAME FROM USERS WHERE ID = {id};""")
    row = cursor.fetchall()[0] #returns the rows, we only need the row
    ip, port, name = row[0], row[1], row[2]
    lock.release()
    return ip, port, name

def broadcast_message(sender_conn, message):
    for conn in connection_list:
        if(conn is not sender_conn):
            conn.send(message.encode())

def broadcast_leaving_message(message):
    for conn in connection_list:
        conn.send(message.encode())

def listen_client(conn, ID):

    ip, port, name = fetch_info(ID)
    print(bcolors.OKCYAN + f"[+] Listening for messages from ({ip}, {port})" + bcolors.ENDC)
    while True:
        try:
            data = conn.recv(1024).decode()
        except:
            leaving_message = f"[-] {name} ({ip}, {port}) left the server!"
            logging.INFO(leaving_message)
            leaving_message = bcolors.WARNING + leaving_message + bcolors.ENDC
            print(leaving_message)
            connection_list.remove(conn)
            broadcast_leaving_message(leaving_message)
            break
        else:
            if (data):
                message = (bcolors.UNDERLINE + f"[*] {name} ({ip}, {port}) sent:" +
                      bcolors.ENDC + bcolors.OKBLUE + bcolors.BOLD + f" {data}" + bcolors.ENDC)
                print(message)
                logging.info(f"[*] {name} ({ip}, {port}) sent {data}")
                broadcast_message(conn, message)

            time.sleep(0.5)

def create_client(conn, addr):
    global GLOBAL_ID
    conn.send((bcolors.UNDERLINE + "[+] Please enter your name:" + bcolors.ENDC + " ").encode())
    name = conn.recv(1024).decode()
    lock.acquire() # need it for accessing db and global_id
    cursor = sqldb.execute(f"""SELECT ID FROM USERS WHERE NAME = '{name}';""")
    rows = cursor.fetchall()
    if(rows):
        conn.send("Welcome back!".encode())
        id = rows[0][0]
    else:
        sqldb.execute(f"""INSERT INTO USERS (ID, IP, PORT, NAME) VALUES ({GLOBAL_ID}, '{addr[0]}', {addr[1]}, '{name}');""")
        sqldb.commit()
        id = GLOBAL_ID
        GLOBAL_ID += 1
        conn.send("First login! Welcome".encode())

    t = threading.Thread(target=listen_client, args=(conn, id))
    t.start()
    connection_list.append(conn)
    lock.release()

    time.sleep(0.2)

def recieve_clients():
    while True:
        conn, addr = socket.accept()
        print(conn)
        t = threading.Thread(target=create_client, args=(conn, addr))
        t.start()

recieve_clients()


sqldb.close()
socket.close()


