import pythonopencvvscppopencvfrompython as cc
import time
import cv2
from pathlib import Path
import subprocess

root = Path(__file__).parent
def cc_python(file_path: str) -> int:
    image = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)
    _, thresh = cv2.threshold(image, 255, 255, cv2.THRESH_OTSU)
    num, _ = cv2.connectedComponents(thresh)
    return num


if __name__ == "__main__":
    image_file = (root/"numbers.png").as_posix()
    its = 1000
    start = time.perf_counter()
    for i in range(its):
        a = cc_python(image_file)
        print(a)
    end = time.perf_counter()
    a = end - start
    start = time.perf_counter()
    for i in range(its):
        b = cc.image_process(image_file)
        print(b)
    end = time.perf_counter()
    b= end - start
    subprocess.call("clear")
    print(a/b)

