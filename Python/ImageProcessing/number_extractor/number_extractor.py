import numpy as np
import cv2


def remove_lines(bin_image: np.ndarray, thresh: int):
    h = remove_lines_v(bin_image, thresh)
    without_lines = remove_lines_h(h, thresh)
    return without_lines


def remove_lines_h(bin_image: np.ndarray, thresh: int):
    # bin_image = cv2.bitwise_not(bin_image)
    _, cols = bin_image.shape
    v_size = cols // thresh
    v_struct = cv2.getStructuringElement(cv2.MORPH_RECT, (2, v_size), (-1, -1))
    v_lines = cv2.morphologyEx(bin_image, cv2.MORPH_OPEN, v_struct)
    v_removed = cv2.add(bin_image, v_lines)
    cv2.imshow("V line", v_lines)
    return v_removed


def remove_lines_v(bin_image: np.ndarray, thresh: int):
    bin_image = cv2.bitwise_not(bin_image)
    rows, _ = bin_image.shape
    h_size = rows // thresh
    h_struct = cv2.getStructuringElement(cv2.MORPH_RECT, (h_size, 1), (-1, -1))
    h_lines = cv2.morphologyEx(bin_image, cv2.MORPH_OPEN, h_struct)
    h_removed = cv2.add(bin_image, h_lines)
    cv2.imshow("H removed", h_removed)
    return h_removed


def main():
    cv2.destroyAllWindows()
    num_image = cv2.imread("numbers.png")
    num_image_g = cv2.cvtColor(num_image, cv2.COLOR_BGR2GRAY)
    _, num_th = cv2.threshold(num_image_g, 127, 255, cv2.THRESH_BINARY)

    wo_lines = remove_lines(num_th, 20)
    cv2.imshow("Numbers", wo_lines)
    while cv2.waitKey() != ord("q"):
        pass
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
