#ifndef _frog_
#define _frog_


#include <iostream>
#include <fstream>
#include <string>

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
    float TMIN = 0.0;
    int NSTEPS = 0;
    float DT = 0.0;
    float G = 0.0;
    float B = 0.0;
    float K = 0.0;
    // method
    void read(const std::string& fname);
};

void compute_force(Particle& b, const Config& c);
void start_integration(Particle& b, float dt);
void timestep(float dt, Particle& b);



#endif // 
