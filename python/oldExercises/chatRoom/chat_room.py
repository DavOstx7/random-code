import threading
import socket
import datetime


host = '127.0.0.1' #localhost
port = 55555

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host,port))
server_socket.listen()

socket_list = []
username_list = []
manager_list = []
muted_list = []

def get_name_length(data):
    #In order to only get the length, use [0]
    length = ""
    while True:
        if (data[0].isdigit()):
            length += data[0]
            data = data[1:]
        else:
            break
    return (int(length), data)

def get_name(data):
    (x, data) = get_name_length(data)
    name = ""
    for y in range(0, x):
        name += data[0]
        data = data[1:]
    return name

def get_command(data):
    # The command is a number between 1-5.
    (x, data) = get_name_length(data)
    for y in range(0, x):
        data = data[1:]
    return int(data[0])

def get_message_length(data):
    #In order to only get the length, use [0]
    # The command is a number between 1-5.
    (x, data) = get_name_length(data)
    for y in range(0, x + 1):
        data = data[1:]
    length = ""
    while True:
        if (data[0].isdigit()):
            length += data[0]
            data = data[1:]
        else:
            break
    return (int(length),data)

def get_message(data):
    # The command is a number between 1-5.
    (x, data) = get_message_length(data)
    return data

def get_name_V2(data):
    name = ''
    while True:
        if (data[0].isalpha()):
            name += data[0]
            data = data[1:]
        else:
            break
    return name

def get_message_V2(data):
    while True:
        if (data[0].isalpha()):
            data = data[1:]
        else:
            break
    while True:
        if(data[0].isdigit()):
            data = data[1:]
        else:
            break
    return data

def broadcast(message):
    for client in socket_list:
        client.send(message)

def send_message(full_message, manager):
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    if(hour >= 0 and hour <= 9):
        hour = "0" + str(hour)
    if (minute >= 0 and minute <= 9):
        minute = "0" + str(minute)
    message = str(hour) +":" + str(minute) + " "
    if(manager == True):
        message += '@'
    message += get_name(full_message) + ": "
    message += get_message((full_message))
    broadcast(message.encode('ascii'))

def kick_message(name):
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    if (hour >= 0 and hour <= 9):
        hour = "0" + str(hour)
    if (minute >= 0 and minute <= 9):
        minute = "0" + str(minute)
    message = str(hour) + ":" + str(minute) + " "
    message+= name + " "
    message+= 'has been kicked from the chat!'
    broadcast(message.encode('ascii'))

def manager_promotion_message(name):
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    if (hour >= 0 and hour <= 9):
        hour = "0" + str(hour)
    if (minute >= 0 and minute <= 9):
        minute = "0" + str(minute)
    message = str(hour) + ":" + str(minute) + " "
    message += name + " "
    message += 'has been promoted to a manager!'
    broadcast(message.encode('ascii'))

def muted_message(name):
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    if (hour >= 0 and hour <= 9):
        hour = "0" + str(hour)
    if (minute >= 0 and minute <= 9):
        minute = "0" + str(minute)
    message = str(hour) + ":" + str(minute) + " "
    message += name + " "
    message += 'is now muted!'
    broadcast(message.encode('ascii'))

def send_private_message(name, msg, sock, addition):
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    if (hour >= 0 and hour <= 9):
        hour = "0" + str(hour)
    if (minute >= 0 and minute <= 9):
        minute = "0" + str(minute)
    message = str(hour) + ":" + str(minute) + " "
    message += "!" + addition + name + ": " + msg
    sock.send(message.encode('ascii'))

def check_manager(client):
    isManager = False
    for sock in manager_list:
        if client is sock:
            isManager = True
    return isManager

def check_mute(client):
    isMuted = False
    for sock in muted_list:
        if client is sock:
            isMuted = True
    return isMuted

def view_managers(client):
    msg = "the managers are: "
    for sock in manager_list:
        index = socket_list.index(sock)
        name = username_list[index]
        msg += name + "  "
    client.send(msg.encode('ascii'))

def command_1(client, message): # 1 ---> sending a message
    try:
        if(client not in muted_list):
            isManager = check_manager(client)
            send_message(message, isManager)
        else:
            client.send('You cannot speak here!'.encode('ascii'))
    except:
        client.send('An unexpected error has occurred, please try again'.encode('ascii'))

def command_2(client, message): # 2 ---> promoting a manager
    try:
        name = get_message(message)

        if name in username_list: #checking if the name is online
            index = username_list.index(name)
            sock = socket_list[index]
            if sock not in manager_list:
                manager_list.append(sock)
                manager_promotion_message(name)
            else:
                client.send(f'{name} is already a manager'.encode('ascii'))
        else:
            client.send(f'{name} is not in the chat room!'.encode('ascii'))
    except:
        client.send('An unexpected error has occurred, please try again'.encode('ascii'))

