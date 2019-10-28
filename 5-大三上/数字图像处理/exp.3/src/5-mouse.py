import cv2
import numpy as np

img = cv2.imread("../assert/sudoku.jpg")


def init_img():
    return np.zeros_like(img, dtype=np.uint8)


board = init_img()  # to draw
panel = init_img()  # temp to show
count = 0  # -> 4 finish
point_list = []  # 4-point -> to rect

width, height, channel = img.shape


def draw(event, x, y, flags, param):
    global board, panel, count
    if count < 4:
        if event == cv2.EVENT_MOUSEMOVE:
            panel = np.zeros_like(img, dtype=np.uint8)
            add_point(panel, x, y)
        elif event == cv2.EVENT_LBUTTONUP:
            count += 1
            print("%d: (%d, %d)" % (count, x, y))
            point_list.append((x, y))
            add_point(board, x, y)
            if count == 4:
                print(point_list)
                reshape()


def reshape():
    pts1 = np.float32(point_list)
    pts2 = np.float32([[0, 0], [height, 0], [0, width], [height, width]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dst = cv2.warpPerspective(img, M, (height, width))
    cv2.imshow("Result", dst)


def add_point(target, x, y):
    cv2.circle(target, (x, y), 3, (0, 0, 255), -1)


def extract(a, b):
    gray_b = cv2.cvtColor(b, cv2.COLOR_BGR2GRAY)
    ret, mask_front = cv2.threshold(gray_b, 0, 255, cv2.THRESH_BINARY_INV)
    mask_inv = cv2.bitwise_not(mask_front)
    a_clean = cv2.bitwise_and(a, a, mask=mask_front)
    b_cut = cv2.bitwise_and(b, b, mask=mask_inv)
    return cv2.add(a_clean, b_cut)


if __name__ == '__main__':
    cv2.namedWindow("image")
    cv2.setMouseCallback("image", draw)
    try:
        while 1:
            res = extract(img, panel)
            res = extract(res, board)
            cv2.imshow("image", res)
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break
    finally:
        cv2.destroyAllWindows()
