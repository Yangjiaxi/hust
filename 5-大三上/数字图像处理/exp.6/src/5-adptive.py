import numpy as np
import cv2

from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320
plt.rcParams["figure.figsize"] = [5, 15]

N_PER_ROW = 1
N = 4

current = 0

global_attr = {
    "cmap": "gray"
}


def add_new(img, title, **kwargs):
    global current
    current += 1
    plt.subplot(np.ceil(N / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img, **global_attr, **kwargs)
    plt.xticks([])
    plt.yticks([])


if __name__ == '__main__':
    dave = cv2.imread("../assert/dave.jpg", 0)

    dave = cv2.medianBlur(dave, 5)
    add_new(dave, "Origin")

    ret, th_bin = cv2.threshold(dave, 127, 255, cv2.THRESH_BINARY)
    add_new(th_bin, "Global Threshold (v = 127)")

    th_adp_mean = cv2.adaptiveThreshold(dave, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)
    add_new(th_adp_mean, "Adaptive Mean Threshold")

    th_adp_gauss = cv2.adaptiveThreshold(dave, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)
    add_new(th_adp_gauss, "Adaptive Gaussian Threshold")

    plt.savefig("../output/5-adaptive.jpg")
    plt.show()
