import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

N_PER_ROW = 3
FROM = 3
TO = 7

current = 0


def add_new(img, n, title, **kwargs):
    global current
    current += 1
    plt.subplot(np.ceil(n / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img, **kwargs)
    plt.xticks([])
    plt.yticks([])


if __name__ == '__main__':
    img = cv2.imread("../assert/moon.jpg", 0)
    n = 5
    add_new(img, n, "Origin", cmap="gray")

    laplacian = cv2.Laplacian(img, cv2.CV_64F)
    add_new(laplacian, n, "Laplacian", cmap="gray")

    sobelx = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=5)
    add_new(sobelx, n, "Sobel-X", cmap="gray")

    sobely = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=5)
    add_new(sobely, n, "Sobel-Y", cmap="gray")

    origin_without_laplacian = cv2.subtract(img, laplacian, dtype=cv2.CV_64F)
    add_new(origin_without_laplacian, n, "Ori - Lap", cmap="gray")

    plt.savefig("../output/5-Sobel&Laplacian.jpg")
    plt.show()
