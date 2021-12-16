import numpy as np
#import pandas as pd
import csv 


# data = pd.read_csv("data.csv")
# data.head()

# VAl = 31
# inp1 = np.array([])
# inp2 = np.array([])
# for i in range(13):
#     if(data['first'][i] == VAl):
#         inp1 = np.append(inp1, data['first'][i])
#         for j in range(i, 0, -1):
#             if(data['first'][j] == 1):
#                 inp2 = np.append(inp2, data['second'][j])
#                 break

# print(inp1)
# print(inp2)

arr = np.array([["Adr","Time"]])
with open('data2.csv') as File:
    reader = csv.reader(File, delimiter=';', quotechar=',',
                        quoting=csv.QUOTE_MINIMAL)
    for row in reader:
        if (row[0] == '1'):
            temp = row[1]
        if (row[0] == '31'):
            arr = np.append(arr, [[row[0], int(temp,16)]], axis=0)
            

myFile = open('input.csv', 'w')

with myFile:
    writer = csv.writer(myFile, delimiter = ";", lineterminator = "\r")
    writer.writerows(arr)

# print(arr)

val = "0xDDDD"
val = int(val, 16)
print(val)
