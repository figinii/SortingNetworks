import os
import matplotlib.pyplot as plt
import numpy as np

FILE_DIR = "./comparatorPrints/"

def getComparatorList():
    file = os.listdir(FILE_DIR)

    if(len(file) < 1):
        print("Error: no file found in directory")
        exit()

    file = FILE_DIR + file[0]

    numOfInput = 0
    comparatorList = []
    with open(file, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 2: 
                a, b = int(parts[0]), int(parts[1])
                numOfInput = max(numOfInput, a, b)
                comparatorList.append((a, b))

    return numOfInput + 1, comparatorList

def plot_sorting_network(num_inputs, comparatorList):
    fig, ax = plt.subplots()
    ax.set_xlim(0, len(comparatorList) + 1)
    ax.set_ylim(-1, num_inputs + 1)
    ax.set_aspect('equal')
    
    for i in range(0, num_inputs):
        ax.plot([0, len(comparatorList) + 1], [i, i], color='black', linewidth=1)
    
    for idx, (a, b) in enumerate(comparatorList):
        x = idx + 1
        ax.plot([x, x], [a, b], color='black', linewidth=1)
        ax.scatter([x], [a], color='black', s=20)
        ax.scatter([x], [b], color='black', s=20)
    
    ax.axis('off')
    plt.show()

#main
num_inputs, comparatorList = getComparatorList()
plot_sorting_network(num_inputs, comparatorList)