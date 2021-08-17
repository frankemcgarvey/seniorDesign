import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path
import struct 
from scipy.signal import savgol_filter

counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

numOfChannel = 2
fileName = 'pcmFile.bin'
index = 0

with open(os.path.dirname(__file__) + '/../pcmFiles/' + fileName, 'rb') as pcmfile:
    hw = pcmfile.read(4)
    while hw:
        counter = counter + 1
        if(counter%1024 == 0):
            index = index + 1

        if(index%3 == 0):
            if(sys.getsizeof(hw) >= 37):
                a, = struct.unpack('f',hw)
                data1.append(a)
        elif(index%3 == 1):
            if(sys.getsizeof(hw) >= 37):
                b, = struct.unpack('f',hw)
                data2.append(b)
        elif(index%3 == 2):
            if(sys.getsizeof(hw) >= 37):
                c, = struct.unpack('f',hw)
                data3.append(c)

        hw = pcmfile.read(4)

pcmData1 = np.array(data1)
pcmData2 = np.array(data2)
pcmData3 = np.array(data3)

fig , ax = plt.subplots(ncols = 3)

ax[0].plot(pcmData1)
ax[1].plot(pcmData2)
ax[2].plot(pcmData3)

plt.show()

