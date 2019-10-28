import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

N_PER_ROW = 2
FROM = 3
TO = 7

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
    img = cv2.imread("../assert/lena_with_noise.jpg")

    blur_size = range(FROM, TO + 1, 2)
    n = len(blur_size)

    add_new(img, n + 1, "Origin")

    for x in blur_size:
        blur_res = cv2.medianBlur(img, x)
        add_new(blur_res, n + 1, "M-Blur=%d" % x)

    plt.savefig("../output/3-medianBlur.jpg")
    plt.show()
