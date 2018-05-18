import numpy as np
from random import randint
from pprint import pprint

def main ():
    #Create memory
    #Each block of memory is 10
    memory = np.array([None] * 0xF)
    memory = [None] * 0xF
    print("\nMemory size: {0}\n".format(len(memory) + 1))

    #Wait queue
    wait = []

    pCounter = 1
    mCounter = 0
    #Allocate processes
    while pCounter < len(memory):
        pSize = randint(1,20)
        sizeMemory = int(pSize/11) + 1
        #Cant fit process
        if ((len(memory) - mCounter -1) < sizeMemory): break

        #Fit the process
        for i in range(mCounter, mCounter + sizeMemory):
            memory[i] = "P{}, size: {}".format(pCounter, pSize)

        mCounter += sizeMemory

        pCounter += 1

    pprint(memory)
    freeMemory = len(memory) - mCounter - 1
    print('Free memory left: {} blocks of 10 units each one\n'.format(freeMemory))
    print('There are {0} processes'.format(pCounter))
    #Delete processes
    deleteProcess = input('\nn Process you want to delete... ')
    for i in range(len(memory)):
        if memory[i] == None: continue
        if int(deleteProcess) == (int(memory[i].split(',')[0][1:])):
            memory[i] = 'None'

            freeMemory +=1

    print(memory)


    #Insert process
    newProcess = input('Size of process: {}'.format(pCounter))
    newSize = int(newProcess)
    newBlock = newSize/11 +1
    if (newBlock > freeMemory): print("Not enough memory")
    for i in range(len(memory)):
        if(memory[i] == None):
            memory[i] = "P{}, size: {}".format(pCounter, newSize)
    print(memory)

if __name__ == '__main__':
    main()
