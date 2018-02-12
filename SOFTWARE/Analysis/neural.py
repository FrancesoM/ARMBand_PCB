# -*- coding: utf-8 -*-
"""
Created on Thu Feb  8 17:47:25 2018

@author: Francesco
"""

#First open the data files
try:
    import keras
    from keras.datasets import mnist
    from keras.models import Sequential
    from keras.layers import Dense, Dropout, Flatten
    from keras.layers import Conv2D, MaxPooling2D
    from keras import backend as K
    print("Keras found")

except ModuleNotFoundError:
    keras_is_installed = 0
    print("Keras is not found, the program will skip the learning...")

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d, Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from scipy import interpolate
import os
import sys
import random

def readata(name):
    f = open(name).read()
    lines = f.split('\n')
    N = len(lines) - 1
    M = len(lines[0].split(','))
    #fill the matrix
    d = np.zeros((N,M))
    type_mov = int(lines[0].split(',')[-1])
    for i,line in enumerate(lines):
        #print(i, " :" ,line)
        if(len(line) > 2):
            for j,val in enumerate(line.split(',')[:-1]):
                #print(val)
                d[i,j] = int(val)
            d[i,M-1] = np.average(d[i,:-1])
        #since we read just 31 values, we add the 32 to have a
        #rectangle
        #

    
    return [d,type_mov]

"""
    This function takes this structure:
        ---
        |   --
        |  | Data
        |  | Movement type
        |   --
        |  | Data
        |  | Movement type
        |   --
        |  ...
        ---
        
    And return this structure
    
        ---
        |   --
        |  | Data with movement 0
        |  | Data with movement 0
        |  | ...
        |   --
        |  | Data with movement 1
        |  | Data with movement 1
        |  | ...
        |
        ---
    
"""
def reorganize_files(data_unorganized):
    data_types = [] 
    
    #Search for all different kind of movements
    for data in data_unorganized:
        if((data[1] in data_types) == False):
            data_types.append(data[1])
    
    #Since the types are just numbers, we will use them as index, so sort
    data_types.sort()
    
    #intermediate representation 
    step1 = []
    for i in data_types:
        step1.append(list(filter(lambda t:t[1]==i,data_unorganized)))
        step1[i] = [t[0] for t in step1[i]]
    
    #np.concatenate takes a list, which is exactly what each 
    #iterable element of step1 is
    organized_data = list(map(np.concatenate,step1))
        
    return organized_data

def traintest(data,labels,percentage):
    N = data.shape[0]
    N_test = int(N*percentage)
    N_train = N - N_test
    
    data_test = np.zeros((N_test,data.shape[1]))
    data_train = np.zeros((N_train,data.shape[1]))
    
    print("data_test",data_test.shape)
    print("data_train",data_train.shape)
    
    
    label_test = np.zeros(N_test)
    label_train = np.zeros(N_train)
    
    indexes_for_test = random.sample(range(0,N),N_test)
    
    test_i = 0
    train_i = 0
    for i in range(N):
        if(i in indexes_for_test):
            data_test[test_i][:] = data[i][:]
            label_test[test_i] = labels[i]
            test_i = test_i + 1
        else:
            data_train[train_i][:] = data[i][:]
            label_train[train_i] = labels[i]
            train_i = train_i+1
    
    return(data_test,label_test,data_train,label_train)


if __name__=="__main__":

    labels = ['Close','Open','Up','Down']
    
    data = list(map(readata,(list(filter(lambda name: name.find('txt') > 0,os.listdir())))))
    
    organized = reorganize_files(data)
    
    full_labels_length = sum([n.shape[0] for n in organized])
    full_labels = np.zeros(full_labels_length)
    
    #element i in the "organized" list has the type i
    index = 0
    for typ,data_typ in enumerate(organized):
        full_labels[index:index+data_typ.shape[0]] = typ
        #print("Start: ",index,"Stop: ",index+data_typ.shape[0])
        index = index+data_typ.shape[0]
    
    #matrix full of recordings of different type, the type can
    #be retrieved because full_label[i] == type(full_data[i])
    full_data = np.concatenate(organized)
    
    print(full_data.shape)
    
    data_test,y_test,data_train,y_train = traintest(full_data,full_labels,0.2)
    
