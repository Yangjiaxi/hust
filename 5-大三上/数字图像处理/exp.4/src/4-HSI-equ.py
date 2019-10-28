import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320


def hist(target, title):
    hist, bins = np.histogram(target.flatten(), 256, [0, 256])

    cdf = hist.cumsum()
    cdf_normalized = cdf * hist.max() / cdf.max()

    plt.plot(cdf_normalized, color="b", label="Histogram")
    plt.hist(target.flatten(), 256, [0, 256], color="r", label="CDF")

    plt.xlim([0, 256])
    plt.legend()
    plt.title(title)
    plt.show()


if __name__ == '__main__':
    img = cv2.imread("../assert/fig3.jpg")

    # HLS为HSI的分段定义法
    hls_img = cv2.cvtColor(img, cv2.COLOR_BGR2HLS)

    row1 = np.copy(img)
    row2 = np.hstack([hls_img[:, :, i] for i in range(0, 3)])

    hls_img[:, :, 2] = cv2.equalizeHist(hls_img[:, :, 2])
    res = cv2.cvtColor(hls_img, cv2.COLOR_HLS2BGR)

    row1 = np.hstack((row1, res))
    row1 = np.hstack((row1, cv2.cvtColor(hls_img[:, :, 2], cv2.COLOR_GRAY2BGR)))

    # cv2.imshow("1", row1)
    # cv2.imshow("2", row2)

    pic = np.vstack((row1, cv2.cvtColor(row2, cv2.COLOR_GRAY2BGR)))

    cv2.imshow("RES", pic)

    # hist(img, "hist for origin")
    # hist(res, "hist for post")

    rgb_equ = np.zeros_like(img)

    for i in range(0, 3):
        rgb_equ[:, :, i] = cv2.equalizeHist(img[:, :, i])

    print(rgb_equ.shape)

    cv2.imshow("RGB-equ", rgb_equ)

    cv2.waitKey(0)
    cv2.destroyAllWindows()
