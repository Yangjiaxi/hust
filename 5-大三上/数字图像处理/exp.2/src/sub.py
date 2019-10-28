import cv2
import numpy as np

if __name__ == "__main__":
    ori = cv2.imread("./output/add.jpg")
    factor = cv2.imread("./assert/flower2.jpg")
    res = cv2.subtract(ori, factor)
    cv2.imshow("add", res)
    k = cv2.waitKey(0)
    if k == 27:
        cv2.destroyAllWindows()
    elif k == ord("s"):
        cv2.imwrite("./output/sub.jpg", res)
        cv2.destroyAllWindows()
