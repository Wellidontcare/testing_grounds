import bluetooth

if __name__ == "__main__":
    address = "7C:7A:91:75:D8:2E"
    port = 3
    s = bluetooth.BluetoothSocket()
    s.bind((address, port))
    client, address = s.accept()
    data = client.recv(1024)
    print(data)
