The goal of the project was all about to implement a Fully Connected Network for Semantic Segmentation starting from a pre-
trained model that was the VGG16.

The steps were roughly the following:

```
 Upsampled a given fully connected layer
 Transformed a fully connected layer into a convolutional 1x1 layer
 Added skipping connections
```
The method implemented recalls the 2015 paper “Fully Connected Layer” from UC Berkely.

The network has been trained with the following parameters:

```
 keep_prob: 0.
 learning rate: 0.
 epochs: 10
 batch_size: 1
```
Besides, the loss function of the network is a cross-entropy, an Adam optimizer and a L2-regularizer for the kernel weights have
been picked.

The final loss amounted at 0.017 at the 10th epoch.


Below a bunch of the results over the images elaborated.