#    print(data_test.shape)
#    print(data_train.shape)
#    print(y_test.shape)
#    print(y_train.shape)
    
    x_train = np.zeros((data_train.shape[0],8,4))
    x_test = np.zeros((data_test.shape[0],8,4))
    
    for i,array in enumerate(data_test):
        x_test[i,:,:] = array.reshape(8,4)
        
    for i,array in enumerate(data_train):
        x_train[i,:,:] = array.reshape(8,4)
      
    
    x_train = x_train.reshape(x_train.shape[0],1,8,4)
    x_test = x_test.reshape(x_test.shape[0],1,8,4)
    
    
    batch_size = 64
    num_classes = len(np.unique(y_test))
    epochs = 12
    
    # input image dimensions
    img_rows, img_cols = 8,4
    input_shape = (1,img_rows, img_cols)

    
    x_train = x_train.astype('float32')
    x_test = x_test.astype('float32')
    x_train /= 2**12
    x_test /=  2**12
    print('x_train shape:', x_train.shape)
    print(x_train.shape[0], 'train samples')
    print(x_test.shape[0], 'test samples')

    #if I want to print the data

    try:
        if sys.argv[1] == "p":
            plot3 = 1
        else:
            plot3 = 0
    except IndexError:
        plot3 = 0

    if plot3:

        X, Y = np.mgrid[0:7:8j,0:3:4j]
        xnew, ynew = np.mgrid[0:7:100j,0:3:100j]

        fig3dintpol = []
        axsurfintpol = []

        for l in range(len(labels)):

            Z = np.average(x_train[y_train==l,0,:,:],axis=0)
            tck = interpolate.bisplrep(X, Y, Z, kx = 2, ky = 2)
            znew = interpolate.bisplev(xnew[:,0], ynew[0,:], tck)
        
            #prepare axes and plot the 3d interpolated data
            #fig3d = plt.figure()
            #axsurf = fig3d.gca(projection='3d')
            #axsurf.plot_surface(X, Y, Z, cmap='summer', rstride=1, cstride=1, alpha=None)

            #plot only the interpolated one
            fig3dintpol.append(plt.figure(figsize=(12,12)))
            axsurfintpol.append(fig3dintpol[l].gca(projection='3d'))
            axsurfintpol[l].plot_surface(xnew, ynew, znew, cmap='summer', rstride=1, cstride=1, alpha=None, antialiased=True)

        plt.show()

    if keras_is_installed != 0:
    
        # convert class vectors to binary class matrices
        y_train = keras.utils.to_categorical(y_train, num_classes)
        y_test = keras.utils.to_categorical(y_test, num_classes)
        
        """ Here starts the machine learning """
        
        model = Sequential()
        model.add(Conv2D(32, kernel_size=(2, 2),
                         activation='relu',
                         input_shape=input_shape,data_format='channels_first'))
     
        model.add(Conv2D(64, (2, 2), activation='relu'))
        
        #model.add(MaxPooling2D(pool_size=(2, 2)))
        model.add(Dropout(0.25))
        model.add(Flatten())
        model.add(Dense(128, activation='relu'))
        model.add(Dropout(0.5))
        model.add(Dense(num_classes, activation='softmax'))
        
        model.compile(loss=keras.losses.categorical_crossentropy,
                      optimizer=keras.optimizers.Adadelta(),
                      metrics=['accuracy'])
        
        model.fit(x_train, y_train,
                  batch_size=batch_size,
                  epochs=epochs,
                  verbose=1,
                  validation_data=(x_test, y_test))
        score = model.evaluate(x_test, y_test, verbose=0)
        
        outputtt = model.save("out.h5")
        print('Test loss:', score[0])
        print('Test accuracy:', score[1])
    
            
            