#ifndef PID_H
#define PID_H


#define N_K 3

#define TARGET_SPEED 25


class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  double best_error;


  /*
  * Coefficients
  */ 
  //double Kp;
  //double Ki;
  //double Kd;
  
  double K[N_K];  
  double dk[N_K];

  
  // State Machine
  int State;
  
  
  // Counters  
  unsigned int Steps;
  
  unsigned int Total_Steps;
  
  unsigned int Attempts;
  
  unsigned int index;

  double factor_I;
  
  double factor_D;
  
  double past_angle;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
