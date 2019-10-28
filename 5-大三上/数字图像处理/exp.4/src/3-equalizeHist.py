import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

if __name__ == '__main__':
    img = cv2.imread("../assert/fig5.jpg", 0)
    equ = cv2.equalizeHist(img)
    res = np.hstack((img, equ))

    cv2.imshow("img", img)
    cv2.imshow("equ", equ)
    cv2.imshow("res", res)
    cv2.imwrite("../output/histEqu.jpg", res)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
