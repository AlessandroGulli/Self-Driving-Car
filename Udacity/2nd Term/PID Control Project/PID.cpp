#include "PID.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd)
{
	PID::K[0] = Kp;
	PID::K[1] = Ki;
	PID::K[2] = Kd;	
	
	PID::dk[0] = 0.1*Kp;
	PID::dk[1] = 0.1*Ki;
    PID::dk[2] = 0.1*Kd;
	
	PID::best_error = std::numeric_limits<double>::max();
	
	PID::State = 1;
	
	PID::index = 0;
	
	PID::Steps = 0;

	PID::Attempts = 200;
	
	PID::factor_I = 0;
	
	PID::factor_D = 0;
	
	PID::past_angle = 0;

}

void PID::UpdateError(double cte) 
{
    
	d_error = cte - p_error;
    p_error = cte;
    i_error += cte;

	
	index++;

	
	if(index > 2)
	{
		index = 0;
	}
	
	if(cte > abs(0.000001))
	{		
		K[index] += dk[index];
	
		if(cte < best_error)
		{			
	
			K[index] += dk[index];
			
			if(Steps > Attempts)
			{
				dk[index] *= 1.1;
				cte = pow(cte,2);		
			}
			
			best_error = cte;
			
			std::cout << "state: " << 1 << std::endl;										
			std::cout << "best error: " << best_error << std::endl;
			
		}
		else
		{
			
			K[index] -= 2*dk[index];
			
			if(cte < best_error)
			{
				best_error = cte;
				dk[index] *= 1.05;
				
				std::cout << "state: " << 2 << std::endl;								
				std::cout << "best error: " << best_error << std::endl;
				
			}
			else
			{
				
				K[index] += dk[index];
				dk[index] *= 0.95;
				
				
				std::cout << "state: " << 3 << std::endl;								
				std::cout << "best error: " << best_error << std::endl;
			}
			
			//Steps = 0;
			
		}									
	}
	
	Steps ++;		

}

double PID::TotalError() 
{
	return  0.0;
}

