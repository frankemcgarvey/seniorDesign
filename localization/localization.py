
import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path

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
    ax[2].plot(gcc_i_j.real)
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
    return ifft_i_j


counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

with open(os.path.dirname(__file__) + '/../pcmFile.bin', 'rb') as pcmfile:
    hw = pcmfile.read(2)
    while hw:
        if counter%2 == 0:
                 data1.append(int.from_bytes(hw, "little", signed = "True"))
        elif counter%2 == 1:
                 data2.append(int.from_bytes(hw, "little", signed = "True"))
        hw = pcmfile.read(2)
        counter = counter + 1

pcmData1 = np.array(data1)
pcmData2 = np.array(data2)

check = np.array_equal(pcmData1, pcmData2)

counter = 0
k      = 1024
fftLen = k*2

fig , ax = plt.subplots(ncols = 2) 

ax[0].plot(pcmData1)
ax[1].plot(pcmData2)
plt.show()

angle = 0
 

while counter < (len(pcmData1)/k + 1):
     
    sig_i = pcmData1[counter*k : (counter*k)+k]

    sig_j = pcmData2[counter*k : (counter*k)+k]
    
   # max, gcc_i_j = gcc_phat2(sig_i, sig_j, 48000)
    
    gcc_i_j = gcc_phat(sig_j, sig_i, fftLen)
    max = np.argmax(np.abs(gcc_i_j))
    max1 = np.max(sig_i)
    max2 = np.max(sig_j)

    if(max1 > 4000 or max2 > 4000):
        display(sig_i, sig_j, np.abs(gcc_i_j), max)

    counter = counter + 1

    

   

 
eof = 0
