import socket

address = "7C:7A:91:75:D8:2E"
port = 3
s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s.connect((address, port))
text = input()
s.send(bytes(text, 'UTF-8'))
