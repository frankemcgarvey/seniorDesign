import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path
import struct 

counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

numOfChannel = 2
fileName = 'pcmFile.bin'
state = True
with open(os.path.dirname(__file__) + '/../pcmFiles/' + fileName, 'rb') as pcmfile:
    hw = pcmfile.read(4)
    while hw:
        counter = counter + 1
        if(counter%1024 == 0):
            state = not(state)

        if(state):
            if(sys.getsizeof(hw) >= 37):
                data1.append(struct.unpack('f',hw))
        else:
            if(sys.getsizeof(hw) >= 37):
                data2.append(struct.unpack('f',hw))
        hw = pcmfile.read(4)

pcmData1 = np.array(data1)
pcmData2 = np.array(data2)
pcmData3 = np.array(data3)
pcmData4 = np.array(data4)


fig , ax = plt.subplots(ncols = numOfChannel)

if numOfChannel > 0:
    ax[0].plot(pcmData1)

if numOfChannel > 1:
    ax[1].plot(pcmData2)

if numOfChannel > 2:
    ax[2].plot(pcmData3)

if numOfChannel > 3:
    ax[3].plot(pcmData4)

plt.show()
