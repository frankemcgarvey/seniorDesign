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

numOfChannel = 4
fileName = 'pcmFile.bin'
state = True
index = 0

with open(os.path.dirname(__file__) + '/../pcmFiles/' + fileName, 'rb') as pcmfile:
    hw = pcmfile.read(2)
    while hw:
        counter = counter + 1
        if(counter%1024 == 0):
            index = index + 1

        if(index%numOfChannel == 0):
                data1.append(int.from_bytes(hw, 'little', signed = 'True'))
        elif(index%numOfChannel == 1): 
                data2.append(int.from_bytes(hw, 'little', signed = 'True'))
        elif(index%numOfChannel == 2):
                data3.append(int.from_bytes(hw, 'little', signed = 'True'))
        elif(index%numOfChannel == 3):
                data4.append(int.from_bytes(hw, 'little', signed = 'True'))
        hw = pcmfile.read(2)

pcmData1 = np.int16(np.array(data1))
pcmData2 = np.int16(np.array(data2))
pcmData3 = np.int16(np.array(data3))
pcmData4 = np.int16(np.array(data4))

fig , ax = plt.subplots(ncols = 4)

ax[0].plot(pcmData1)
ax[1].plot(pcmData2)
ax[2].plot(pcmData3)
ax[3].plot(pcmData4)


plt.show()


