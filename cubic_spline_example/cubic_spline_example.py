
import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, ifft
from pylab import *
from scipy.interpolate import CubicSpline


def cubic_spline(d):
    sig_i = np.zeros(1024)
    sig_j = np.zeros(1024)

    sq_i = np.zeros(1024)
    sq_j = np.zeros(1024)

    f = 1000.0
    fs = 16000.0
    t = 0.064
    delay = d/fs

    samples = np.arange(t*fs)/fs

    #Signal I
    sig_i = np.sin(2*np.pi*f*(samples-delay))
    sig_i[300:1024] = 0
   
    #Signal J
    sig_j = np.sin(2*np.pi*f*samples)
    sig_j[300:1024] = 0

    #Normalize
    a = (sig_i - np.mean(sig_i)) / (np.std(sig_i) * len(sig_i))
    b = (sig_j - np.mean(sig_j)) / (np.std(sig_j))
    normalize_corr = np.correlate(a, b, mode = 'full')

    corr = normalize_corr[1024-12:1024+12]
    x    = np.arange(1024-12, 1024+12)
    cs   = CubicSpline(x, corr, bc_type = 'natural')

    x_new = np.arange(1024-12, 1024+12, 1/12)
    s = cs(x_new)

    maxS = (np.argmax(s))
    
    return maxS

#r = .5
#delay = np.array(np.arange(-7,7+r,r))
#arrayS = np.array(np.arange(-7,7+r,r))
#for i in range(len(arrayS)):
#    arrayS[i] = cubic_spline(delay[i]) 
#    bp = 0

#A = np.vstack([delay, np.ones(len(delay))]).T
#m, c = np.linalg.lstsq(A, arrayS)[0]

#arrayS = arrayS - 110.46896551724134

    
s = (cubic_spline(0) - 12*11)/12
s = (cubic_spline(1) - 12*11)/12
s = (cubic_spline(2) - 12*11)/12
s = (cubic_spline(3) - 12*11)/12
s = cubic_spline(4) 
s = cubic_spline(5) 
s = cubic_spline(6) 
s = cubic_spline(7) 
s = cubic_spline(10) 
eof = 0