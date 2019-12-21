import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import numpy as np

lena = mpimg.imread('test_image/lena_grey.bmp')
# plt.imshow(lena, cmap='Greys_r')
# plt.axis("off")
# plt.show()

data = np.zeros((256, 2), dtype=int)
data[..., 0] = np.arange(256)

for i in lena:
    for j in i:
        data[j, 1] += 1
print(data)
plt.bar(data[..., 0], data[..., 1],color='g')
#
# data = np.arange(256)
# plt.hist(lena, data)
# print(np.shape(hist))
# print(np.shape(data))
# plt.bar(hist, bins)
plt.show()
