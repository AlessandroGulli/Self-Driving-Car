#ifndef VEHICLE
#define VEHICLE

#include <vector>
#include <map>
#include <string>

using namespace std;

class Vehicle {
public:

  double s;
  double d;
  double v;
  
  
  /**
  * Constructors
  */
  Vehicle();
  Vehicle(double s, double d, double v);

  /**
  * Destructor
  */
  virtual ~Vehicle();

  
};

#endif