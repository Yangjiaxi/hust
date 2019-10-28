import cv2
import numpy as np

if __name__ == '__main__':
    img = cv2.imread("../assert/flowerx.png")
    res = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)
    height, width, _ = img.shape
    res = cv2.resize(img, (2 * width, 2 * height), interpolation=cv2.INTER_CUBIC)
    cv2.imshow("res", res)
    cv2.imshow("img", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
