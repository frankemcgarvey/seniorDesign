
import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, ifft
from pylab import *
from scipy.interpolate import CubicSpline
import os.path


def cubic_spline(sig_i, sig_j):

    #Normalize
    a = (sig_i - np.mean(sig_i)) / (np.std(sig_i) * len(sig_i))
    b = (sig_j - np.mean(sig_j)) / (np.std(sig_j))
    normalize_corr = np.correlate(a, b, mode = 'full')

    corr = normalize_corr[1024-10:1024+10]
    x    = np.arange(1024-10, 1024+10)
    cs   = CubicSpline(x, corr, bc_type = 'natural')

    x_new = np.arange(1024-10, 1024+10, 1/8)
    s = cs(x_new)

    maxS = np.argmax(s) - 80
    
    return maxS

def parabola(sig_i, sig_j):

    #Normalize
    a = (sig_i - np.mean(sig_i)) / (np.std(sig_i) * len(sig_i))
    b = (sig_j - np.mean(sig_j)) / (np.std(sig_j))
    normalize_corr = np.correlate(a, b, mode = 'full')

    plt.figure()
    plt.plot(normalize_corr)
    plt.show()
    argMax = np.argmax(normalize_corr)

    up_x = np.zeros(3)
    up_x[1] = argMax*12
    up_x[0] = up_x[1] - 12
    up_x[2] = up_x[1] + 12

    x0   = up_x[0]
    x0sq = np.power(up_x[0],2)

    x1   = up_x[1]
    x1sq = np.power(up_x[1],2)

    x2   = up_x[2]
    x2sq = np.power(up_x[2],2)

    A = np.array([[x0sq, x0, 1],
                  [x1sq, x1, 1],
                  [x2sq, x2, 1]])
    
    y = np.array([normalize_corr[argMax -1], normalize_corr[argMax], normalize_corr[argMax + 1]])

    x = np.linalg.solve(A, y)

    a = x[0]
    b = x[1]
    c = x[2]

    x = (-b/(2*a) - 1023*12)

    return np.float(x)

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
                x = parabola(sig_i, sig_j)
                s = cubic_spline(sig_i, sig_j)
                bp = 0
            counter = counter + 1


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
