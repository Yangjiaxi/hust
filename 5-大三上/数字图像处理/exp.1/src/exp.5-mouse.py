import cv2
import numpy as np

colorList = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]
modeList = ["LINE", "CIRCLE", "RECTANGLE"]

state = {"drawing": False, "mode": 0, "color": 0}

ix, iy = -1, -1
r = 0

HEIGHT = 512
WIDTH = 512

tmp = np.zeros((WIDTH, HEIGHT, 3), np.uint8)
img = np.zeros((WIDTH, HEIGHT, 3), np.uint8)

linetype = cv2.LINE_AA
font = cv2.FONT_HERSHEY_SIMPLEX


def draw(event, x, y, flags, param):
    global ix, iy, r, img, tmp
    mode = modeList[state["mode"]]
    color = colorList[state["color"]]
    if event == cv2.EVENT_LBUTTONDOWN:
        state.update({"drawing": True})
        ix, iy = x, y
    elif event == cv2.EVENT_MOUSEMOVE and flags == cv2.EVENT_FLAG_LBUTTON:
        if state["drawing"] == True:
            tmp = np.zeros((512, 512, 3), np.uint8)
            if mode == "LINE":
                cv2.line(tmp, (ix, iy), (x, y), color, 3)
            elif mode == "RECTANGLE":
                cv2.rectangle(tmp, (ix, iy), (x, y), color, -1)
            elif mode == "CIRCLE":
                r = int(np.sqrt(np.min(x - ix, 0) ** 2 + np.min(y - iy, 0) ** 2))
                cv2.circle(tmp, (ix, iy), r, color, -1)
    elif event == cv2.EVENT_LBUTTONUP:
        state.update({"drawing": False})
        img = extract(img, tmp)
        tmp = np.zeros((512, 512, 3), np.uint8)


def extract(a, b):
    gray_b = cv2.cvtColor(b, cv2.COLOR_BGR2GRAY)
    ret, mask_front = cv2.threshold(gray_b, 0, 255, cv2.THRESH_BINARY_INV)
    mask_inv = cv2.bitwise_not(mask_front)
    a_clean = cv2.bitwise_and(a, a, mask=mask_front)
    b_cut = cv2.bitwise_and(b, b, mask=mask_inv)
    res = cv2.add(a_clean, b_cut)
    return res


def drawText():
    color = colorList[state["color"]]
    mode = modeList[state["mode"]]
    cv2.rectangle(img, (0, 0), (175, 60), (0, 0, 0), -1)
    cv2.rectangle(img, (0, 0), (175, 60), color, 3)
    cv2.putText(img, "COLOR : {}".format(color), (0, 20), font, 0.5, color)
    cv2.putText(img, "SHAPE : {}".format(mode), (0, 50), font, 0.5, color)


cv2.namedWindow("image")
cv2.setMouseCallback("image", draw)

try:
    while 1:
        drawText()

        res = extract(img, tmp)
        cv2.imshow("image", res)

        k = cv2.waitKey(1) & 0xFF
        if k == ord("m"):
            m = state["mode"] + 1
            state.update({"mode": (m) % (len(modeList))})
        elif k == ord("c"):
            c = state["color"] + 1
            state.update({"color": (c) % (len(colorList))})
        elif k == ord("x"):
            img = np.zeros((512, 512, 3), np.uint8)
        elif k == 27:
            break
finally:
    cv2.destroyAllWindows()
