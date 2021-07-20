import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, ifft
from pylab import *
import scipy.signal as signal

def gcc_phat(sig_i, sig_j, length):
    #Outputs an array of (N/2) + 1
    fft_i = np.fft.rfft(sig_i,length)
    fft_j = np.fft.rfft(sig_j,length)
    fft_conj_j = np.conjugate(fft_j)
    fft_i_j = fft_i * fft_conj_j
    fft_i_j_abs = np.abs(fft_i_j)
    ifft_i_j = ifft(fft_i_j/fft_i_j_abs)
    return ifft_i_j

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
       return np.arcsin((-28. + samples)/48000.0 * 340.0/distance)*180.0/np.pi
    else:
       samples = 0.0
       return 0.0
 
def hold():
    W
    
    
def sin_decay_gcc(delay):
   
    taps = 201
    b   = (1.558844e-16,1.287554e-07,2.672892e-07,2.956034e-07,-1.070492e-15,-6.889754e-07,-1.451110e-06,-1.527365e-06,2.833924e-15,3.648067e-06,8.959139e-06,1.429764e-05,1.732312e-05,1.613824e-05,1.068485e-05,3.631611e-06,0.000000e+00,5.232227e-06,2.220896e-05,4.852767e-05,7.568576e-05,9.132167e-05,8.435367e-05,5.119163e-05,-4.967003e-14,-4.992508e-05,-7.488740e-05,-5.795299e-05,1.146356e-13,7.516582e-05,1.260142e-04,1.090538e-04,-1.261225e-13,-1.889679e-04,-4.056177e-04,-5.730547e-04,-6.211395e-04,-5.221961e-04,-3.143045e-04,-9.772699e-05,0.000000e+00,-1.196922e-04,-4.715322e-04,-9.598879e-04,-1.399517e-03,-1.583519e-03,-1.375557e-03,-7.871250e-04,4.939226e-13,6.874168e-04,9.789565e-04,7.207065e-04,-9.058706e-13,-8.507394e-04,-1.364210e-03,-1.131100e-03,8.122270e-13,1.807461e-03,3.733974e-03,5.084383e-03,5.318831e-03,4.321434e-03,2.516996e-03,7.583068e-04,0.000000e+00,8.752851e-04,3.353848e-03,6.648878e-03,9.452628e-03,1.044241e-02,8.867994e-03,4.967501e-03,-1.645315e-12,-4.174585e-03,-5.844569e-03,-4.236553e-03,2.625791e-12,4.872335e-03,7.732779e-03,6.358078e-03,-2.062425e-12,-1.005773e-02,-2.075016e-02,-2.829683e-02,-2.973987e-02,-2.436258e-02,-1.436528e-02,-4.401918e-03,-3.194354e-18,-5.348018e-03,-2.125427e-02,-4.411505e-02,-6.643623e-02,-7.891504e-02,-7.349651e-02,-4.639610e-02,2.574388e-12,5.712778e-02,1.122822e-01,1.521396e-01,1.666662e-01,1.521396e-01,1.122822e-01,5.712778e-02,2.574388e-12,-4.639610e-02,-7.349651e-02,-7.891504e-02,-6.643623e-02,-4.411505e-02,-2.125427e-02,-5.348018e-03,-3.194354e-18,-4.401918e-03,-1.436528e-02,-2.436258e-02,-2.973987e-02,-2.829683e-02,-2.075016e-02,-1.005773e-02,-2.062425e-12,6.358078e-03,7.732779e-03,4.872335e-03,2.625791e-12,-4.236553e-03,-5.844569e-03,-4.174585e-03,-1.645315e-12,4.967501e-03,8.867994e-03,1.044241e-02,9.452628e-03,6.648878e-03,3.353848e-03,8.752851e-04,0.000000e+00,7.583068e-04,2.516996e-03,4.321434e-03,5.318831e-03,5.084383e-03,3.733974e-03,1.807461e-03,8.122270e-13,-1.131100e-03,-1.364210e-03,-8.507394e-04,-9.058706e-13,7.207065e-04,9.789565e-04,6.874168e-04,4.939226e-13,-7.871250e-04,-1.375557e-03,-1.583519e-03,-1.399517e-03,-9.598879e-04,-4.715322e-04,-1.196922e-04,0.000000e+00,-9.772699e-05,-3.143045e-04,-5.221961e-04,-6.211395e-04,-5.730547e-04,-4.056177e-04,-1.889679e-04,-1.261225e-13,1.090538e-04,1.260142e-04,7.516582e-05,1.146356e-13,-5.795299e-05,-7.488740e-05,-4.992508e-05,-4.967003e-14,5.119163e-05,8.435367e-05,9.132167e-05,7.568576e-05,4.852767e-05,2.220896e-05,5.232227e-06,0.000000e+00,3.631611e-06,1.068485e-05,1.613824e-05,1.732312e-05,1.429764e-05,8.959139e-06,3.648067e-06,2.833924e-15,-1.527365e-06,-1.451110e-06,-6.889754e-07,-1.070492e-15,2.956034e-07,2.672892e-07,1.287554e-07,1.558844e-16)
    D   = delay
    D   = 2*D
    k   = 256
    
    
    n = np.arange(0,256)

    noise1 = np.random.normal(0,0.05,256)
    noise2 = np.random.normal(0,0.05,256)

    decay_j = np.zeros(256)
    decay_i = np.zeros(256)
    exp = np.exp(-n/25)
    sin_i = np.sin(2*np.pi*5000*n/48000)

    l = 2
    m = l/2
  

    decay_i = exp*sin_i
    decay_j[D:256] = decay_i[0:256-D]

    decay_noise_i = decay_i + noise1
    decay_noise_j = decay_j + noise2

    #decay_filter_i = np.convolve(b, decay_noise_i, mode = 'full')
    #decay_filter_j = np.convolve(b, decay_noise_j, mode = 'full')
    a = 1
    decay_filter_i =  signal.lfilter(b, a, decay_i)
    decay_filter_j =  signal.lfilter(b, a, decay_j)

    decay_gcc_j_i           = gcc_phat(decay_j, decay_i, l*k)
    decay_noise_gcc_j_i     = gcc_phat(decay_noise_j, decay_noise_i, l*k)
    decay_filter_gcc_j_i    = gcc_phat(decay_filter_j, decay_filter_i, l*k)
    
    decay_max   = np.argmax(decay_gcc_j_i)
    noise_max   = np.argmax(decay_noise_gcc_j_i)
    filter_max  = np.argmax(decay_filter_gcc_j_i)

    decayAngle   = getAngle(decay_max, 0.2)
    noiseAngle   = getAngle(noise_max, 0.2)
    filterAngle  = getAngle(filter_max, 0.2)

    fig , ax = plt.subplots(nrows = 3, ncols = 3) 

    ax[0][0].plot(n,decay_j)
    ax[0][0].plot(n,decay_i)

    ax[0][1].plot(np.arange(0,256),decay_noise_j)
    ax[0][1].plot(np.arange(0,256),decay_noise_i)

    ax[0][2].plot(np.arange(0, len(decay_filter_j)),decay_filter_j)
    ax[0][2].plot(np.arange(0, len(decay_filter_i)),decay_filter_i)

    ax[1][0].plot(np.arange(0, m*k+1), (decay_gcc_j_i.real))
    ax[1][1].plot(np.arange(0, m*k+1), (decay_noise_gcc_j_i.real))
    ax[1][2].plot(np.arange(0, m*k+1), (decay_filter_gcc_j_i.real))

    ax[2][0].plot(0, decayAngle/100, 'ro')
    ax[2][1].plot(0, noiseAngle/100, 'ro')
    ax[2][2].plot(0, filterAngle/100, 'ro')

    ax[2][0].set_ylim(-1,1)
    ax[2][1].set_ylim(-1,1)
    ax[2][2].set_ylim(-1,1)

    ax[2][0].yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(16))
    ax[2][1].yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(16))
    ax[2][2].yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(16))

    return decayAngle, noiseAngle, filterAngle
 


