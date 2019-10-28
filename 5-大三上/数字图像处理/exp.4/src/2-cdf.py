import cv2
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

if __name__ == '__main__':
    img = cv2.imread("../assert/fig4.jpg")
    hist, bins = np.histogram(img.flatten(), 256, [0, 256])

    cdf = hist.cumsum()
    cdf_normalized = cdf * hist.max() / cdf.max()

    plt.plot(cdf_normalized, color="b", label="Histogram")
    plt.hist(img.flatten(), 256, [0, 256], color="r", label="CDF")

    plt.xlim([0, 256])
    plt.legend()
    plt.savefig("../output/cdf.jpg")
