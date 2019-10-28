import cv2
import numpy as np

if __name__ == '__main__':
    img = cv2.imread("../assert/flower2.jpg", 0)
    rows, cols = img.shape
    M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 45, 0.6)
    dst = cv2.warpAffine(img, M, (cols, rows))
    cv2.imshow("before", img)
    cv2.imshow("after", dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
