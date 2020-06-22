#ifndef _FROG_
#define _FROG_


#include <iostream>
#include <fstream>
#include <string>
#include<cmath>
struct Particle
{
    // atributes
    float mass{ 0 };
    float rad{ 0 };
    float R[3] = { 0.0 };
    float V[3] = { 0.0 };
    float F[3] = { 0.0 };
    void read(const std::string& fname);
};

struct Config {

    float K = 0.0;
    float G = 0.0;
    float B = 0.0;
    // method
    void read(const std::string& fname);
};

void compute_force(Particle& b, const Config& c);
void start_integration(Particle& b, float dt);
void timestep(float dt, Particle& b);
float DotProduct(const float vector1[3], const float vector2[3]);
void BallBallBounce(Particle& a, Particle& b, int& collisions_counter);
float VectorNorm(const float vector[3]);

#endif // 
