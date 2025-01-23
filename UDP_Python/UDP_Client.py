from socket import *
serverName = 'localhost'    # serverName = 'localhost' or private IP address of the server
serverPort = 12000



clientSocket = socket(AF_INET, SOCK_DGRAM)

message = input('Input lowercase sentence:')

clientSocket.sendto(message.encode(),(serverName, serverPort))

modifiedMessage, serverAddress = clientSocket.recvfrom(2048)

print("Message from server :"+modifiedMessage.decode())
clientSocket.close()




# # run continlusly chat application
# while True:
#     clientSocket = socket(AF_INET, SOCK_DGRAM)

#     message = input('Input lowercase sentence:')
                        
#     clientSocket.sendto(message.encode(),(serverName, serverPort))

#     modifiedMessage, serverAddress = clientSocket.recvfrom(2048)

#     print("Message from server :"+modifiedMessage.decode())
#     clientSocket.close()



