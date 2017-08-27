#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

#define DT 0.095 // time step duration dt in s 

#define LF 2.67

#define NUMBER_OF_STEPS 19

#define REF_CTE 0
#define REF_EPSI 0
#define REF_V 60.5

// Weights parameters for the cost function
#define K_CTE 4.5
#define K_EPSI 0.5
#define K_V 0.265
#define K_DELTA 80000
#define K_A 20
#define K_DDELTA 0.01
#define K_DA 0.0001
#define K_AD 10000

// Lower and Upper limits for variables.
#define DED25RAD 0.436332 // 25 deg in rad, used as delta bound
#define MAXTHR 1.0 // Maximal a value
#define BOUND 1.0e3 // Bound value for other variables

using namespace std;

class MPC {
 public:
  MPC();

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
  vector<double> mpc_x;
  vector<double> mpc_y;
};

#endif /* MPC_H */