import cv2

if __name__ == "__main__":
    flags = [x for x in dir(cv2) if x.startswith("COLOR_")]
    print(flags)
    print("Total: %d" % len(flags))
