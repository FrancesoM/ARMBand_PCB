# -*- coding: utf-8 -*-
"""
Created on Thu Feb  8 17:47:25 2018

@author: Francesco
"""

#First open the data files
import keras 
import numpy as np
import matplotlib.pyplot as plt

def readata(name):
    f = open(name).read()
    lines = f.split('\n')
    N = len(lines) - 1
    M = len(lines[0].split(','))-1
    #fill the matrix
    d = np.zeros((N,M))
    type_mov = lines[0].split(',')[-1]
    for i,line in enumerate(lines):
        #print(i, " :" ,line)
        if(len(line) > 2):
            for j,val in enumerate(line.split(',')[:-1]):
                #print(val)
                d[i,j] = int(val)
            
    return [d,type_mov]

if __name__=="__main__":
    
    data = list(map(readata,(list(filter(lambda name: name.find('txt') > 0,os.listdir())))))
    print(data)