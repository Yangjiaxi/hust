import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

N_PER_ROW = 3

current = 0


def add_new(img, n, title):
    global current
    current += 1
    plt.subplot(np.ceil(n / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img)
    plt.xticks([])
    plt.yticks([])


if __name__ == '__main__':
    img = cv2.imread("../assert/lena.jpg")

    size_list = range(3, 17 + 1, 2)
    n = len(size_list)

    add_new(img, n + 1, "Origin")

    for x in size_list:
        kernel = np.ones((x, x), dtype=np.float32) / (x * x)
        dst = cv2.filter2D(img, -1, kernel)
        add_new(dst, n + 1, "K= %d" % x)

    plt.savefig("../output/1-filter2D.jpg")
    plt.show()
