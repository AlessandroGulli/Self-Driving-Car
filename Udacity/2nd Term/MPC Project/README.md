
### Model Predictive Control - Summary

The model implemented in this project is the Kinematic model which takes into account within its
equations the vehicle’s 𝒙𝒕 and 𝒚𝒕 coordinates, orientation angle 𝝍𝒕, and velocity 𝒗𝒕. In addition to that to
make the model more complete are included the cross-track error 𝒄𝒕𝒆𝒕 and psi error 𝒆𝝍𝒕. Moreover, the
actuators outputs are the acceleration 𝒂𝒕 and the steering angle 𝜹𝒕. All the terms cited are function of the
time, therefore the model combines the state and the actuations from the previous time step to calculate
the state for current time step based on the following equations:

![image](https://user-images.githubusercontent.com/29335742/223183576-e640df07-2a85-4d5f-ac46-e0ca2d2bd3c1.png)

where 𝒅𝒕 represents the time elapsed within two steps.

### Timestep Lenght and Elapsed Duration (N & dt)

After several attempts, the value respectively chosen for **N** and 𝒅𝒕 are 19 and 0.095. These values mean
that the optimizer is considering a 1,805 seconds for the event horizon. Shrinking this period of time made
the car off the track introducing a component of instability or alternatively it turned to be fall far short to
make any predictions on the trajectory, ending up with a sudden stop of the vehicle along the curves.

Full disclosure, other values for N and 𝒅𝒕 tried were 10/0.1, 15/0.1, 25/0.095, 35/0.05 and many others, all
of them introduced an erratic behaviour in the control system.


### Polynomial Fitting and MPC Preprocessing

First of all, the waypoints were transformed from map’s perspective to car’s perspective. Doing so the
process to fit a polynomial to the waypoints are much simplified since the vehicle’s x and y coordinates are
translated to the origin and the orientation angle is also null.

### Model Predictive Control with Latency

Within the simulation was included a latency which represents the reaction of the system to the actuation.
Therefore, this means the effect of the outcomes of the cinematic equations can be executed another step
later than the ideal conditions. To deal with this aspect I tuned the cost function with different weights in
order to approach, especially along the curves, the vehicle in a smoother manner strongly penalizing the
combination of velocity and delta.
