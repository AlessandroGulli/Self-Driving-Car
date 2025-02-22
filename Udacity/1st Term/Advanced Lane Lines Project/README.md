
# Advanced Lane Lines


<p align="center">
 <img src="https://user-images.githubusercontent.com/29335742/223137841-80d2edf1-73af-47e7-baf6-e246de3c7fa8.gif" alt="animated" />
</p>


## 1. Camera Calibration

As first step I use the calibration camera method in order to rule out the unwanted embedded
distortions produced by the device.

Threrefore, I implemented the procedure availing me of two OpenCV functions, respectively
findChessboardCorners and calibrateCamera. Different images of chessboards taken from
different angles were provided in order to calculate the parameters to adjust several type of
potential distortions inducted by the camera.

Applying findChessboardCorners I was able to grasp the location of internal corners of the
chessboards, which are used to fed to calibrateCamera which in turn it returns distortion
coefficients and camera calibration. After that I used undistort, whose goal is to undistort a
given image on the base of the coefficients passed.

The result of this few steps can be observed below:

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223138410-95ae0b04-397e-4c0e-82ed-deeef127101e.png" />
</p>

## 2. Pipeline

Below an image of the result of applying undistort over a test image of the dataset.

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223138492-c3e54e7e-3fe8-42cc-be8f-c45ed71abc8a.png" />
</p>

The effect of the process can be stand out at the corner of the image even if it isn’t so marked.

The most interesting part of the project was all about trying to apply several colour spaces
and different threshold to the sample image I chose. Exploring a myriad of combinations I
came to the conclusion that it could have been right for me L channel of the HLS colour space
to isolate white lines and both the B channel of the LAB colour space and V channel of the HSV
colour space to isolate yellow lines. After multiple attempts observing the result on video
output I opted for V channel as yellow lines seeker. In addition to that I firmly decided of not
using any sort of gradient thresholds that in my opinion made worse the quality of the final
outcome. On the other hand to be minimally tolerant to changes in lighting I tuned the
threshold for each channel. Moreover, I normalized the maximum values of the HLS L channel
and the V channel to 255, since the values the lane lines in these channels are affected on
lighting conditions. 
Below are examples of thresholds in the HLS L channel and the V channel:

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223138719-4a44fec2-a67e-4204-807c-0094ffdfdd73.png" width="50%" height="50%"/>
  <img src="https://user-images.githubusercontent.com/29335742/223138719-4a44fec2-a67e-4204-807c-0094ffdfdd73.png" width="50%" height="50%"/>
</p>

Below are the results of applying the binary thresholding pipeline to various sample images:

<p align="center">
  <img src="https://user-images.githubusercontent.com/29335742/223138819-4bdfe7a4-0a91-4509-b91f-ca16fbe87f2a.png" width="250" height="150"/> <img src="https://user-images.githubusercontent.com/29335742/223138998-97392b07-315a-4258-acbd-827b3600348c.png" width="250" height="150"/> <img src="https://user-images.githubusercontent.com/29335742/223139101-b99c8a17-f592-4a3e-8e37-43847e0c6ecd.png" width="250" height="150"/>
</p>
                                                                                                                             

The code for my perspective transform is titled "Warped Image" in the Jupyter notebook, in
the seventh and eighth code cells from the top. The warp() function takes as inputs an image
(img), as well as source (src) and destination (dst) points. I hardwired the source and
destination points in the following manner:

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223139189-09fe46f2-4d81-4a24-9cd5-8f662a9a1e9d.png" width="20%" height="20%"/>
</p>

Where w stands for the width and h for the height of the original image.

Below the outcome a sample of bird’s eye prospective starting from the original picture.

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223139316-0afb8772-afd5-43d1-b192-9470a02bd48f.png" width="70%" height="70%"/>
</p>                                                                                                                                         
                                                                                                                                           


The functions sliding_window_and_polyfit(14th cell) and polyfit_using_prev_fit, which identify
lane lines and fit a second order polynomial to both right and left lane lines, are clearly labeled
in the Jupyter notebook as "Finding lines from bird’s eye prospective" and "Find lines from
previous frame".

sliding_window_and_polyfit :
To make more robust the algorithm I chose to use to compute a histogram of the quarters just
left and right of the midpoint, since this approach turned to be useful to reject lines from
adjacent lanes. Besides, the function identifies ten windows from which to detect lane pixels,
each one centered on the midpoint of the pixels from the window below. Doing this as you can
see from the picture above the lane lines are tracked up to the top of the binary image. Numpy
polyfit() method is used to fit a second order polynomial to each set of pixels.


<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223139617-26b9312c-0863-4d28-b763-373ae077c89d.png" width="40%" height="40%"/>
</p>                                                                                                                                         


The image below depicts the histogram generated by sliding_window_and_polyfit; the left and
right lanes - the two peaks nearest the center - are well highlighted:

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223140005-6fcb2c86-b29e-44ef-88c7-883017172781.png" width="40%" height="40%"/>
</p>  


The polyfit_using_prev_fit function performs basically the same task, but with less
computational approach relying on a previous fit (from a previous video frame) and only
searching for lane pixels within a certain range of that fit. The green shaded area is the range
from the previous fit, and the yellow lines and red and blue pixels are from the current image:

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223140200-b7c65b1e-70ed-4d4e-9e43-abc474255d6e.png" width="40%" height="40%"/>
</p>  


The radius of curvature calculated in the code derive from


<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223140260-71d7a081-db03-49bc-aa1d-74661e5722fe.png" width="30%" height="30%"/>
</p>  


This is translated in python with the following:

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223140306-6a4437b4-e8b2-42db-a482-ac7eef3f0149.png" width="70%" height="70%"/>
</p>  


fit[0] is the first coefficient (the y-squared coefficient) of the second order polynomial fit,
and fit[1] is the second (y) coefficient. y_0 is the y position within the image upon which the
curvature calculation is based. Instead y_meters_per_pixel is the factor used for converting
from pixels to meters. In particulary this conversion was also used to generate a new fit with
coefficients in terms of meters.

Therefore the position of the car with respect to the center of the lane is calculated like this:

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223140424-f13a81ae-1c54-4496-a63e-f2d7cc48b519.png" width="70%" height="70%"/>
</p>  


where r_fit_x_int and l_fit_x_int are the x-intercepts of the right and left fits,
respectively.


So center_dist represents the difference between these intercept points and the image
midpoint.

In " Drawing lanes on the original picture" (22th cell) you can find the results of the previous
points. The draw lane function is appointed to generate the detection by means of a polygon
based on plots of the left and right fits, warped back to the perspective of the original image
using the inverse perspective matrix Minv and overlaid onto the original image.

<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223146812-de164510-1137-4e19-a868-b398a85a330a.png" width="50%" height="50%"/>
</p>  

Below is another example of the results of the draw_additional_data function, which writes text

identifying the curvature radius and vehicle position data onto the original image:


<p align="center">                                                           
  <img src="https://user-images.githubusercontent.com/29335742/223140484-d2ab57aa-2632-4c99-bca2-b9b249e381a3.png" width="50%" height="50%"/>
</p>  