def command_3(client, message): # 3 ---> kick a user
    try:
        name = get_message(message)

        if name in username_list: #checking if the name is online
            index = username_list.index(name)
            sock = socket_list[index]

            # checking if the sock is a manager him self, if he is, we cannot disconnect him
            if (check_manager(sock) == False):
                socket_list.remove(sock)
                username_list.remove(name)
                sock.close()
                kick_message(name)
            else:
                client.send(f'Cannot kick {name} because he is a manager'.encode('ascii'))
        else:
            client.send(f'{name} is not in the chat room!'.encode('ascii'))
    except:
        client.send('An unexpected error has occurred, please try again'.encode('ascii'))

def command_4(client, message): # 4 ---> mute a user
    try:
        name = get_message(message)

        if name in username_list: #checking if the name is online
            index = username_list.index(name)
            sock = socket_list[index]
            # checking if the sock is a manager him self, if he is, we cannot disconnect him
            if (check_manager(sock) == False):
                muted_list.append(sock)
                muted_message(name)
            else:
                client.send(f'Cannot mute {name} because he is a manager'.encode('ascii'))
        else:
            client.send(f'{name} is not in the chat room!'.encode('ascii'))
    except:
        client.send('An unexpected error has occurred, please try again'.encode('ascii'))

def command_5(client, message): # 5 ---> private message
    try:
        new_message = get_message(message)
        name = get_name_V2(new_message)
        msg = get_message_V2(new_message)

        if name in username_list: #checking if the name is online
            index = username_list.index(name)
            sock = socket_list[index]
            sent_from = get_name(message)
            isManager = check_manager(client)
            addition = ''
            if isManager == True: #checking if the client is manager
                addition = '@'
            send_private_message(sent_from, msg, sock, addition)
            client.send("The private message has been sent successfully".encode('ascii'))
        else:
            client.send(f'{name} is not in the chat room!'.encode('ascii'))
    except:
        client.send('An unexpected error has occurred, please try again'.encode('ascii'))

def handle(client):
    while True:
        try:
            #Get input from clients
            message = str((client.recv(1024).decode('ascii')))
            print("Message: " + message)
            try:
                if (message == 'quit'):
                    client.close()
                elif (message == 'view-managers'):
                    if (len(manager_list) == 0):
                        client.send('There are no managers! '.encode('ascii'))
                    else:
                        view_managers(client)
                else:
                    #Get the command (number between 1 to 5)
                    command = get_command(message)
                    print("command: " + str(command))

                    # 1 ---> sending a message
                    if command == 1:
                        command_1(client, message)

                    # 2 ---> promoting a manager
                    if command == 2:
                        if check_manager(client) == True: #checking if the client is a manager him self
                            command_2(client, message)
                        else:
                            client.send('You need to be a manager in order to promote a manager'.encode('ascii'))

                    # 3 ---> kicking a user
                    if command == 3:
                        if check_manager(client) == True: #checking if the client is a manager him self
                            command_3(client, message)
                        else:
                            client.send('You need to be a manager in order to kick a user'.encode('ascii'))

                    # 4 ---> muting a user
                    if command == 4:
                        if check_manager(client) == True: #checking if the client is a manager him self
                            command_4(client, message)
                        else:
                            client.send('You need to be a manager in order to mute a user'.encode('ascii'))

                    # 5 ---> private message
                    if command == 5:
                        command_5(client, message)
            except:
                client.send('Error, unable to execute command, try checking for typos'.encode('ascii'))

        except:
            #client disconnected probably

            if client in socket_list: #remove client from the socket list if he is still in there, and broadcast that he has left
                index = socket_list.index(client)
                socket_list.remove(client)
                username = username_list[index]


                now = datetime.datetime.now()
                hour = now.hour
                minute = now.minute
                if (hour >= 0 and hour <= 9):
                    hour = "0" + str(hour)
                if (minute >= 0 and minute <= 9):
                    minute = "0" + str(minute)
                #str(hour) + ":" + str(minute) + " "
                broadcast(f'{str(hour)}:{str(minute)} {username} left the chat!'.encode('ascii'))
                username_list.remove(username)

            #remove client from the manager list if he is one
            if client in manager_list:
                manager_list.remove(client)

            # remove client from the muted list if he is one
            if client in muted_list:
                muted_list.remove(client)

            break

def recieve():
    first = True
    #main function
    while True:
        client, address = server_socket.accept()
        print(f'Connected with {str(address)}')

        client.send('USER'.encode('ascii'))

        username = client.recv(1024).decode('ascii')
        username_list.append(username)
        socket_list.append(client)

        if first == True:
            manager_list.append(client)
            first = False

        print(f'Username of the client is {username}!')
        broadcast(f'{username} joined the chat!'.encode('ascii'))
        client.send('Connected to the server!'.encode('ascii'))
        client.send('You can now start chatting!'.encode('ascii'))

        thread = threading.Thread(target = handle, args = (client,))
        thread.start()

print('Server is listening!')
recieve()

