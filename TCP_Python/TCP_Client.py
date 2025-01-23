from socket import *
serverName = 'localhost'     # serverName = 'localhost' or private IP address of the server
serverPort = 12000


clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

message = input('Input lowercase sentence:')
                        
clientSocket.send(message.encode())

modifiedSentence = clientSocket.recv(1024)

print('Reply From Server: ', modifiedSentence.decode())


clientSocket.close()


# # run continlusly chat application

# while True:
#     clientSocket = socket(AF_INET, SOCK_STREAM)
#     clientSocket.connect((serverName, serverPort))

#     message = input('Input lowercase sentence:')
                        
#     clientSocket.send(message.encode())

#     modifiedSentence = clientSocket.recv(1024)

#     print('Reply From Server: ', modifiedSentence.decode())


#     clientSocket.close()