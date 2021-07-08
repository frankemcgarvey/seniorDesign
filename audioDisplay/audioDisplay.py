import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path

counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

with open(os.path.dirname(__file__) + '/../pcmFile.bin', 'rb') as pcmfile:
    hw = pcmfile.read(2)
    while hw:
        if counter%4 == 0:
                 data1.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%4 == 1:
                 data2.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%4 == 2:
                 data3.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%4 == 3:
                 data4.append(int.from_bytes(hw, "little", signed = "True"))
        counter = counter + 1
        hw = pcmfile.read(2)

pcmData1 = np.array(data1)
pcmData2 = np.array(data2)
pcmData3 = np.array(data3)
pcmData4 = np.array(data4)
N = len(pcmData1)/48000
t = np.arange(0.0,N,(1/48000))

fig , ax = plt.subplots(nrows = 2, ncols = 2, sharey=True)

ax[0][0].plot(t,pcmData1)
ax[0][1].plot(t,pcmData2)
ax[1][0].plot(t,pcmData3)
ax[1][1].plot(t,pcmData4)

plt.show()
