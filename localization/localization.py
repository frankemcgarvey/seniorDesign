
import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, ifft
from pylab import *
from scipy.interpolate import CubicSpline
import os.path

def gcc_phat2(sig, refsig, fs=1, max_tau=None, interp=1):
    '''
    This function computes the offset between the signal sig and the reference signal refsig
    using the Generalized Cross Correlation - Phase Transform (GCC-PHAT)method.
    '''
    
    # make sure the length for the FFT is larger or equal than len(sig) + len(refsig)
    n = sig.shape[0] + refsig.shape[0] + 1

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

def gcc_phat(sig_i, sig_j):

    n = sig_i.shape[0] + sig_j.shape[0]

    sig_i_fft = np.fft.rfft(sig_i, n=n)
    sig_j_fft = np.fft.rfft(sig_j, n=n)

    sig_j_conj = np.conjugate(sig_j_fft)
    
    sig = sig_i_fft * sig_j_conj

    sig = sig/(np.abs(sig))

    cc = np.fft.irfft(sig, n)

    cc = np.concatenate((cc[-int(n/2):], cc[:int(n/2)+1]))
    return cc

   

def normalize(sig_i, sig_j): 
    #Normalize 
 
    normalize_corr = np.correlate(sig_i, sig_j, mode = 'full')/np.sqrt(np.sum(np.power(sig_i,2)) * np.sum(np.power(sig_j,2)))
   
    plt.figure()
    plt.plot(normalize_corr)
    plt.show()
    return normalize_corr


def cubic_spline(sig, maxArg, rate):
  

    x    = np.arange((maxArg) - 1, (maxArg) + 2)
    y    = np.array(sig)
    cs   = CubicSpline(x, y, bc_type = 'not-a-knot')

    x_new = np.arange((maxArg) - 1, (maxArg) + 2, rate)
    s = cs(x_new)

    return s

def parabola(sig, argMax, rate):

    argMaxPara = argMax
    argMaxSig  = np.argmax(sig)

    up_x = np.zeros(3)
    up_x[1] = (argMaxPara)
    up_x[0] = up_x[1] - 1/rate
    up_x[2] = up_x[1] + 1/rate

    x0   = up_x[0] 
    x0sq = np.power(up_x[0],2)

    x1   = up_x[1]
    x1sq = np.power(up_x[1],2)

    x2   = up_x[2]
    x2sq = np.power(up_x[2],2)

    A = np.array([[x0sq, x0, 1],
                  [x1sq, x1, 1],
                  [x2sq, x2, 1]])
    
    y = np.array([sig[argMaxSig -1], sig[argMaxSig], sig[argMaxSig + 1]])

    x = np.linalg.solve(A, y)

    a = x[0]
    b = x[1]
    c = x[2]

    vert = -b/(2*a)
    return vert

def localize(pcmData1, pcmData2):

    counter = 0
    k      = 1024
    m      = 1024
    n      = 2*k/m
     
    maxFlag = False
    doneFlag = False
    startFlag = True

    while counter < (len(pcmData1)/k):
  
            sig_i = pcmData1[counter*k : (counter*k)+k]
            sig_j = pcmData2[counter*k : (counter*k)+k]

            max_i = np.max(np.abs(sig_i))
            max_j = np.max(np.abs(sig_j))
        
            if(max_i > .01 or max_j > .01):
                cc = gcc_phat(sig_i, sig_j)
                plt.figure()
                plt.plot(cc)
                plt.show()
                max = np.argmax(cc[1000:1040])
                norm = normalize(sig_i, sig_j)
                l = np.argmax(norm)
                s = cubic_spline(norm[1023-12:1023+12],l, 1/8)
                d = np.argmax(s)/8
                x = np.round(parabola(s) - 1023, 2)
                bp = 0
            counter = counter + 1

def signals():

    sig_i = np.zeros(1024)
    sig_j = np.zeros(1024)

    D = 10
    fs = 24000
    f = 1000

    delay = D/fs
    t = 1
    n = np.arange(1024)/fs

    sig_i = np.sin(2*np.pi*f*(n-delay))*np.exp(-(n-delay)*250)
    sig_j = np.sin(2*np.pi*f*(n))*np.exp(-(n)*250)

 #   sig_i[:50] = 0
 #   sig_j[:50] = 0
 #   sig_i[1000:] = 0
 #   sig_j[1000:] = 0
 #   sig_i[100:150] = 1
 #   sig_j[120:170] = 1

    plt.figure()
    plt.plot(sig_i)
    plt.plot(sig_j)
    plt.show()

    norm = normalize(sig_i, sig_j)

    tau, corr = gcc_phat2(sig_j, sig_i)

    argMaxNorm = np.argmax(norm)

    maxNorm = np.max(norm)

    s = cubic_spline(norm[argMaxNorm-1:argMaxNorm+2], argMaxNorm, 1/96)

    argMaxS = (np.argmax(s)/96 + (argMaxNorm-1))

    max = (argMaxS/48)
  
    x  = round((parabola(s, argMaxS, 96) - 1023),3)
    x2 = round((parabola(norm, argMaxNorm, 1) - 1023),3)
    plt.figure(0)
    plt.plot(s)
 #   plt.plot(max, 'ro')
    plt.show()

    bp = 0










signals()
counter = 0
data1 = []
data2 = []
data3 = []
data4 = []

numOfChannel = 4
fileName = 'pcmFile.bin'

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

pcmData1 = np.asfarray(np.array(data1))/32768.0
pcmData2 = np.asfarray(np.array(data2))/32768.0
pcmData3 = np.asfarray(np.array(data3))/32768.0
pcmData4 = np.asfarray(np.array(data4))/32768.0

length = len(pcmData2)
pcmData1 = pcmData1[:length]

pcmData1 = pcmData1[20*1024:]
pcmData2 = pcmData2[20*1024:]
pcmData3 = pcmData3[20*1024:]
pcmData4 = pcmData4[20*1024:]

fig , ax = plt.subplots(ncols = 4)
ax[0].plot(pcmData1)
ax[1].plot(pcmData2)
ax[2].plot(pcmData3)
ax[3].plot(pcmData4)
plt.show() 

localize(pcmData2,pcmData1)

eof = 0
