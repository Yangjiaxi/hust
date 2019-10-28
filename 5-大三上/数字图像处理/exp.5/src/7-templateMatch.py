import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")
plt.rcParams["figure.dpi"] = 200
plt.rcParams["figure.figsize"] = [8, 20]

N_PER_ROW = 2
N = 6 * 2 + 2

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
    img = cv2.imread("../assert/lena-2.jpg", 0)

    template = cv2.imread("../assert/eye-2.jpg", 0)
    h, w = template.shape

    methods = ['cv2.TM_CCOEFF', 'cv2.TM_CCOEFF_NORMED', 'cv2.TM_CCORR',
               'cv2.TM_CCORR_NORMED', 'cv2.TM_SQDIFF', 'cv2.TM_SQDIFF_NORMED']

    add_new(img, "Origin", cmap="gray")
    add_new(template, "Target")

    for mtd_ss in methods:
        img_copy = img.copy()
        method = eval(mtd_ss)
        res = cv2.matchTemplate(img_copy, template, method)
        min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
        if method in [cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED]:
            top_left = min_loc
        else:
            top_left = max_loc
        bottom_right = (top_left[0] + w, top_left[1] + h)
        cv2.rectangle(img_copy, top_left, bottom_right, 255, 2)

        add_new(res, "Res" + mtd_ss, cmap="gray")
        add_new(img_copy, "Detect" + mtd_ss)

    plt.savefig("../output/7-match.jpg")
    plt.show()
