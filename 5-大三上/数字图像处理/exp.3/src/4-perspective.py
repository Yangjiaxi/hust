import cv2
import numpy as np

if __name__ == '__main__':
    img = cv2.imread("../assert/news.jpg", 0)
    rows, cols = img.shape
    pts1 = np.float32([[56, 65], [368, 52], [28, 387], [389, 390]])
    pts2 = np.float32([[0, 0], [300, 0], [0, 300], [300, 300]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dst = cv2.warpPerspective(img, M, (200, 200))
    cv2.imshow("input", img)
    cv2.imshow("output", dst)
    cv2.imwrite("../output/getPerspective.jpg", dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
