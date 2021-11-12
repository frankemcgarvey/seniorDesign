import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, ifft
import struct 
from pydub import AudioSegment
import os, os.path

# simple version for working with CWD
DIR = os.path.dirname(__file__) + '/../../rifle/'
length = len([name for name in os.listdir(DIR) if os.path.isfile(os.path.join(DIR, name))])

for counter in range(1, length+1):
    DIR = os.path.dirname(__file__) + '/../../rifle/audio (' + str(counter) + ').wav'
    sound = AudioSegment.from_wav(DIR)
    sound = sound.set_channels(1)
    sound.export(DIR, format="wav")

for counter in range(1, length+1):
    DIR = os.path.dirname(__file__) + '/../../rifle/audio (' + str(counter) + ').wav'
    stream = wave.open(DIR,"rb")

    num_channels = stream.getnchannels()
    sample_rate = stream.getframerate()
    sample_width = stream.getsampwidth()
    num_frames = stream.getnframes()

    raw_data = stream.readframes( num_frames )
    stream.close()

    total_samples = num_frames * num_channels

    if sample_width == 1:
        fmt = "%iB" % total_samples
    elif sample_width == 2:
        fmt = "%ih" % total_samples
    else:
        raise ValueError("Only supports 8 and 16 bit audio formats.")

    integer_data = struct.unpack(fmt, raw_data)
    del raw_data

    channels = []

    for index, value in enumerate(integer_data):
        bucket = index % num_channels
        channels.append(value)
    
    y = np.array(channels)

    abs_val = np.abs(y)

    index = np.argmax(abs_val)

    spliceVal = 5000

    while(index < spliceVal):
        spliceVal = spliceVal - 100
    
    y = np.int16(y[index-spliceVal:(index-spliceVal) + sample_rate])


    with wave.open(DIR, 'wb') as wavfile:
        wavfile.setparams((num_channels, sample_width, sample_rate, 0, 'NONE', 'NONE'))
        wavfile.writeframes(y)
    bp = 0
   
   







