import numpy as np
import cv2

from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320
plt.rcParams["figure.figsize"] = [10, 10]

N_PER_ROW = 3
N = 8 + 1

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
    gradient = cv2.imread("../assert/gradient.jpg", 0)
    add_new(gradient, "Origin")

    method_list = [
        "cv2.THRESH_BINARY",
        "cv2.THRESH_BINARY_INV",
        "cv2.THRESH_MASK",
        "cv2.THRESH_OTSU",
        "cv2.THRESH_TOZERO",
        "cv2.THRESH_TOZERO_INV",
        "cv2.THRESH_TRIANGLE",
        "cv2.THRESH_TRUNC"
    ]

    for ss in method_list:
        method = eval(ss)
        ret, res = cv2.threshold(gradient, 127, 255, method)
        add_new(res, ss)

    plt.savefig("../output/4-thresh.jpg")
    plt.show()
