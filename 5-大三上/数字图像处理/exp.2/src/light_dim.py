import cv2
import numpy as np

if __name__ == "__main__":
    ori = cv2.imread("./assert/woman.png", 0)
    light = cv2.add(ori, 80)
    dim = cv2.subtract(ori, 80)
    cv2.imshow("light", light)
    cv2.imwrite("./output/light.jpg", light)
    cv2.imshow("dim", dim)
    cv2.imwrite("./output/dim.jpg", dim)
    k = cv2.waitKey(0)
    cv2.destroyAllWindows()
