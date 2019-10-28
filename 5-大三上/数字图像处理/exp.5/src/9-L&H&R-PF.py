import cv2
import numpy as np
from numpy import fft
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320
plt.rcParams["figure.figsize"] = [8, 30]

N_PER_ROW = 2
N = 15 * 2 + 2

current = 0


def add_new(img, title, **kwargs):
    global current
    current += 1
    plt.subplot(np.ceil(N / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img, **kwargs)
    plt.xticks([])
    plt.yticks([])


def create_circular_mask(h, w, upper, lower):
    center = [int(w / 2), int(h / 2)]

    Y, X = np.ogrid[:h, :w]
    dist_from_center = np.sqrt((X - center[0]) ** 2 + (Y - center[1]) ** 2)

    mask_1 = dist_from_center <= upper
    mask_2 = lower <= dist_from_center

    return np.bitwise_and(mask_1, mask_2)


if __name__ == '__main__':
    img = cv2.imread("../assert/child.jpg", 0)
    h, w = img.shape

    f = fft.fft2(img)
    fshift = fft.fftshift(f)

    magnitude_shift = 20 * np.log(np.abs(fshift))
    add_new(magnitude_shift, "Magnitude-Shift", cmap="gray")
    add_new(img, "Origin", cmap="gray")

    for upper in [0.5, 0.4, 0.3, 0.25, 0.1, 0.01]:
        for lower in [0.5, 0.4, 0.3, 0.25, 0.1, 0.01]:
            if lower >= upper:
                continue
            else:
                upper_D = int(min(upper * w, upper * h))
                lower_D = int(min(lower * w, lower * h))
                circle_mask = create_circular_mask(h, w, upper_D, lower_D)

                # mask element-wise product
                LPF_shift = np.multiply(fshift, circle_mask)

                magnitude_LPF_shift = 20 * np.log(np.abs(LPF_shift))
                add_new(magnitude_LPF_shift, "LPF-Magnitude-[%.2f, %.2f]" % (lower, upper), cmap="gray")

                f_ishift = fft.ifftshift(LPF_shift)
                img_restore = fft.ifft2(f_ishift)
                img_restore = np.abs(img_restore)

                add_new(img_restore, "Restore-[%.2f, %.2f]" % (lower, upper), cmap="gray")

    plt.savefig("../output/9-RPF.jpg")
    plt.show()
