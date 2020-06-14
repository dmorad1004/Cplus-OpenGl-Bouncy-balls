#include <iostream>
#include <fstream>
#include <string>

/*
  Goal: modelar una particula que cae bajo la accion de la gravedad y con amortiguamiento para Visual Studio
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
  void read(const std::string & fname);
  void print(const std::string & fname);
};

struct Config {
  float TMIN = 0.0;
  int NSTEPS = 0;
  float DT = 0.0;
  float G = 0.0;
  float B = 0.0;
  float K = 0.0;
  // method
  void read(const std::string & fname);
  void print(const std::string & fname);
};


void compute_force(Particle & b, const Config & c);
void start_integration(Particle & b, float dt);
void timestep(float dt, Particle & b);


#define readnumber std::stod(line.erase(line.find("#")));
#define readline std::getline(fin, line);

int main(void)
{
  Particle body1;
	body1.read("MD.body");
  Config conf; 
  conf.read("MD.conf");

  // preprocessing
  compute_force(body1, conf); // F
  start_integration(body1, conf.DT);

  // processing
  for(int ii = 0; ii < conf.NSTEPS; ++ii) {
    float t = conf.TMIN + ii*conf.DT;
    timestep(conf.DT, body1);
    compute_force(body1, conf);
    if (ii%1 == 0) {
      print(t, body1);
    }
  }

  return 0;
}


void compute_force(Particle & b, const Config & c)
{
	// reset forces
  for(int ii = 0; ii < 3; ++ii) {
    b.F[ii] = 0.0;
  }
  // gravity force
  b.F[1] += -c.G*b.mass; 
  // add damping
  for(int ii = 0; ii < 3; ++ii) {
    b.F[ii] += -c.B*b.mass*b.V[ii]; 
  }
  // bounce with floor
  //if (b.R[1] <= 0 && b.V[1] < 0) b.V[1] *= -1;
  float delta = 0.0 - (b.R[1] - b.rad);
  if (delta > 0) {
    b.F[1] += c.K*delta;
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



void Config::read(const std::string & fname)
{
  // open file (for reading)
  std::ifstream fin(fname);
  
  // read it
  std::string line;

  readline; // read first line
  TMIN = readnumber;
  readline // read second line
  NSTEPS = std::stoi(line.erase(line.find('#')));
  readline // read next line
  DT = readnumber;
  readline // read next line
  G = readnumber;
  readline // read next line
  B = readnumber;
  readline // read next line
  K = readnumber;

  // close it
  fin.close();
}



void Particle::read(const std::string & fname)
{
  // open file (for reading)
  std::ifstream fin(fname);
  // read it
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


  // close it
  fin.close();
}

