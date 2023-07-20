
import pickle as pk
import socket

import numpy as np



def dks(arr:np.ndarray):
    sum = 0
    for i in range(1,32,1):
        sum += arr[i]
        # print(f" i = {i} buf = {arr[i]}")
    return np.uint16(0x5555 - sum)



sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # создаем сокет
sock.connect(('localhost', 9000)) 
buf = np.zeros(32, dtype=np.uint16)
print(np.size(buf))

buf[0] = np.uint16(2751)

buf[1] = np.uint16(1111)
buf[2] = np.uint16(2)
buf[3] = np.uint16(3)
buf[4] = np.uint16(4)


buf[31] = dks(buf)



sock.sendall(buf)

data = sock.recv(66)
print(data)
# print("Квитанция - ", hex(data))
sock.close()

# # print (data)