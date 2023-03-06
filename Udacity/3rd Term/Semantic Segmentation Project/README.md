# Semantic Segmentation

The goal of the project was all about to implement a Fully Connected Network for Semantic Segmentation starting from a pre-trained model that was the VGG16.

The steps were roughly the following:

* Upsampled a given fully connected layer
* Transformed a fully connected layer into a convolutional 1x1 layer
* Added skipping connections

The method implemented recalls the 2015 paper “Fully Connected Layer” from UC Berkely.

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223194198-6964d593-9ef8-4b1e-affb-5d5360289357.png">
<\p>

The network has been trained with the following parameters:

* keep_prob: 0.
* learning rate: 0.
* epochs: 10
* batch_size: 1

Besides, the loss function of the network is a cross-entropy, an Adam optimizer and a L2-regularizer for the kernel weights have
been picked.

The final loss amounted at 0.017 at the 10th epoch.

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223194262-858ecf26-1c41-44aa-a10a-0d41df1c57ff.png" width="10%" height="10%">
<\p>



Below a bunch of the results over the images elaborated.

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223194330-f1c07ad2-f210-4cf6-b76f-4b22a7693633.png">
  <img src="https://user-images.githubusercontent.com/29335742/223194378-1381fcf4-43d7-4c05-8e73-fb249207c204.png">
  <img src="https://user-images.githubusercontent.com/29335742/223194417-43698a06-52be-4f9c-a836-38cd195f6684.png">
  <img src="https://user-images.githubusercontent.com/29335742/223194479-846c8933-b899-4cf9-b515-06a5af3fa286.png">
<\p>
