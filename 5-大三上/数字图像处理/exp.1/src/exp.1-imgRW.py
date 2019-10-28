import cv2
import numpy as np

img = cv2.imread("./assert/test.png", 1)
cv2.imshow("image", img)
k = cv2.waitKey(0)
if k == 27:
    cv2.destroyAllWindows()
elif k == ord("s"):
    cv2.imwrite("./output/test2.jpg", img)
    cv2.destroyAllWindows()
