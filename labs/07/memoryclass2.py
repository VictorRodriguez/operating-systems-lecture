# -*- coding: utf-8 -*-
"""
Created on Mon Apr  9 08:49:28 2018

@author: oscar
"""

import random

def insert(process):
    count = 0
    pos = 0
    first_time = True
    
    for position in range (0, len(MA)+1):
        if(count >= process):
            for x in range(pos, (pos + process)):
                MA[x] = process
            break
        if MA[position] == 0:
            if first_time:
                pos = position
                first_time = False
            count += 1
        elif MA[position] != 0:
            count = 0
            first_time = True
        
def delete(process):
    for position in range(0,len(MA)+1):
        if(MA[position] == process):
            for x in range(position, position + process):
                MA[x] = 0
            break

MA = list()

for x in range(0,9):
    MA.append(0)
    
insert(5)
insert(3)
insert(1)
print(MA)
delete(5)
print(MA)
delete(3)
print(MA)
insert(4)
print(MA)
