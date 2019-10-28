import cv2
import numpy as np

if __name__ == "__main__":
    image_1 = cv2.imread("./assert/flower2.jpg")
    image_2 = cv2.imread("./assert/diamond.jpg")
    res = cv2.add(image_1, image_2)
    cv2.imshow("add", res)
    k = cv2.waitKey(0)
    if k == 27:
        cv2.destroyAllWindows()
    elif k == ord("s"):
        cv2.imwrite("./output/add.jpg", res)
        cv2.destroyAllWindows()
