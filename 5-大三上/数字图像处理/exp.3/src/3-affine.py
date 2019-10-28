import cv2
import numpy as np

if __name__ == '__main__':
    img = cv2.imread("../assert/sudoku.jpg", 0)
    rows, cols = img.shape
    pts1 = np.float32([[50, 50], [200, 50], [50, 200]])
    pts2 = np.float32([[10, 100], [200, 50], [100, 250]])
    M = cv2.getAffineTransform(pts1, pts2)
    dst = cv2.warpAffine(img, M, (cols, rows))
    cv2.imshow("input", img)
    cv2.imshow("output", dst)
    cv2.imwrite("../output/getAffineImg.jpg", dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
