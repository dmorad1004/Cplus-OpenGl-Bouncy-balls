#include <iostream>
/*
  Goal: modelar una particula que cae bajo la accion de la gravedad y tal vez amortiguamiento 
    Y
    |
    |
    |_______ X
    /
   /
  /
 Z
*/
struct Particle 
{ 
  // atributes
  float mass{0}; 
  float rad{0};
  float R[3] = {0.0};
  float V[3] = {0.0};
  float F[3] = {0.0}; 
};

const float TMIN = 0.0;
const int NSTEPS = 1000;
const float DT = 0.01;
const float G = 9.81;
const float B = 0.0;
const float K = 12.8;

void initial_conditions(Particle & b);
void compute_force(Particle & b);
void start_integration(Particle & b, float dt);
void timestep(float dt, Particle & b);

int main(void)
{
  Particle body1;

  // preprocessing
  initial_conditions(body1); // R, V
  compute_force(body1); // F
  start_integration(body1, DT);

  // processing
  for(int ii = 0; ii < NSTEPS; ++ii) {
    float t = TMIN + ii*DT;
    timestep(DT, body1);
    compute_force(body1);
  }

  return 0;
}

void initial_conditions(Particle & b)
{
  b.R[1] = 10.7;
  b.V[1] = 3.9;
  b.mass = 0.128;
  b.rad = 0.11;
}

void compute_force(Particle & b)
{
  // reset forces
  for(int ii = 0; ii < 3; ++ii) {
    b.F[ii] = 0.0;
  }
  // gravity force
  b.F[1] += -G*b.mass; 
  // add damping
  for(int ii = 0; ii < 3; ++ii) {
    b.F[ii] += -B*b.mass*b.V[ii]; 
  }
  // bounce with floor
  //if (b.R[1] <= 0 && b.V[1] < 0) b.V[1] *= -1;
  float delta = 0.0 - (b.R[1] - b.rad);
  if (delta > 0) {
    b.F[1] += K*delta;
  }
}

void start_integration(Particle & b, float dt)
{
  for(int ii = 0; ii < 3; ++ii) {
    b.V[ii] = b.V[ii] - dt*b.F[ii]/(2*b.mass);
  }
}


void timestep(float dt, Particle & b)
{
  for(int ii = 0; ii < 3; ++ii) {
    b.V[ii] = b.V[ii] + b.F[ii]*dt/b.mass;
  }
  for(int ii = 0; ii < 3; ++ii) {
    b.R[ii] = b.R[ii] + dt*b.V[ii];
  }
}

