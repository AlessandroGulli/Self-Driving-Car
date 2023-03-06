

# Traffic Sign Recognition

**Building a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set (see below for links to the project data set)
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report

### Data Set Summary & Exploration

#### 1. Used the numpy library to calculate summary statistics of the traffic signs dataset:

* The size of training set is 34799
* The size of the validation set is 12630
* The size of test set is 4410
* The shape of a traffic sign image is (34799,32,32,3)
* The number of unique classes/labels in the data set is 43

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set. It is a bar chart
showing how the data are distributed per classes.

![image](https://user-images.githubusercontent.com/29335742/223123373-ea67db30-5701-4b85-a2b1-3dc4a3269687.png)

### Design and Test a Model Architecture

#### 1. As first step, I decided to convert the images to gray scale thinking this
could have been a good approach making the network process faster as well as
targeting the most important details, since the original color images showed
unnecessary information.

As last step, I normalized the image data because in order to keep numerical
stability in dynamic range for a set of the data, as explained in the
lectures, curtaining them between 0.1 and 0.9.

I decided to generate additional data because visualizing the data
distribution I noticed that the distribution itself was pretty uneven, where
many classes had way below number of samples than mean, leading to an
innocent towards majority classes.

Therefore, to add more data to the the data set, I used the rotation
techniques, iterating trough existing images and generating new images until
enough the sum of additional images overcame the mean.

The difference between the original data set and the augmented data set is
the following picture where you can notice that now much more classes are at
the same level.

![image](https://user-images.githubusercontent.com/29335742/223123478-0fa31e61-c02a-4261-8681-ad20f844b2ee.png)

Furthermore, in order to perform the model better I decided to shuffle and
split the validation and training data. This way I provided part of the
additional data also on the validation set and not just on the training set,
avoiding to show good result only in the training part and nothing that
special in the test section.

#### 2. Model architecture

The architecture is based on Le-Net solution, just with some parameters
changes...

![image](https://user-images.githubusercontent.com/29335742/223123623-b0613847-b6cc-4741-8efa-2461059f7019.png)

#### 3. Describe how you trained your model.

Instead using the classical Gradient Descent Optimizer I discovered the
existence of AdamOptimezer which shown better performances. In order to
achieve the best outcome I chose 150 as batch size, which represented the
right compromise between smaller or bigger values of it. About the epochs, I
ran different numbers of epochs, but I noticed that the the validation
accuracy settles within 10 epochs. Therefore, I chose not to increase this
value; in my opinion you should demonstrate to reach good result of your
model with few iterations.

I haven’t changed the hyperparamters because I didn’t see improvements, on
the contrary ramping sigma up I noticed an increase of the training time.

An interesting approach is about the learning rate, which I changed for
every epoch, casting it to a minimum value of 0.001 and starting from a max
value of 0.008. I used this solution in order to accelerate the training
during initial phase smoothing it step by step, getting better results
without deriving or create instability as mentioned in the lectures.

As dropout I chose a value of 0.7 instead of the common 0.5 used in the Le-
Net solution, which prevent my model from overfitting in a better way.

#### 4. Describe the approach taken for finding a solution and getting the
validation set accuracy to be at least 0.93.

In my final model I reached a validation accuracy of 0.990 and a testing
accuracy of 0.912. In particularly the latter demonstrated that my model
wasn’t affected from overfitting.

As I mentioned before I didn’t changed the Le-Net architecture in general, I
tried to maintain the original scaffolding, changing just the depth of the
filters and the size of every patch, with the aim to target important
details from the pictures.

### Test a Model on New Images

#### 1. Here are ten German traffic signs I found on the web:

<img src="https://user-images.githubusercontent.com/29335742/223123767-47a50fb3-1a7e-45b8-b771-ea659a06c0c3.png" width="200" height="300"> <img src="https://user-images.githubusercontent.com/29335742/223123821-3259e957-b319-4c53-a9a7-aca2cfcf8371.png" width="200" height="300">
  
<img src="https://user-images.githubusercontent.com/29335742/223123913-94a879fc-70eb-4f7f-8fce-e641ab0215d0.png" width="200" height="300"> <img src="https://user-images.githubusercontent.com/29335742/223124041-06e3f14b-09e6-4e6f-b640-78a3f963e8fb.png" width="200" height="300"> 


I found it difficult to classify the “Pedestrians” and “End of all limits”.
The elaboration of the first is completely wrong, I think that the inner
shape and the complexity of the sing has lead the model to such huge
mistake.

About the second one the colour of the sign can be attributed to priority
road, so we can say they belong to the same family in somehow. It is not
justified on the other hand the failure to recognize the shape.

A possible improvement might be introducing a new layer in the covnet in
order to fill the gap concerning this aspect, with the intent to detect more
important characteristics of these type of signs. An inception layer might
do the trick.

Further, at first, I was little biased about the correct classification of
the ciphers of the speed limit sings, nonetheless my concerns, it seems that
the model works pretty good over this category.

#### 2. Discuss the model's predictions on these new traffic signs and
compare the results to predicting on the test set.

Here are the results of the prediction:

![image](https://user-images.githubusercontent.com/29335742/223124274-97939318-a091-491b-b716-a7bb1cbd2661.png)


The model was able to correctly guess 8 in 10 traffic signs, which gives an
accuracy of 80%. I think the things might change if the prospective of the
image changes and also if the complexity of the sign enhances. Anyway I’m
quite satisfied about the correct classification of the speed limit sings,
which as I mentioned before was my biggest concern.

#### 3. The code for making predictions on my final model is located in the 61th and
62th cell of the Ipython notebook.

For the first the model is rather sure that this is a Right of way at the
next intersection sign, probability of 1.0.

![image](https://user-images.githubusercontent.com/29335742/223124886-887ef014-1cae-4f80-9a24-2dbe0016920d.png)

For the second the model is rather sure that this is a Right of way at the
next intersection, probability of 1.0.

![image](https://user-images.githubusercontent.com/29335742/223124972-1a370e75-c980-4865-a997-72b86824dbcc.png)

For the third the model is rather sure that this is a Yeld, probability of
1.0.

![image](https://user-images.githubusercontent.com/29335742/223125073-f59b2513-f25d-45e5-9f58-bc53dd86e7e3.png)

For the fourth the model is rather sure that this is a Speed Limit (
km/h), probability of 1.0.

![image](https://user-images.githubusercontent.com/29335742/223125143-34c28da6-35df-44ac-af52-3f29d18ec084.png)

For the fifth the model is rather sure that this is a Pedestrians,
probability of 1.0, but it is completely way off base, even if we look at
the other probabilities. My model definitely doesn’t work with this sign.

![image](https://user-images.githubusercontent.com/29335742/223125231-255d1fec-0584-477a-9ff3-766271c6d48b.png)

For the sixth the model is quite sure that this is a Priority Road,
probability of 1.0, but it is completely way off base, even if we look at
the other probabilities. My model definitely doesn’t work with this sign.

![image](https://user-images.githubusercontent.com/29335742/223125298-1c3d677a-3cfe-4e91-b046-86d19cde5fb4.png)

For the seventh the model is quite sure that this is a Priority Road,
probability of 0.98.

![image](https://user-images.githubusercontent.com/29335742/223125388-f57c8d59-a597-4178-8728-1383eeec5c00.png)

For the eight the model is quite that this is a Keep right, probability of
1.0.

![image](https://user-images.githubusercontent.com/29335742/223125460-798ee157-f765-4651-96a1-0bed43e2c97b.png)



For the ninth the model is quite sure that this is a Speed Limit (30 km/h),
probability of 1.0.

![image](https://user-images.githubusercontent.com/29335742/223127611-c6507056-0061-46f3-bc10-65c49c34d325.png)


For the tenth the model is quite sure that this is a Road work, probability
of 1.0.

![image](https://user-images.githubusercontent.com/29335742/223127678-62e33042-4f22-4e4a-add1-9ee7ebdc06d5.png)


