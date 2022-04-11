import socket

if __name__ == "__main__":
    address = "7C:7A:91:75:D8:2E"
    port = 3
    s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
    s.bind((address, port))
    s.listen(1)
    client, address = s.accept()
    data = client.recv(1024)
    print(data)
