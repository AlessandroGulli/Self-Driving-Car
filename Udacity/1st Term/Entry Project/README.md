

# Finding Lane Lines on the Road 

### Description

My pipeline consisted of 5 steps. First, I converted the images to grayscale, then I applied the Gaussian smoothing. 
After that I used the canny function with its parameters.

The next step was to apply an image mask over the canny edges found and in cascade Hough transform.

### How to test
Open the P1 jupyter notebook file
