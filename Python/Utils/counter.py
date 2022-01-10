#!/usr/bin/env python3

import cv2
import numpy as np

if __name__ == "__main__":
    image = np.zeros((200, 600, 3)).astype("uint8")
    count = 0
    image_c = cv2.putText(
        image.copy(),
        str(count),
        (20, 140),
        cv2.FONT_HERSHEY_SIMPLEX,
        5,
        (224, 123, 22),
        3,
    )
    cv2.imshow("Counter", image_c)
    while cv2.waitKey() != ord("q"):
        count += 1
        image_c = cv2.putText(
            image.copy(),
            str(count),
            (20, 140),
            cv2.FONT_HERSHEY_SIMPLEX,
            5,
            (224, 123, 22),
            3,
        )
        cv2.imshow("Counter", image_c)
