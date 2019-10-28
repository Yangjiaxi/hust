import numpy as np
import cv2

from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320
plt.rcParams["figure.figsize"] = [8, 20]

N_PER_ROW = 2
N = 5 * 2

current = 0


def add_new(img, title, **kwargs):
    global current
    current += 1
    plt.subplot(np.ceil(N / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img, **kwargs)
    plt.xticks([])
    plt.yticks([])


if __name__ == '__main__':
    kernel = np.ones((3, 3), np.uint8)

    img_open = cv2.imread("../assert/j_out.jpg", 0)
    add_new(img_open, "Origin-1", cmap="gray")
    opening = cv2.morphologyEx(img_open, cv2.MORPH_OPEN, kernel)
    add_new(opening, "Opening", cmap="gray")

    img_close = cv2.imread("../assert/j_in.jpg", 0)
    add_new(img_close, "Origin-2", cmap="gray")
    closing = cv2.morphologyEx(img_close, cv2.MORPH_CLOSE, kernel)
    add_new(closing, "Closing", cmap="gray")

    img_normal = cv2.imread("../assert/j.jpg", 0)
    add_new(img_normal, "Origin-Normal", cmap="gray")
    gradient = cv2.morphologyEx(img_normal, cv2.MORPH_GRADIENT, kernel)
    add_new(gradient, "Gradient", cmap="gray")

    house = cv2.imread("../assert/house.jpg", 0)
    add_new(house, "Origin-House", cmap="gray")

    element = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
    house_dilate = cv2.dilate(house, element)
    house_erode = cv2.erode(house, element)
    house_edge = cv2.absdiff(house_dilate, house_erode)
    add_new(house_edge, "House-Edge-Plain", cmap="gray")

    ret, result = cv2.threshold(house_edge, 40, 255, cv2.THRESH_BINARY)
    add_new(result, "Result", cmap="gray")
    result = cv2.bitwise_not(result)
    add_new(result, "Result-INV", cmap="gray")

    plt.savefig("../output/3-morph-OC.jpg")
    plt.show()
