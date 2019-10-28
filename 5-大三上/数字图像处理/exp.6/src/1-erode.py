import numpy as np
import cv2

if __name__ == '__main__':
    img = cv2.imread("../assert/j.jpg", 0)

    kernel = np.ones((5, 5), np.uint8)
    erosion = cv2.erode(img, kernel, iterations=1)

    res = np.hstack((img, erosion))

    cv2.imshow("image", res)
    cv2.waitKey(0)
    cv2.imwrite("../output/1-eroded.jpg", res)
    cv2.destroyAllWindows()
