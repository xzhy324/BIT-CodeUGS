import imageio
import glob
import numpy
import matplotlib.pyplot
import pylab
#%matplotlib inline


our_own_dataset = []
for image_file_name in glob.glob('my_own_images_5.png'):
    print("loading...",image_file_name)
    label = int(image_file_name[-5:-4])
    img_array = imageio.imread(image_file_name,as_gray=True)
    img_data = 255.0-img_array.reshape(784)
    img_data = (img_data/255.0*0.99)+0.01
    print(numpy.min(img_data))
    print(numpy.max(img_data))
    record = numpy.append(label,img_data)
    print(record)

    our_own_dataset.append(record)

    #print(our_own_dataset)
    pass
matplotlib.pyplot.imshow(our_own_dataset[0][1:].reshape(28,28),cmap='Greys',interpolation='None')
pylab.show()
print(our_own_dataset[0])
