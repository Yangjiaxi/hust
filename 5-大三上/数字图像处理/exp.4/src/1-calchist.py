import cv2
from matplotlib import pyplot as plt
import seaborn as sb

sb.set()
sb.set_style("whitegrid")

plt.rcParams["figure.dpi"] = 320

if __name__ == '__main__':
    img = cv2.imread("../assert/fig3.jpg")
    color = ('b', 'g', 'r')
    for i, col in enumerate(color):
        hist = cv2.calcHist([img], [i], None, [256], [0, 256])
        plt.plot(hist, color=col, label="Color-" + col)
        plt.xlim([0, 256])
    plt.title("Calc Hist for Flower.jpg")
    plt.legend()
    plt.savefig("../output/calc-hist.jpg")
