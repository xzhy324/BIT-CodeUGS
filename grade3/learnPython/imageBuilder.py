from PIL import Image
import numpy as np

'''
test_img = Image.open("1.png")
arr = np.asarray(test_img, dtype=np.uint8)
img = Image.fromarray(arr,'RGBA')
img.save('12.png')
'''
img = Image.new(mode="RGB", size=(64, 64))
img.show()
