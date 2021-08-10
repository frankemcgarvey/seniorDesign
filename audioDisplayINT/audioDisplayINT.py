
import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path
import struct 

def getAngle(samples, distance):
    if samples <= 33:
       if samples > 28:
          samples = 28.0
       samples = samples
       return np.arcsin((28.0-samples)/48000.0 * 340.0/distance)*180.0/np.pi
    elif samples >= 224:
       if samples < 229:
          samples = 229.0
       samples = (256.0-samples)
       return np.arcsin((-28.0 + samples)/48000.0 * 340.0/distance)*180.0/np.pi
    else:
       samples = 0.0
       return 0.0

def display(sig_i, sig_j, gcc_i_j, dir):
    fig , ax = plt.subplots(ncols = 4)
    ax[0].plot(sig_i)
    ax[1].plot(sig_j)
    ax[2].plot(gcc_i_j)
    ax[3].plot(dir,'ro')
    plt.show()

def gcc_phat2(sig, refsig, fs=1, max_tau=None, interp=16):
    '''
    This function computes the offset between the signal sig and the reference signal refsig
    using the Generalized Cross Correlation - Phase Transform (GCC-PHAT)method.
    '''
    
    # make sure the length for the FFT is larger or equal than len(sig) + len(refsig)
    n = sig.shape[0] + refsig.shape[0]

    # Generalized Cross Correlation Phase Transform
    SIG = np.fft.rfft(sig, n=n)
    REFSIG = np.fft.rfft(refsig, n=n)
    R = SIG * np.conj(REFSIG)

    cc = np.fft.irfft(R / np.abs(R), n=(interp * n))

    max_shift = int(interp * n / 2)
    if max_tau:
        max_shift = np.minimum(int(interp * fs * max_tau), max_shift)

    cc = np.concatenate((cc[-max_shift:], cc[:max_shift+1]))

    # find max cross correlation index
    shift = np.argmax(np.abs(cc)) - max_shift

    tau = shift / float(interp * fs)
    
    return tau, cc

def gcc_phat(sig_i, sig_j, length):
    #Outputs an array of (N/2) + 1
    fft_i = np.fft.rfft(sig_i,length)
    fft_j = np.fft.rfft(sig_j,length)
    fft_conj_j = np.conjugate(fft_j)
    fft_i_j = fft_i * fft_conj_j
    fft_i_j_abs = np.abs(fft_i_j)
    ifft_i_j = np.fft.irfft(fft_i_j/fft_i_j_abs, length)
    max = np.argmax(ifft_i_j)
    return max, ifft_i_j

def correalation(sig_i, sig_j):
    corr = np.abs(np.correlate(sig_i, sig_j, mode = 'full'))
    max = np.argmax(corr)
    length = len(sig_i) - 1
    return max - length, corr

counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

numOfChannel = 2
fileName = 'pcmFile.bin'
state = True
size = 2048
with open(os.path.dirname(__file__) + '/../pcmFiles/' + fileName, 'rb') as pcmfile:
    hw = pcmfile.read(4)
    while hw:
        counter = counter + 1
        if(counter%size == 0):
            state = not(state)

        if(state):
            data1.append(int.from_bytes(hw, 'little'))
        else:
            data2.append(int.from_bytes(hw, 'little'))
        hw = pcmfile.read(4)

fig , ax = plt.subplots(ncols = 2)  



pcmData1 = np.array(data1)
pcmData2 = np.array(data2)

ax[0].plot(pcmData1)
ax[1].plot(pcmData2)

plt.show()
