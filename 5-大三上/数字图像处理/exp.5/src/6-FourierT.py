import cv2
import numpy as np
from numpy import fft
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

N_PER_ROW = 3
N = 6

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
    img = cv2.imread("../assert/child.jpg", 0)

    add_new(img, "Origin", cmap="gray")

    f = fft.fft2(img)
    fshift = fft.fftshift(f)

    magnitude = 20 * np.log(np.abs(f))
    magnitude_shift = 20 * np.log(np.abs(fshift))

    add_new(magnitude, "Magnitude", cmap="gray")
    add_new(magnitude_shift, "Magnitude-Shift", cmap="gray")

    rows, cols = img.shape
    crow, ccol = int(rows / 2), int(cols / 2)
    fshift[crow - 30:crow + 30, ccol - 30:ccol + 30] = 0
    chip_magnitude = 20 * np.log(np.abs(fshift))
    add_new(chip_magnitude, "Clip", cmap="gray")

    f_ishift = fft.ifftshift(fshift)
    img_restore = fft.ifft2(f_ishift)
    img_restore = np.abs(img_restore)

    add_new(img_restore, "Restore-Gray", cmap="gray")
    add_new(img_restore, "Restore")

    plt.savefig("../output/6-Fourier.jpg")
    plt.show()
