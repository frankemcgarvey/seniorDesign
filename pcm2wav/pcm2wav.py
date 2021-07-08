import sys
import wave
import os.path

with open(os.path.dirname(__file__) + '/../pcmFile.bin', 'rb') as pcmfile:
        pcmData = pcmfile.read()
with wave.open("wavFile.wav", 'wb') as wavfile:
        wavfile.setparams((4, 2, 48000, 0, 'NONE', 'NONE'))
        wavfile.writeframes(pcmData)






