import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, ifft
from pylab import *
import scipy.signal as signal
    
def sin_decay(delay):

    decay_j = np.zeros(256)
    decay_i = np.zeros(256)
    n = np.arange(0,256)
    exp = np.exp(-n/25)
    sin_i = np.sin(2*np.pi*3000*n/(48000))

    decay_i = exp*sin_i
    decay_j[delay:256] = decay_i[0:256-delay]

    return decay_i, decay_j

def gcc_phat(sig_i, sig_j):
    #Outputs an array of (N/2) + 1
    fft_i = np.fft.rfft(sig_i,2*len(sig_i))
    fft_j = np.fft.rfft(sig_j,2*len(sig_i))
    fft_conj_j = np.conjugate(fft_j)
    fft_i_j = fft_i * fft_conj_j
    fft_i_j_abs = np.abs(fft_i_j)
    ifft_i_j = np.fft.irfft(fft_i_j/fft_i_j_abs, 2*len(sig_i))
    
    return ifft_i_j

def square(delay):
    decay_j = np.zeros(256)
    decay_i = np.zeros(256)

    decay_i[20:40] = [1]
    decay_j[20+delay:40+delay] = [1]
    return decay_i, decay_j

def display(sig_i, sig_j, corr1, corr2):
    fig , ax = plt.subplots(ncols = 4)
    ax[0].plot(sig_i)
    ax[1].plot(sig_j)
    ax[2].plot(corr1)
    ax[3].plot(corr2)
    plt.show()

def cos(delay):
    decay_j = np.zeros(256)
    decay_i = np.zeros(256)
    n = np.arange(0,256.0)/48000.0
    sin_i = np.sin(2.0*np.pi*3000.0*n)
    decay_i = sin_i
    decay_j = np.sin(2.0*np.pi*3000.0*(n-(delay/48000)))

    return decay_i, decay_j

for i in range(20,30):
    sig_i, sig_j = sin_decay(i)
 #   sig_i, sig_j = cos(i)
 #   sig_i, sig_j = square(i)

 
    corr_ij = np.correlate(sig_i, sig_j, mode = 'full')
    corr_ji = np.correlate(sig_j, sig_i, mode = 'full')

    corr_ij = corr_ij/np.sqrt(np.correlate(sig_i, sig_i, mode = 'full')[128]*np.correlate(sig_j, sig_j, mode = 'full')[128])
    corr_ji = corr_ji/np.sqrt(np.correlate(sig_i, sig_i, mode = 'full')[128]*np.correlate(sig_j, sig_j, mode = 'full')[128])

    display(sig_i, sig_j, corr_ij, corr_ji)

    fft_corr_ij = gcc_phat(sig_i, sig_j)
    fft_corr_ji = gcc_phat(sig_j, sig_i)

    display(sig_i, sig_j, fft_corr_ij, fft_corr_ji)




eof = 0




