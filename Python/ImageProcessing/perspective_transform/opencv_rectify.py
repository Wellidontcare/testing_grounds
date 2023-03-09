import cv2
import numpy as np
from numpy.typing import NDArray
import matplotlib.pyplot as plt

def rectify(image: NDArray, corners: NDArray):
    x = corners[:, 0]
    y = corners[:, 1]
    sorting = np.argsort(np.sqrt(x**2 + y**2))
    corners_rect = find_fitting_rect(corners)
    x = corners_rect[:, 0]
    y = corners_rect[:, 1]
    sorting_rect = np.argsort(np.sqrt(x**2 + y**2))
    M = cv2.getPerspectiveTransform(corners[sorting].astype('float32'), corners_rect[sorting_rect].astype('float32'))
    return cv2.warpPerspective(image, M, (image.shape[1], image.shape[0]))

def find_fitting_rect(corners: NDArray):
    rect = list(cv2.minAreaRect(corners))
    rect = cv2.boxPoints(rect)
    return rect

if __name__ == "__main__":
    w, h = 100, 100
    x, y = 10, 10
    points = np.array([[815, 847], [2031, 878], [812, 1453], [2062, 1507]])
    x = points[:, 0]
    y = points[:, 1]

    #corners = np.array([[x , y], [x + w  + 10, y], [x + w, y + h + 100], [x, y + h]])
    corners = points

    print(corners)
    corners_rect = find_fitting_rect(corners)
    image = np.zeros((4000, 4000), dtype='uint8')
    image = cv2.fillPoly(image, corners.reshape(1, 4, 2), (255, 255, 255))
    image = cv2.rectangle(image, corners[0], corners[1], (255, 255, 255))
    rectified = rectify(image, corners)
    plt.subplot(121)
    plt.imshow(image)
    plt.subplot(122)
    plt.imshow(rectified)
    plt.show()
