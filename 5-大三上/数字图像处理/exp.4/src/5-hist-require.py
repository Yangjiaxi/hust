import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320


def plot_hist(input, title, color='r'):
    hist, bins = np.histogram(input.flatten(), 256, [0, 256])

    cdf = hist.cumsum()
    cdf_normalized = cdf * hist.max() / cdf.max()

    plt.plot(cdf_normalized, color="b", label="Histogram " + title)
    plt.hist(input.flatten(), 256, [0, 256], color=color, label="CDF " + title)

    plt.xlim([0, 256])
    plt.legend()
    plt.title(title)


def get_cumsum_hist(img):
    row, col = np.shape(img)
    hist, bins = np.histogram(img.flatten(), 256, [0, 256])
    cdf = hist.cumsum()
    return cdf / (row * col)


def hist_spec(origin_img, target_img):
    target_hist = get_cumsum_hist(origin_img)
    refer_hist = get_cumsum_hist(target_img)

    match_table = np.zeros(256, dtype=np.uint8)
    for i in range(256):
        diff = np.abs(target_hist[i] - refer_hist[i])
        best_match = i
        for j in range(i, 256):
            if np.abs(target_hist[i] - refer_hist[j]) < diff:
                diff = np.abs(target_hist[i] - refer_hist[j])
                best_match = j
        match_table[i] = best_match
    result = cv2.LUT(origin_img, match_table)
    return result


if __name__ == '__main__':
    origin = cv2.imread("../assert/fig7A.jpg")
    target = cv2.imread("../assert/fig7B.jpg")

    w, h, c = origin.shape
    w = int(w / 3)
    h = int(h / 3)
    origin = cv2.resize(origin, (h, w))
    target = cv2.resize(target, (h, w))

    to_save = np.copy(target)
    to_save = np.hstack((to_save, origin))

    # plot_hist(origin[:, :, 0], "Origin")
    # plt.show()
    # plot_hist(target[:, :, 0], "Target")
    # plt.show()

    # cv2.imshow("origin", origin)
    # cv2.imshow("target", target)

    result = np.zeros_like(origin)

    for i in range(0, 3):
        result[:, :, i] = hist_spec(origin[:, :, i], target[:, :, i])

    to_save = np.hstack((to_save, result))

    # cv2.imshow("origin-changed", result)

    cv2.imshow("ALL", to_save)

    # for i in range(0, 3):
    #     plot_hist(result[:, :, i], "Result-%d" % i, color='b')
    #     plot_hist(target[:, :, i], "Target-%d" % i, color='r')
    #     plt.show()

    cv2.waitKey(0)
    cv2.destroyAllWindows()
