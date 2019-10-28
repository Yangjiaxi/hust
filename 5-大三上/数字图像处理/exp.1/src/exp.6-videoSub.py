import cv2

cap = cv2.VideoCapture("./assert/vtest.avi")
is_add_text = False


def add_text(frame):
    linetype = cv2.LINE_AA
    font = cv2.FONT_HERSHEY_SIMPLEX
    res = "Sub: " + "".join(text)
    cv2.putText(frame, res, (10, 500), font, 2, (255, 255, 255), 2)
    return frame


def click(event, x, y, flags, param):
    global is_add_text
    if event == cv2.EVENT_LBUTTONUP:
        is_add_text = not is_add_text


cv2.namedWindow("FRAME")
cv2.setMouseCallback("FRAME", click)

text = []

try:
    while cap.isOpened():
        ret, frame = cap.read()
        if ret:
            gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
            if is_add_text:
                gray = add_text(gray)
            cv2.imshow("FRAME", gray)

        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break
        elif k == 127:
            text = text[0:-1]
        elif k != 255:
            text.append(chr(k))

finally:
    cap.release()
    cv2.destroyAllWindows()
