#include <random>
#include <algorithm>
#include <random>
#include <iostream>
#include <tuple>
#include <numeric>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

#include "particle_filter.h"

using std::normal_distribution;
using std::default_random_engine;

using vector_t = std::vector<double>;

default_random_engine gen;

using namespace std;

void ParticleFilter::init(double x, double y, double theta, double std[]) {

	// Number of particles
	num_particles = 200;
	weights.resize(num_particles, 1.0f);

	// Creates a normal (Gaussian) distribution for x
	normal_distribution<double> dist_x(x, std[0]);
	
	// Creates a normal (Gaussian) distribution for y
	normal_distribution<double> dist_y(y, std[1]);
	
	// Creates a normal (Gaussian) distribution for y
	normal_distribution<double> dist_theta(theta, std[2]);
	
	// Initializations
	for (int i = 0; i < num_particles; i++) 
	{
		Particle p;
		
		p.id = i;
		// Add random Gaussian noise to each particle.		
		p.x = dist_x(gen);
		p.y = dist_y(gen);
		p.theta = dist_theta(gen);
		
		// Initialize all weights to 1
		p.weight = 1.0;
		
		particles.push_back(p);
	}
	
	is_initialized = true;
  
}

void ParticleFilter::prediction(double delta_t, double std_pos[], double velocity, double yaw_rate) 
{
	
	// Creates a normal (Gaussian) distribution for x
	normal_distribution<double> dist_x(0, std_pos[0]);
	
	// Creates a normal (Gaussian) distribution for y
	normal_distribution<double> dist_y(0, std_pos[1]);
	
	// Creates a normal (Gaussian) distribution for theta
	normal_distribution<double> dist_theta(0, std_pos[2]);
	
	
	for( int i = 0; i <  num_particles; i++)
	{
		// Avoid the division by zero
		if (fabs(yaw_rate)  < 0.01) 
		{ 
			// Add measurements to each particle
			particles[i].x += velocity * delta_t * cos(particles[i].theta);			
			particles[i].y += velocity * delta_t * sin(particles[i].theta);
			
		}	 
		else 
		{

			// Add measurements to each particle
			particles[i].x += (velocity/yaw_rate)*(sin(particles[i].theta + yaw_rate*delta_t) - sin(particles[i].theta));	
			particles[i].y += (velocity/yaw_rate)*(cos(particles[i].theta) - cos(particles[i].theta + yaw_rate*delta_t));		
			particles[i].theta += yaw_rate*delta_t;
		}

		
		// Add Gaussian noise to each particle		
		particles[i].x += dist_x(gen);		
		particles[i].y += dist_y(gen);		
		particles[i].theta += dist_theta(gen);
	}
}

void ParticleFilter::dataAssociation(std::vector<LandmarkObs> predicted, std::vector<LandmarkObs>& observations)
{
	double min_distance, delta, dx, dy;
	int min_idx;

	for(unsigned k = 0; k < observations.size(); k++)
	{
		auto obs = observations[k];
	
		min_distance = numeric_limits<double>::max();
		min_idx = -1;
	
		for(unsigned j = 0; j < predicted.size(); j++)
		{
			auto pred_lm = predicted[j];

			delta = dist(obs.x, obs.y, pred_lm.x, pred_lm.y);
			
			if(delta < min_distance)
			{
				min_distance = delta;
				min_idx = j;
			}
		}
		
		observations[k].id = min_idx; 
	}
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[],
		std::vector<LandmarkObs> observations, Map map_landmarks)
{  
  
	for(unsigned i =0; i < particles.size(); i++)
	{
		auto p = particles[i];
  
		std::vector<LandmarkObs> predicted_landmarks;
  
		for (unsigned int j = 0; j < map_landmarks.landmark_list.size(); j++) 
		{
			LandmarkObs lm_pred;
		
			lm_pred.x = map_landmarks.landmark_list[j].x_f;
			lm_pred.y = map_landmarks.landmark_list[j].y_f;
			lm_pred.id = map_landmarks.landmark_list[j].id_i;
			
			auto dx = lm_pred.x - p.x;
			auto dy = lm_pred.y - p.y;
			
			// If in range		
			if(fabs(dx) <= sensor_range  && fabs(dy) <= sensor_range)
			{
				predicted_landmarks.push_back(lm_pred);
			}
		}

		std::vector<LandmarkObs> transformed_obs;
		double total_prob = 1.0f;
		
		// Transformation	
		for(auto obs_lm : observations)
		{
			LandmarkObs transf;
			
			transf.x = obs_lm.x * cos(p.theta) - obs_lm.y * sin(p.theta) + p.x;
			transf.y = obs_lm.x * sin(p.theta) + obs_lm.y * cos(p.theta) + p.y;
			transf.id = obs_lm.id;
		
			transformed_obs.push_back(transf);
		}	
		
		// Association
		dataAssociation(predicted_landmarks, transformed_obs);
	
		// Calculate total weight's particle with multivariate Gaussian
		for(int j = 0; j < transformed_obs.size(); j++)
		{
			auto obs = transformed_obs[j];			
			
			auto assoc_lm = predicted_landmarks[obs.id];  
					
			double s_x = std_landmark[0];
			double s_y = std_landmark[1];
			
			double obs_w = ( 1/(2*M_PI*s_x*s_y)) * 
							exp( -( pow(assoc_lm.x - obs.x,2)/(2*pow(s_x, 2)) + (pow(assoc_lm.y - obs.y,2)/(2*pow(s_y, 2))) ) );		
			
			total_prob *= obs_w;
		}
		
		particles[i].weight = total_prob;
		
		weights[i] = total_prob;
	}
  
}

void ParticleFilter::resample()
{
	std::discrete_distribution<int> d(weights.begin(), weights.end());
	std::vector<Particle> new_particles;
	
	for(unsigned i = 0; i < num_particles; i++)
	{
		auto ind = d(gen);
		new_particles.push_back(std::move(particles[ind]));
	}
	
	particles = std::move(new_particles);
}

Particle ParticleFilter::SetAssociations(Particle particle, std::vector<int> associations, std::vector<double> sense_x, std::vector<double> sense_y)
{
	//particle: the particle to assign each listed association, and association's (x,y) world coordinates mapping to
	// associations: The landmark id that goes along with each listed association
	// sense_x: the associations x mapping already converted to world coordinates
	// sense_y: the associations y mapping already converted to world coordinates

	//Clear the previous associations
	particle.associations.clear();
	particle.sense_x.clear();
	particle.sense_y.clear();

	particle.associations= associations;
 	particle.sense_x = sense_x;
 	particle.sense_y = sense_y;

 	return particle;
}

string ParticleFilter::getAssociations(Particle best)
{
	vector<int> v = best.associations;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<int>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
string ParticleFilter::getSenseX(Particle best)
{
	vector<double> v = best.sense_x;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
string ParticleFilter::getSenseY(Particle best)
{
	vector<double> v = best.sense_y;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}