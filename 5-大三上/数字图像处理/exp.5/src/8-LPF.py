import cv2
import numpy as np
from numpy import fft
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320
plt.rcParams["figure.figsize"] = [8, 20]

N_PER_ROW = 2
N = 5 * 2 + 2

current = 0


def add_new(img, title, **kwargs):
    global current
    current += 1
    plt.subplot(np.ceil(N / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img, **kwargs)
    plt.xticks([])
    plt.yticks([])


def create_circular_mask(h, w, radius):
    center = [int(w / 2), int(h / 2)]

    Y, X = np.ogrid[:h, :w]
    dist_from_center = np.sqrt((X - center[0]) ** 2 + (Y - center[1]) ** 2)

    mask = dist_from_center <= radius
    return mask


if __name__ == '__main__':
    img = cv2.imread("../assert/child.jpg", 0)
    h, w = img.shape

    f = fft.fft2(img)
    fshift = fft.fftshift(f)

    magnitude_shift = 20 * np.log(np.abs(fshift))
    add_new(magnitude_shift, "Magnitude-Shift", cmap="gray")
    add_new(img, "Origin", cmap="gray")

    for ratio in [0.5, 0.4, 0.3, 0.25, 0.1]:
        D_0 = int(min(ratio * w, ratio * h))
        circle_mask = create_circular_mask(h, w, D_0)

        # mask element-wise product
        LPF_shift = np.multiply(fshift, circle_mask)

        magnitude_LPF_shift = 20 * np.log(np.abs(LPF_shift))
        add_new(magnitude_LPF_shift, "LPF-Magnitude-%.2f" % ratio, cmap="gray")

        f_ishift = fft.ifftshift(LPF_shift)
        img_restore = fft.ifft2(f_ishift)
        img_restore = np.abs(img_restore)

        add_new(img_restore, "Restore-%.2f" % ratio, cmap="gray")

    plt.savefig("../output/8-LPF.jpg")
    plt.show()
