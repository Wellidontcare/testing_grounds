import numpy as np
import scipy as sci
import cv2
import matplotlib.pyplot as plt
###
plt.close('all')
image = np.array(cv2.imread('', cv2.IMREAD_GRAYSCALE)).astype('float64')
fft = np.abs(np.fft.fftshift(np.fft.fft2(image)))
plt.figure(1)
plt.title('Standard fft')
plt.imshow(np.log(fft), cmap='gray')
plt.figure(2)
plt.title('Welch fft')
ksizex, ksizey  = np.array(image).shape
ffts = []
overlap = 0.5
ksize = 400
for y in range(0, ksizex, int(ksizex/50)):
    for x in range(0, ksizex, int(ksizex/50)):
        ffts.append(np.abs(np.fft.fftshift(np.fft.fft2(image[x:x+ksize, y:y+ksize]))))
validffts = [x for x in ffts if x.shape == (ksize,ksize)]
welched = np.sum(validffts, axis=0, keepdims=True).reshape(ksize, ksize)/len(validffts)
plt.imshow(np.log(welched), cmap='gray')
plt.show()


