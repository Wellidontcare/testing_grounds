import socket
import time
address = "84:a6:c8:10:ca:79"
port = 3
s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s.connect((address, port))
counter = 0
while True:
    text = str(time.time())
    start = time.perf_counter()
    s.send(bytes(text, 'UTF-8'))
    end = time.perf_counter()
    print(f"Sending Data with {1 / (end - start)} FPS!")
    counter += 1
    print(time.time())
