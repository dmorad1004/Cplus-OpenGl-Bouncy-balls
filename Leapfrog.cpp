#include"LeapFrog.h"

#define readnumber std::stof(line.erase(line.find("#")));
#define readline std::getline(fin, line);


void compute_force(Particle & b, const Config & c)
{
    // reset forces
    for (int ii = 0; ii < 3; ++ii) {
        b.F[ii] = 0.0;
    }
    // gravity force
    b.F[1] += -c.G * b.mass;
    // add damping
    for (int ii = 0; ii < 3; ++ii) {
        b.F[ii] += -c.B * b.mass * b.V[ii];
    }
    // bounce with floor
    double delta = 0.0 - (b.R[1] - b.rad);
    if (delta > 0) {
    b.F[1] += c.K*delta;
  }
    
}

void start_integration(Particle & b, float dt)
{
    for (int ii = 0; ii < 3; ++ii) {
        b.V[ii] = b.V[ii] - dt * b.F[ii] / (2 * b.mass);
    }
}


void timestep(float dt, Particle & b)
{
    for (int ii = 0; ii < 3; ++ii) {
        b.V[ii] = b.V[ii] + b.F[ii] * dt / b.mass;
    }
    for (int ii = 0; ii < 3; ++ii) {
        b.R[ii] = b.R[ii] + dt * b.V[ii];
    }
}



void Config::read(const std::string & fname)
{

    std::ifstream fin(fname);
    std::string line;

    readline;
    TMIN = readnumber;
    readline;
    NSTEPS = std::stoi(line.erase(line.find('#')));
    readline;
    DT = readnumber;
    readline;
    G = readnumber;
    readline;
    B = readnumber;
    readline;
    K = readnumber;

    fin.close();
}



void Particle::read(const std::string & fname)
{

    std::ifstream fin(fname);
    std::string line;

    readline;
    mass = readnumber;
    readline;
    rad = readnumber;
    //Position
    readline;
    R[0] = readnumber;
    readline;
    R[1] = readnumber;
    readline;
    R[2] = readnumber;
    //Velocity
    readline;
    V[0] = readnumber;
    readline;
    V[1] = readnumber;
    readline;
    V[2] = readnumber;
    //Force
    readline;
    F[0] = readnumber;
    readline;
    F[1] = readnumber;
    readline;
    F[2] = readnumber;

    fin.close();
}
