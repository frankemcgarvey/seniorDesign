
import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import os.path
import struct 
from scipy.signal import savgol_filter

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

def display(sig_i, sig_j, corr, delay):
    fig , ax = plt.subplots(ncols = 4)
    ax[0].plot(sig_i)
    ax[1].plot(sig_j)
    ax[2].plot(corr)
    ax[3].plot(delay,'ro')
    plt.show()

def display1(sig_i, sig_j):
    fig , ax = plt.subplots(ncols = 2)
    ax[0].plot(sig_i, 'ro')
    ax[1].plot(sig_j, 'bo')
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

def shank(sig_i, sig_j):
    
    counter = 0
    n      = 1024*80
    m      = 1024
     
    maxFlag = False
    sig_j_buff = np.zeros(n)
    sig_i_buff = np.zeros(n)
    tf0 = 0
    tf1 = 0
    h = 6  
        
    while counter < (len(sig_i)/n):
        sig_i_buff = pcmData1[counter*n : (counter*n)+n]
        sig_j_buff = pcmData2[counter*n : (counter*n)+n]
            
        for i in range(0, int(n-m)):
            shankAvg0 = 1/m*np.sum(np.abs(sig_i_buff[i:i+m-1]))
            shankAvg1 = 1/m*np.sum(np.abs(sig_j_buff[i:i+m-1]))
            if(np.abs(sig_i_buff[m+i] > shankAvg0*h)):
                tf0 = m + i
                display1(sig_i_buff[i:i+m-1], tf0)
                display1(1,tf0 - tf1)
            if(np.abs(sig_j_buff[m+i] > shankAvg1*h)):
                tf1 = m + i
                display1(sig_j_buff[i:i+m-1], tf1)
                display1(1,tf0 - tf1)
            

        counter = counter + 1


def gcc(sig_i, sig_j):

    counter = 0
    k      = 1024*10
    m      = 512
    n      = k/m
     
    maxFlag = False
    sig_j_buff = np.zeros(k)
    sig_i_buff = np.zeros(k)
    doneFlag = False
    delayMax = 0
    corrMax = 0
    index = 0
    sigMax = 0
    while counter < (len(sig_i)/k):
     
        sig_i_buff = pcmData1[counter*k : (counter*k)+k]
        sig_j_buff = pcmData2[counter*k : (counter*k)+k]

        max_i = np.max(np.abs(sig_i_buff))
        max_j = np.max(np.abs(sig_j_buff))
        
        if(max_i > .04 or max_j > .04):
            maxFlag = True
        elif(maxFlag):
            doneFlag = True
         
        if(maxFlag):
            for i in range(0, int(n)):
                tempSig = gcc_phat(sig_i_buff[i*m:i*m+m], sig_j_buff[i*m:i*m+m], len(sig_i_buff[i*m:i*m+m])*2)
                tempMax = np.max(tempSig)
                tempDelay = np.argmax(tempSig)

                if(tempMax > corrMax):
                    sigMax      = tempSig
                    corrMax     = tempMax
                    delayMax    = tempDelay

            

        if(doneFlag):
            display1(sigMax, delayMax)
            corrMax = 0
            delayMax = 0
            tempCorrMax = 0
            maxFlag = False
            doneFlag = False

        counter = counter + 1


def correlation(sig_i, sig_j):

 #   corr = np.abs(np.correlate(sig_i, sig_j, mode = 'full'))
    corr = np.correlate(sig_i, sig_j, mode = 'full')
    length = len(sig_i)
    max = np.argmax(corr)
 
    return (max - length), corr

def correlate(pcmData1, pcmData2):
    counter = 0
    k      = 1024*2
    m      = 512
    n      = k/m
    
     
    maxFlag = False
    sig_j_buff = np.zeros(k)
    sig_i_buff = np.zeros(k)
    temp_i, temp_j = np.zeros(k), np.zeros(k)
    doneFlag = False
    delayMax = 0
    corrMax = 0
    index = 0

    while counter < (len(pcmData1)/k):
     
        index = counter%2

        sig_i_buff = pcmData1[counter*k : (counter*k)+k]
        sig_j_buff = pcmData2[counter*k : (counter*k)+k]

        max_i = np.max(np.abs(sig_i_buff))
        max_j = np.max(np.abs(sig_j_buff))
        
        if(max_i > .04 or max_j > .04):
            maxFlag = True
        elif(maxFlag):
            doneFlag = True
        
        if(maxFlag):
            for i in range(0, int(n)):
               delayTemp1, corrTemp1 = correlation(sig_i_buff[i*m:i*m+m], sig_j_buff[i*m:i*m+m])

               tempCorrMax1 = np.max(corrTemp1)

               if(tempCorrMax1 > corrMax):
                    corrMax = tempCorrMax1
                    delayMax = delayTemp1

        if(doneFlag):
            display1(delayMax, corrMax)
            corrMax = 0
            delayMax = 0
            tempCorrMax = 0
            maxFlag = False
            doneFlag = False
        
        
        counter = counter + 1

   
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
                a, = struct.unpack('f',hw)
                data1.append(a)
        else:
            if(sys.getsizeof(hw) >= 37):
                b, = struct.unpack('f',hw)
                data2.append(b)

        hw = pcmfile.read(4)
k = 1024
pcmData1 = np.array(data1[2048:])
pcmData2 = np.array(data2[2048:])
for i in range(0, int(len(pcmData1)/k)):
    pcmData1[i*k:i*k+k] =  savgol_filter(pcmData1[i*k:i*k+k], window_length = 31, polyorder = 3)
    pcmData2[i*k:i*k+k] =  savgol_filter(pcmData2[i*k:i*k+k], window_length = 31, polyorder = 3)

fig , ax = plt.subplots(ncols = 2)
ax[0].plot(pcmData1)
ax[1].plot(pcmData2)
plt.show()


correlate(pcmData1, pcmData2)

gcc(pcmData1, pcmData2)

#shank(pcmData1, pcmData2)

eof = 0