decayAngle  = np.array([0.0]*29)
noiseAngle  = np.array([0.0]*29)
filterAngle = np.array([0.0]*29)
for i in range(0,29,1):
    decayAngle[i], noiseAngle[i], filterAngle[i] = sin_decay_gcc(i)

plt.show()

fig , ax = plt.subplots(ncols = 3)  
trueAngle = np.arcsin((28-np.arange(0,29))/48000*340/.2)*180/np.pi

decayError  = np.array([0.0]*29)
noiseError  = np.array([0.0]*29)
filterError = np.array([0.0]*29)

decayError[28]   = np.sqrt(np.power(trueAngle[28]-decayAngle[28],2))
decayError[0:28]  = np.sqrt(np.power(trueAngle[0:28]-decayAngle[0:28],2))/trueAngle[0:28]

noiseError[28]   = np.sqrt(np.power(trueAngle[28]-noiseAngle[28],2))
noiseError[0:28]  = np.sqrt(np.power(trueAngle[0:28]-noiseAngle[0:28],2))/trueAngle[0:28]

filterError[28]   = np.sqrt(np.power(trueAngle[28]-filterAngle[28],2))
filterError[0:28]  = np.sqrt(np.power(trueAngle[0:28]-filterAngle[0:28],2))/trueAngle[0:28]


ax[0].plot(np.arange(0,29), decayError, 'ro')

ax[1].plot(np.arange(0,29), noiseError, 'kx')

ax[2].plot(np.arange(0,29), filterError, 'ys')


plt.show()


eof = 0



