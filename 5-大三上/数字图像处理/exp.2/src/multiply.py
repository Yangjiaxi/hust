import cv2
import numpy as np

if __name__ == "__main__":
    ori = cv2.imread("./assert/woman.png", 0)
    res = cv2.multiply(ori, 1.5)

    cv2.imshow("origin", ori)

    cv2.imshow("multiply", res)
    cv2.imwrite("./output/multiply.jpg", res)
    k = cv2.waitKey(0)
    cv2.destroyAllWindows()
