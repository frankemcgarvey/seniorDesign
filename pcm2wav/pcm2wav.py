import sys
import wave


with open("pcmFile.pcm", 'rb') as pcmfile:
    pcmdata = pcmfile.read()

with wave.open("wavFile.wav", 'wb') as wavfile:
    wavfile.setparams((1, 2, 48000, 0, 'NONE', 'NONE'))
    wavfile.writeframes(pcmdata)