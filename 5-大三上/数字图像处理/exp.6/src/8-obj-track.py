import cv2
import numpy as np

fps = 16

cap = cv2.VideoCapture(0)

# in this way it always works, because your get the right "size"

w = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH) / 3)
h = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT) / 3)

fourcc = cv2.VideoWriter_fourcc("8", "B", "P", "S")  # works, large
out = cv2.VideoWriter("./output/output.avi", fourcc, fps, (w * 3, h), True)


def make(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    lower_blue = np.array([58, 70, 110])
    upper_blue = np.array([169, 199, 247])
    mask = cv2.inRange(hsv, lower_blue, upper_blue)

    res = cv2.bitwise_and(frame, frame, mask=mask)

    kernel = np.ones((5, 5), np.uint8)
    closing = cv2.morphologyEx(res, cv2.MORPH_CLOSE, kernel)

    return np.hstack((frame, cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR), closing))


if __name__ == "__main__":
    try:
        while cap.isOpened():
            ret, frame = cap.read()
            if ret:
                frame = cv2.resize(frame, (w, h))
                result = make(frame)
                out.write(result)
                cv2.imshow("FRAME", result)

                k = cv2.waitKey(1) & 0xFF
                if k == 27:
                    break
            else:
                break

    finally:
        out.release()
        cap.release()
        cv2.destroyAllWindows()
