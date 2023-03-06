

# Finding Lane Lines on the Road 


![76135bf54ec6c3a207fc260b439890d6f5b9af2c](https://user-images.githubusercontent.com/29335742/223119368-dfff5876-93b0-4c1e-88b5-2a079c0fd4ec.gif)
![6438471e1577a25d2c00190796737b844ed7dcad](https://user-images.githubusercontent.com/29335742/223119710-9e156402-9f1a-4487-a6d9-700e1e80d741.gif)



### Description

My pipeline consisted of 5 steps. First, I converted the images to grayscale, then I applied the Gaussian smoothing. 
After that I used the canny function with its parameters.

The next step was to apply an image mask over the canny edges found and in cascade Hough transform.

### How to test
Open the P1 jupyter notebook file
