import numpy as np
import cv2


def main():
    cam = cv2.VideoCapture(2)
    _, image = cam.read()
    last_image = np.zeros_like(image)
    pid = np.zeros_like(last_image)
    last_pid = np.zeros_like(last_image)
    while cv2.waitKey(1) != ord('q'):
        _, image = cam.read()
        pid = 0.9*pid + 0.1 * image + 0.01*last_image + 0.09 * last_pid
        cv2.imshow("Viewer", pid.astype(np.uint8))
        last_image = image
        last_pid = pid

if __name__ == "__main__":
    main()
