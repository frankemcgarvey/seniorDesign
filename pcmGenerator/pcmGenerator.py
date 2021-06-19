import numpy as np
from matplotlib import pyplot as plt

fs = 48000
f = 5000
t = 10

samples = np.arange(t*fs)/fs

sin = np.int16(np.sin(2*np.pi*f*samples)*32767)

f = open('pcmFile.pcm', 'w+b')
f.write(sin)
f.close()