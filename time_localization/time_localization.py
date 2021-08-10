import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path

def time_diff(sig_i, sig_j):

    pos_i = np.argmax(sig_i)

    pos_j = np.argmax(sig_j)

    samples = pos_i - pos_j

    display(sig_i, sig_j, samples, (pos_i, pos_j))

def time_corr(sig_i, sig_j):

    corr = np.correlate(sig_i, sig_j, 'same')

    samples = np.argmax(corr)

    display(sig_i, sig_j, corr, samples)

def freq_difference(sig_i, sig_j):
    
    sig_i_fft = np.fft.rfft(sig_i)
    sig_j_fft = np.fft.rfft(sig_j)

    max_i = np.argmax(sig_i_fft)
    max_j = np.argmax(sig_j_fft)

    samples = np.abs(sig_i_fft[max_j])/np.abs(sig_j_fft[max_j])/(360.0*48000.0)

    display(sig_i, sig_j, samples, sig_i_fft, sig_j_fft)


def display(sig_i, sig_j, sample, fft_i, fft_j):
    fig , ax = plt.subplots(ncols = 5)
    ax[0].plot(sig_i)
    ax[1].plot(sig_j)
    ax[2].plot(sample, 'ro')
    ax[3].plot(fft_i)
    ax[4].plot(fft_j)
    plt.show()

counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

#numOfChannel = int(input("Enter Number of Channels: "))
#fileName = input("Enter filename with ext: ")

with open(os.path.dirname(__file__) + '/../pcmFiles/' + 'pcmfile.bin', 'rb') as pcmfile:
    hw = pcmfile.read(2)
    while hw:
        if counter%2 == 0:
                data1.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%2 == 1:
                data2.append(int.from_bytes(hw, "little", signed = "True"))
        counter = counter + 1
        hw = pcmfile.read(2)

pcmData1 = np.array(data1)
pcmData2 = np.array(data2)

counter = 0
k = 128 

while counter < (len(pcmData1)/k): 
       
    sig_i = pcmData1[counter*k : (counter*k)+k]

    sig_j = pcmData2[counter*k : (counter*k)+k]

    if(np.max(sig_i) > 500 or np.max(sig_j) > 500):
       freq_difference(sig_i, sig_j)
    

    counter = counter + 1


