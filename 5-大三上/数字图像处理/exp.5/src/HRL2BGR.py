import cv2
import numpy as np
from numpy import fft
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320
# plt.rcParams["figure.figsize"] = [8, 30]

N_PER_ROW = 2
N = 3

current = 0


def add_new(img, title, **kwargs):
    global current
    current += 1
    plt.subplot(np.ceil(N / N_PER_ROW), N_PER_ROW, current)
    plt.title(title)
    plt.imshow(img, **kwargs)
    plt.xticks([])
    plt.yticks([])


def create_circular_mask(h, w, upper=None, lower=None):
    center = [int(w / 2), int(h / 2)]

    Y, X = np.ogrid[:h, :w]
    dist_from_center = np.sqrt((X - center[0]) ** 2 + (Y - center[1]) ** 2)

    if upper is None:
        return lower <= dist_from_center
    elif lower is None:
        return dist_from_center <= upper
    else:
        mask_1 = lower <= dist_from_center
        mask_2 = dist_from_center <= upper
        return np.bitwise_and(mask_1, mask_2)


def mask_and_restore(shifted_fft, mask):
    shift = np.multiply(shifted_fft, mask)
    f_ishift = fft.ifftshift(shift)
    img_restore = fft.ifft2(f_ishift)
    img_restore = np.abs(img_restore)
    return img_restore


if __name__ == '__main__':
    img = cv2.imread("../assert/child.jpg", 0)
    h, w = img.shape

    f = fft.fft2(img)
    fshift = fft.fftshift(f)

    magnitude_shift = 20 * np.log(np.abs(fshift))
    add_new(magnitude_shift, "Magnitude-Shift", cmap="gray")
    add_new(img, "Origin", cmap="gray")

    upper = 0.5
    lower = 0.01

    upper_D = int(min(upper * w, upper * h))
    lower_D = int(min(lower * w, lower * h))

    HPF_mask = create_circular_mask(h, w, lower=lower_D)
    RPF_mask = create_circular_mask(h, w, lower=lower_D, upper=upper_D)
    LPF_mask = create_circular_mask(h, w, upper=upper_D)

    B = mask_and_restore(fshift, HPF_mask)
    G = mask_and_restore(fshift, RPF_mask)
    R = mask_and_restore(fshift, LPF_mask)

    res = np.zeros((h, w, 3), dtype=np.uint8)
    res[:, :, 0] = B
    res[:, :, 1] = G
    res[:, :, 2] = R
    add_new(res, "Restore-[%.2f, %.2f]" % (lower, upper), cmap="gray")

    plt.savefig("../output/9-RPF.jpg")
    plt.show()
