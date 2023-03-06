 Describe the effect each of the P, I, D components had in your implementation.
```
Before introducing my method to tune the three constants of the algorithm I’d like to spend some
words about the characteristics of each of them.

First of all, I’d like to talk about the P constant, that it represents the most directly observable
effect on the car behavior since it causes the car to steer proportional and opposite the distance
from the lane center. The CTE expresses just this measure and it can be assimilated to the error to
be corrected. Therefore the mechanism is simple; if the car is far from one of the two sides it
steers hard to the opposite direction to compensate the drift.

Second, the I constant effect which contains the history of the previous error gains importance
around the curves, handing over to the P-D controller the task to reach the centre of the line.

Last but not least, the D component counteracts the P component to ring and overshoot the
midair.

An example of the implementation of the three components is shown in the Final_PID video.

Removing or smoothing the I component it causes that the car found it difficult to follow the
trajectory around the curves. You can see this behavior in the I_Removed video.

On the other hand deleting the D component the system begins to oscillate around the center line
ending up leaving the track (D_removed video).

All the videos before cited are placed into the project’s Videos folder. Unfortunately I had to record them with my
smartphone since any other applications for recording the PC screen conditioned the performance of the simulator and
in turn the car behavior.

```
 Describe how the final hyperparameters were chosen.
```
The hyperparameters were tuned manually at first seeing that automating the parameters just
with the help of the Twiddle algorithm, due to the narrow lane, made the car off the track. After a
correct choice of the parameters, I implemented the Twiddle method through which I found the
right balance of trajectories all around the track. In my simulation, I don’t interrupt the tuning
after a given number of attempts but on the contrary, the algorithm tends to adjust them until the
CTE is greater than a precise threshold.

Besides, I implemented a PID controller for the throttle too.


Altough the good results I improved the car behavior by means of the steering angle, so I
implemented for the steering controller different levels in order to change further the parameters.

Especially within the first part, when the car tries to find an initial stability, I slightly reduced the I
component to shrink the oscillation around the center line. Moreover the I component has been
tuned on the basis of the steering angle, to give more smoothness to the car driving as well as
being more reactive along the curves of the track.