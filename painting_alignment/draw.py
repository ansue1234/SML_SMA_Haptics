import cv2
# import numpy as np

img = cv2.imread("pic2.png")
# img = cv2.resize(img, (640, 480))
outer_crop_px = 50
h, w = 640, 480
img = cv2.resize(img, (640, 480))[outer_crop_px:w - outer_crop_px, outer_crop_px:h - outer_crop_px, :]
cv2.imwrite('../painting_alignment/pic3.png', img)
# canvas = np.ones((200, 200, 3), dtype = "uint8") * 255
# icon = cv2.imread('../object_detection/thinking.png')
# h, w = icon.shape[:2]
# icon = icon[:, (w - h)//2: h + (w - h)//2, :]
# icon = cv2.resize(icon, (390, 390))
# # icon = cv2.resize(icon, (100, 100))

# # font = cv2.FONT_HERSHEY_SIMPLEX
# # cv2.putText(canvas, 'Action:', (10,20), font, 0.4, (0, 0, 0), 1, cv2.LINE_AA)
# # cv2.putText(canvas, 'Rotate Right', (10,35), font, 0.4, (255, 0, 0), 1, cv2.LINE_AA)
# # cv2.putText(canvas, 'Current Task: ', (10,165), font, 0.4, (0, 0, 0), 1, cv2.LINE_AA)
# # cv2.putText(canvas, 'Matching Corners', (10,180), font, 0.4, (0, 0, 255), 1, cv2.LINE_AA)
# # icon = cv2.resize(icon, (100, 100))
# # canvas[50:150, 50:150, :] = icon
# # icon = cv2.flip(icon, 1)
# cv2.imwrite('../object_detection/thinking.png', icon)

# cv2.imshow('canvas', icon)
# cv2.waitKey(0)

# # happy face from https://www.onoursleeves.org/mental-wellness-too#
# # Thinking emoji https://stock.adobe.com/search?k=thinking+emoji&asset_id=354912886