import socket
import sctp


server_socket = sctp.sctpsocket_tcp(socket.AF_INET)

# Bind 
server_address = ('0.0.0.0', 12345)
server_socket.bind(server_address)

# Listen 
server_socket.listen(5)
print("SCTP Server is listening on {}:{}".format(*server_address))

while True:
    # print("Waiting for a connection...")
    connection, client_address = server_socket.accept()
    print("Connected to:", client_address)

    try:
        while True:
            # Receive data 
            data = connection.recv(1024)
            if not data:
                print("No more data from", client_address)
                break

            print("Received:", data.decode('utf-8'))
            # upper case the data
            data = data.decode('utf-8').upper()
            # Send 
            response = data
            connection.send(response.encode('utf-8'))
    finally:
        connection.close()
        print("Connection closed with", client_address)