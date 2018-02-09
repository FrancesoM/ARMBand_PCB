# -*- coding: utf-8 -*-
"""
Created on Wed Jan  3 18:05:15 2018

@author: Francesco
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d, Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from scipy import interpolate

path_ = "C://Users/Francesco/Desktop/GUI-Serial/build-terminal-Desktop_Qt_5_9_1_MinGW_32bit-Debug/"
name = "deafult"
extension = ".txt"

def npopen(path_):
    f = open(path_, 'r').read()
    
    channels = len( f.split('\n')[0].split(','))
    ndata = len(f.split('\n'))-1
    
    data = np.zeros((ndata,channels),dtype=int)
    
    i = 0
    j = 0
    
    for line in f.split('\n'):
        for value in line.split(','):
            if(len(line.split(',')) == channels):
                #print(value,i,j)
                data[i][j] = int(value)
                j = j+1
        j = 0
        i = i+1
        
    return {'ndata' : ndata,
            'channels' : channels,
            'data' : data}

if __name__ == '__main__':
    
    name = "Close1"
    D = npopen(name + extension )
    
    for k in D.keys():
        print(k,':',D[k])
        
    fhist, axarr = plt.subplots(8,4)
    
    print("SHAPE OF YOU:", D['data'].shape)
    
    for i in range(0,D['channels']):
        #print ("Channel:  ",i)
        #print("Min:  ",np.min(D['data'][:,i]))
        #print("Max:  ",np.max(D['data'][:,i]))
        axarr[i%8,i//8].hist(D['data'][:,i],bins=100)
    
    #Create the mesh and use the data for the Z
    X, Y = np.mgrid[0:3:4j, 0:7:8j]
    Z = D['data'][250,:].reshape((4,8))
    
    xnew, ynew = np.mgrid[0:3:100j, 0:7:100j]
    tck = interpolate.bisplrep(X, Y, Z, kx = 2, ky = 2)
    znew = interpolate.bisplev(xnew[:,0], ynew[0,:], tck)
    
    #prepare axes and plot the 3d interpolated data
    fig3d = plt.figure()
    axsurf = fig3d.gca(projection='3d')
    axsurf.plot_surface(X, Y, Z, cmap='summer', rstride=1, cstride=1, alpha=None)
    
    #plot only the interpolated one
    fig3dintpol = plt.figure(figsize=(12,12))
    axsurfintpol = fig3dintpol.gca(projection='3d')
    axsurfintpol.plot_surface(xnew, ynew, znew, cmap='summer', rstride=1, cstride=1, alpha=None, antialiased=True)
    
    
    
    
    
    
    
    plt.tight_layout(pad=0.05, w_pad=0.05, h_pad=0.05)
    plt.show()
        
        
        
        
        
        
        