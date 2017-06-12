import csv
import cv2
import math
import numpy as np
from PIL import Image        
import matplotlib.pyplot as plt
from os import getcwd


from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split


from keras.models import Sequential, model_from_json
from keras.layers import Flatten, Dense, Lambda, Dropout, Activation
from keras.layers import Convolution2D, MaxPooling2D, Cropping2D
from keras.regularizers import l2, activity_l2
from keras.optimizers import Adam
from keras.callbacks import ModelCheckpoint, Callback

import tensorflow as tf
tf.python.control_flow_ops = tf

from keras import models, optimizers, backend
from keras.layers import core, convolutional, pooling
from sklearn import model_selection


def preprocessing_image(img):
    
    new_img = cv2.GaussianBlur(img, (3,3), 0)

    new_img = cv2.cvtColor(new_img, cv2.COLOR_BGR2RGB)
    return new_img

def random_distort(img, angle):
    ''' 
    random distortion to dataset images
    '''
    new_img = img.astype(float)
    # random brightness 
    value = np.random.randint(-28, 28)
    if value > 0:
        mask = (new_img[:,:,0] + value) > 255 
    if value <= 0:
        mask = (new_img[:,:,0] + value) < 0
    new_img[:,:,0] += np.where(mask, 0, value)
    # random shadow 
    h,w = new_img.shape[0:2]
    mid = np.random.randint(0,w)
    factor = np.random.uniform(0.6,0.8)
    if np.random.rand() > .5:
        new_img[:,0:mid,0] *= factor
    else:
        new_img[:,mid:w,0] *= factor
    # randomly shift horizon
    h,w,_ = new_img.shape
    horizon = 2*h/5
    v_shift = np.random.randint(-h/8,h/8)
    pts1 = np.float32([[0,horizon],[w,horizon],[0,h],[w,h]])
    pts2 = np.float32([[0,horizon+v_shift],[w,horizon+v_shift],[0,h],[w,h]])
    M = cv2.getPerspectiveTransform(pts1,pts2)
    new_img = cv2.warpPerspective(new_img,M,(w,h), borderMode=cv2.BORDER_REPLICATE)
    return (new_img.astype(np.uint8), angle)	
	

def generate_training_data(images, angles, batch_size=128, validation_flag=False):
    '''
    method for the model training data generator to process, distort, and load images, in order to feed the model. 
    '''
    images, angles = shuffle(images, angles)
    X,y = ([],[])
    while True:       
        for i in range(len(angles)):
            img = images[i]            			
            angle = angles[i]
            img = preprocessing_image(img)
            if not validation_flag:
                img, angle = random_distort(img, angle)
            X.append(img)
            y.append(angle)
            if len(X) == batch_size:
                yield (np.array(X), np.array(y))
                X, y = ([],[])
                images, angles = shuffle(images, angles)
            # flipping, if steering angle is higher than 0.3
            if abs(angle) > 0.3:
                img = cv2.flip(img, 1)
                angle *= -1
                X.append(img)
                y.append(angle)
                if len(X) == batch_size:
                    yield (np.array(X), np.array(y))
                    X, y = ([],[])
                    images, angles = shuffle(images, angles)

					

					
lines = []
with open('./data/driving_log.csv') as csvfile:    
    reader = csv.reader(csvfile)
    for line in reader:
        lines.append(line)
        
      
        
images = []
measurements = []
for line in lines:
    source_path = line[0]    
    filename = source_path.split('/')[-1]
    current_path = './data/IMG/' + filename
    image = cv2.imread(current_path)    
    images.append(image)    
    measurement = float(line[3])
    measurements.append(measurement)
   
X_train = np.array(images)
y_train = np.array(measurements) 

# split into train/test sets
image_train, image_test, angles_train, angles_test = train_test_split(X_train, y_train, test_size=0.05, random_state=43) 

print('Train set:', image_train.shape, angles_train.shape)
print('Test set:', image_test.shape, angles_test.shape)

###### ConvNet Structure ######

model = Sequential()

# Normalize
model.add(Lambda(lambda x: x / 255.0 - 0.5, input_shape = (160,320,3)))

# Cropping images
model.add(Cropping2D(cropping=((70,25), (60,60))))

# Add three 5x5 convolution layers (output depth 24, 36, and 48), each with 2x2 stride
model.add(Convolution2D(24, 5, 5, subsample = (2,2), activation = "relu"))
model.add(Convolution2D(36, 5, 5, subsample = (2,2), activation = "relu"))
model.add(Convolution2D(48, 5, 5, subsample = (2,2), activation = "relu"))


# Add two 3x3 convolution layers (output depth 64, and 64)
model.add(Convolution2D(64, 3, 3, activation = "relu"))
model.add(Convolution2D(64, 3, 3, activation = "relu"))

# Add a flatten layer
model.add(Flatten())

# Add three fully connected layers (depth 100, 50, 10) and regularizations
model.add(Dense(100, W_regularizer=l2(0.00001)))
model.add(Activation('relu'))
model.add(Dense(50, W_regularizer=l2(0.00001)))
model.add(Activation('relu'))
model.add(Dense(10, W_regularizer=l2(0.00001)))
model.add(Activation('relu'))
model.add(Dense(1, W_regularizer=l2(0.00001)))

model.compile(loss = 'mse', optimizer =optimizers.Adam(lr=1e-04))

# Generators
train_gen = generate_training_data(image_train, angles_train, validation_flag=False, batch_size=64)
val_gen = generate_training_data(image_train, angles_train, validation_flag=True, batch_size=64)
#test_gen = generate_training_data(image_test, angles_test, validation_flag=True, batch_size=64)

checkpoint = ModelCheckpoint('model{epoch:02d}.h5')

history = model.fit_generator(train_gen, validation_data=val_gen, nb_val_samples=2560, samples_per_epoch=23040, nb_epoch=20, verbose=2, callbacks=[checkpoint])


model.save('model.h5')

exit()
