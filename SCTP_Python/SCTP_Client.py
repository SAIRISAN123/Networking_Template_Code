import socket
import sctp


client_socket = sctp.sctpsocket_tcp(socket.AF_INET)


server_address = ('127.0.0.1', 12345)

try:
    while True:
        # Connect t
        client_socket.connect(server_address)
        print("Connected to SCTP Server at {}:{}".format(*server_address))

        # Send a mess
        message = str(input("Enter a message: "))
        client_socket.send(message.encode('utf-8'))
        # print("Sent:", message)

        # Receive a response 
        data = client_socket.recv(1024)
        print("Received:", data.decode('utf-8'))

finally:
    
    client_socket.close()
    print("Connection closed.")





# # chat application



# import socket
# import sctp


# client_socket = sctp.sctpsocket_tcp(socket.AF_INET)


# server_address = ('127.0.0.1', 12345)

# try:

#     client_socket.connect(server_address)
#     print("Connected to SCTP Server at {}:{}".format(*server_address))

#     while True:
#         message = input("Enter a message (or 'exit' to quit): ")
#         if message.lower() == 'exit':
#             break

#         client_socket.send(message.encode('utf-8'))

#         data = client_socket.recv(1024)
#         print("Received from server:", data.decode('utf-8'))

# finally:
#     client_socket.close()
#     print("Connection closed.")