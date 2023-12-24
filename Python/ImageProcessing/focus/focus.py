import numpy as np
import cv2

def test_focus():
    cam = cv2.VideoCapture()
    cam.open(2)
    key = ''
    while key != ord('q'):
        _, image = cam.read()
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        gauss = cv2.GaussianBlur(image, (5, 5), 1)
        laplacian = cv2.Laplacian(gauss, -1)
        show = np.log(laplacian+1) / np.max(np.log(laplacian))
        cv2.imshow("Image", (255*show).astype(np.uint8))
        key = cv2.waitKey(1)
    cam.close()


