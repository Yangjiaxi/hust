import cv2
import numpy as np

ratio_list = [0.1, 0.2, 0.25, 0.3, 0.5]
vpos_enum = ["T", "C", "B"]
hpos_enum = ["L", "C", "R"]
pos_list = [(a, b) for a in vpos_enum for b in hpos_enum]

ratio_index = 0
pos_index = 0

cap = cv2.VideoCapture(0)

width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH) + 0.5)
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT) + 0.5)
size = (width, height)

fourcc = cv2.VideoWriter_fourcc(*"XVID")
out = cv2.VideoWriter("./output/output.avi", fourcc, 20.0, size)

video = cv2.VideoCapture("./assert/vtest.avi")


text = []
is_add_text = False


def get_position_pair(
    ori_rows, ori_cols, cut_rows, cut_cols, horizontal="L", vertical="T"
):
    if ori_rows < cut_rows or ori_cols < cut_cols:
        raise ValueError("Background is not big enough to embed such icon.")
    if horizontal == "L":
        begin_col = 0
        end_col = cut_cols
    elif horizontal == "R":
        begin_col = ori_cols - cut_cols
        end_col = ori_cols
    elif horizontal == "C":
        begin_col = int((ori_cols - cut_cols) / 2)
        end_col = int((ori_cols + cut_cols) / 2)
    else:
        raise ValueError(
            "Keyword `horizontal` expected {`L`, `R`, `C`}, got `%s`" % horizontal
        )

    if vertical == "T":
        begin_row = 0
        end_row = cut_rows
    elif vertical == "B":
        begin_row = ori_rows - cut_rows
        end_row = ori_rows
    elif vertical == "C":
        begin_row = int((ori_rows - cut_rows) / 2)
        end_row = int((ori_rows + cut_rows) / 2)
    else:
        raise ValueError(
            "Keyword `vertical` expected {`T`, `B`, `C`}, got `%s`" % vertical
        )

    return (begin_row, begin_col), (end_row, end_col)


def add_text(frame):
    linetype = cv2.LINE_AA
    font = cv2.FONT_HERSHEY_SIMPLEX
    res = "Sub: " + "".join(text)
    cv2.putText(frame, res, (10, 100), font, 2, (255, 255, 255), 2)
    return frame


def click(event, x, y, flags, param):
    global is_add_text
    if event == cv2.EVENT_LBUTTONUP:
        is_add_text = not is_add_text


def extract(img):
    # 嵌入转灰度图
    bg = np.zeros(img.shape, np.uint8)

    gray_b = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    ret, mask_front = cv2.threshold(gray_b, 127, 255, cv2.THRESH_BINARY)
    mask_inv = cv2.bitwise_not(mask_front)
    a_clean = cv2.bitwise_and(bg, bg, mask=mask_front)
    b_cut = cv2.bitwise_and(img, img, mask=mask_inv)
    res = cv2.add(a_clean, b_cut)

    return res


def make(front, back):
    back_rows, back_cols, back_channels = back.shape
    front_rows, front_cols, front_channels = front.shape

    ratio = ratio_list[ratio_index % len(ratio_list)]
    ratio_rows, ratio_cols = ratio * back_rows, ratio * back_cols
    if ratio_rows > ratio_cols:
        roi_rows, roi_cols = (
            int(ratio_rows),
            int(front_cols * ratio_rows / front_rows),
        )
    else:
        roi_rows, roi_cols = (
            int(front_rows * ratio_cols / front_cols),
            int(ratio_cols),
        )

    (vertical_position, horizontal_position) = pos_list[pos_index % len(pos_list)]
    (bx, by), (ex, ey) = get_position_pair(
        back_rows,
        back_cols,
        roi_rows,
        roi_cols,
        vertical=vertical_position,
        horizontal=horizontal_position,
    )
    roi_data = back[bx:ex, by:ey]
    front = cv2.resize(front, (roi_cols, roi_rows))
    gray_front = cv2.cvtColor(front, cv2.COLOR_BGR2GRAY)
    ret, mask_front = cv2.threshold(gray_front, 175, 255, cv2.THRESH_TRIANGLE)
    mask_inv = cv2.bitwise_not(mask_front)
    roi_clean = cv2.bitwise_and(roi_data, roi_data, mask=mask_front)
    icon_cut = cv2.bitwise_and(front, front, mask=mask_inv)
    roi_res = cv2.add(roi_clean, icon_cut)
    back[bx:ex, by:ey] = roi_res

    return back


cv2.namedWindow("FRAME")
cv2.setMouseCallback("FRAME", click)

try:
    while cap.isOpened() and video.isOpened():
        ret1, frame = cap.read()
        ret2, bg_frame = video.read()
        if ret1 and ret2:
            res = make(frame, bg_frame)
            if is_add_text:
                res = add_text(res)
            cv2.imshow("FRAME", res)
            # cv2.imshow("BACK", bg_frame)
            out.write(res)

        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break
        elif k == 127:
            text = text[0:-1]
        elif k == 91:
            pos_index += 1
        elif k == 93:
            ratio_index += 1
        elif k != 255:
            text.append(chr(k))

finally:
    cap.release()
    video.release()
    cv2.destroyAllWindows()
