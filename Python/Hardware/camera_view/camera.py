import time
import cv2
import signal

stop = False


def sig_int(sig, s):
    global stop
    stop = True


signal.signal(signal.SIGINT, sig_int)
camera = cv2.VideoCapture(0)
cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
while not stop:
    start = time.time()
    image, _ = camera.read()
    cv2.imshow("Image", image)
    cv2.waitKey(1)
    end = time.time()
    print(1 / (end - start))
camera.release()
