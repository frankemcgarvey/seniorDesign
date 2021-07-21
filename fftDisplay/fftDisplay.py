
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

numOfChannel = int(input("Input number of channels: "))

with open(os.path.dirname(__file__) + '/../pcmFile.bin', 'rb') as pcmfile:
    hw = pcmfile.read(2)
    while hw:
        if counter%numOfChannel == 0:
                 data1.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%numOfChannel == 1:
                 data2.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%numOfChannel == 2:
                 data3.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%numOfChannel == 3:
                 data4.append(int.from_bytes(hw, "little", signed = "True"))
        counter = counter + 1
        hw = pcmfile.read(2)

pcmData1 = np.array(data1[256:])
pcmData2 = np.array(data2[256:])
pcmData3 = np.array(data3[256:])
pcmData4 = np.array(data4[256:])

plt.ion()
fig , ax = plt.subplots(nrows = 3, ncols = 2, sharey = True)
counter = 0

k = 256

while counter < (len(pcmData1)/k + 1):

     W = np.fft.rfft(pcmData1[counter*k:counter*k+k], n = k)

     N = len(W)
     n = np.arange(N)
     T = N/48000
     freq = n/T

     if(numOfChannel > 0):
        ax[0][0].plot(freq, np.abs(W))
        ax[0][0].set_xlim([0,6000])
     
     if(numOfChannel > 1):
         X = np.fft.rfft(pcmData2[counter*k:counter*k+k], n = k)
         ax[0][1].plot(freq, np.abs(X))
         ax[0][1].set_xlim([0,6000])

     if(numOfChannel > 2):
         Y = np.fft.rfft(pcmData3[counter*256:counter*256+256], n = k)
         ax[1][0].plot(freq, np.abs(Y))
         ax[1][0].set_xlim([0,6000])

     if(numOfChannel > 3):
         Z = np.fft.rfft(pcmData4[counter*256:counter*256+256], n = k) 
         ax[1][1].plot(freq, np.abs(Z))
         ax[1][1].set_xlim([0,6000])
     plt.pause(0.2)
     counter = counter + 1
     ax[2][0].plot(counter,1)

   

 
plt.show(block=True)