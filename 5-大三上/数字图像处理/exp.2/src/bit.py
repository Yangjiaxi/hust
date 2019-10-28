import cv2
import numpy as np

# ratio of background image
logo_ratio = 0.25
# T: top, B: bottom, C: center
vertical_position = "T"
# L: left, R: right, C: center
horizontal_position = "R"

background_path = "./assert/hust.jpg"
icon_path = "./assert/hustlogo.bmp"

# 四个角落
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
            "Keyword `vertical` expected {`L`, `R`, `C`}, got `%s`" % vertical
        )

    return (begin_row, begin_col), (end_row, end_col)


if __name__ == "__main__":
    back = cv2.imread(background_path)
    icon = cv2.imread(icon_path)

    back_rows, back_cols, back_channels = back.shape
    icon_rows, icon_cols, icon_channels = icon.shape

    # 尺寸变换
    ratio_rows, ratio_cols = logo_ratio * back_rows, logo_ratio * back_cols
    if ratio_rows > ratio_cols:
        roi_rows, roi_cols = (int(ratio_rows), int(icon_cols * ratio_rows / icon_rows))
    else:
        roi_rows, roi_cols = (int(icon_rows * ratio_cols / icon_cols), int(ratio_cols))

    # print(get_position_pair(back_rows, back_cols, roi_rows, roi_cols, vertical="B"))

    # 提取roi
    (bx, by), (ex, ey) = get_position_pair(
        back_rows,
        back_cols,
        roi_rows,
        roi_cols,
        vertical=vertical_position,
        horizontal=horizontal_position,
    )
    roi_data = back[bx:ex, by:ey]

    # 嵌入图片放缩
    icon = cv2.resize(icon, (roi_cols, roi_rows))

    # 嵌入转灰度图
    gray_icon = cv2.cvtColor(icon, cv2.COLOR_BGR2GRAY)

    # 阈值分割 -> 01图，1->代表无嵌入图部分
    ret, mask_front = cv2.threshold(gray_icon, 175, 255, cv2.THRESH_TRIANGLE)

    # 01反转 1: 嵌入图部分
    mask_inv = cv2.bitwise_not(mask_front)

    # mask_front & roi_data -> 提取原图无嵌入部分
    roi_clean = cv2.bitwise_and(roi_data, roi_data, mask=mask_front)

    # mask_inv & icon -> 提取嵌入图
    icon_cut = cv2.bitwise_and(icon, icon, mask=mask_inv)

    # 相加
    roi_res = cv2.add(roi_clean, icon_cut)

    # 拼回
    back[bx:ex, by:ey] = roi_res

    cv2.imshow("result", back)
    k = cv2.waitKey(0)
    if k == 27:
        cv2.destroyAllWindows()
    elif k == ord("s"):
        cv2.imwrite("./output/bit.jpg", back)
        cv2.destroyAllWindows()
