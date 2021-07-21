import sys
import wave
import os.path

numOfChannel = input("Enter Number of Channels")

with open(os.path.dirname(__file__) + '/../pcmFile.bin', 'rb') as pcmfile:
        pcmData = pcmfile.read()
with wave.open("wavFile.wav", 'wb') as wavfile:
        wavfile.setparams((numOfChannel, 2, 48000, 0, 'NONE', 'NONE'))
        wavfile.writeframes(pcmData)






