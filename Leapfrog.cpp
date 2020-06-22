#include"LeapFrog.h"

#define readnumber std::stof(line.erase(line.find("#")));
#define readline std::getline(fin, line);


void compute_force(Particle& b, const Config& c)
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



   /*  double delta = -1.0 - b.R[1] + b.rad;
    if (delta > 0) {
        b.F[1] += c.K * delta;
    }*/
    /*if (b.R[0] <= 0 && b.V[0] < 0) b.V[0] *= 1;
    if (b.R[1] <= 0 && b.V[1] < 0) b.V[1] *= 1;
    if (b.R[2] <= 0 && b.V[2] < 0) b.V[2] *= 1;*/

    for (int ii = 0; ii < 3; ++ii) {
        double delta = -1.0 - b.R[ii] + b.rad;
        if (delta > 0) {
            b.F[ii] += c.K * delta;
        }
    }

    for (int ii = 0; ii < 3; ++ii) {
        double delta = 1.0 - b.R[ii] - b.rad;
        if (delta < 0) {
            b.F[ii] += c.K * delta;
        }
    }
}

void start_integration(Particle& b, float dt)
{
    for (int ii = 0; ii < 3; ++ii) {
        b.V[ii] = b.V[ii] - dt * b.F[ii] / (2 * b.mass);
    }
}


void timestep(float dt, Particle& b)
{
    for (int ii = 0; ii < 3; ++ii) {
        b.V[ii] = b.V[ii] + b.F[ii] * dt / b.mass;
    }
    for (int ii = 0; ii < 3; ++ii) {
        b.R[ii] = b.R[ii] + dt * b.V[ii];
    }
}



void Config::read(const std::string& fname)
{

    std::ifstream fin(fname);
    std::string line;


    readline;
    G = readnumber;
    readline;
    B = readnumber;
    readline;
    K = readnumber;

    fin.close();
}



void Particle::read(const std::string& fname)
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

void BallBallBounce(Particle& a, Particle& b, int& collisions_counter)
{
    float RelativePositionU[3], RelativePosition[3];//unitary relative position vector
    for (int ii = 0; ii < 3; ++ii) {
        RelativePositionU[ii] = a.R[ii] - b.R[ii];
        RelativePosition[ii] = RelativePositionU[ii];

    }

    float Diference = VectorNorm(RelativePosition);
    if (Diference < b.rad + a.rad)
    {

        for (int ii = 0; ii < 3; ii++)
        {
            RelativePositionU[ii] = RelativePositionU[ii] / Diference;
        }

        float aVcm[3];    //center of mass velocity
        float bVcm[3];

        for (int ii = 0; ii < 3; ++ii) {
            aVcm[ii] = (b.mass / (b.mass + a.mass)) * (a.V[ii] - b.V[ii]);
        }

        for (int ii = 0; ii < 3; ++ii) {
            bVcm[ii] = (a.mass / (b.mass + a.mass)) * (b.V[ii] - a.V[ii]);
        }
        float relativeVelocityOnCM[3];
        for (int ii = 0; ii < 3; ii++)
        {
            relativeVelocityOnCM[ii] = aVcm[ii] - bVcm[ii];
        }
        float ConditionForCollision = DotProduct(relativeVelocityOnCM, RelativePositionU);
        if (ConditionForCollision <= 0)
        {
            collisions_counter++;
            float aVcmNorm = VectorNorm(aVcm);

            float cosine = std::fabs((DotProduct(RelativePositionU, aVcm)) / aVcmNorm);

            float deltaV = 2 * aVcmNorm * cosine;

            float deltaVv[3];
            float conservation = 1.0;
            for (int ii = 0; ii < 3; ++ii) {
                deltaVv[ii] = RelativePositionU[ii] * deltaV;
                a.V[ii] += deltaVv[ii];
                b.V[ii] -= (a.mass / b.mass) * deltaVv[ii];
            }

        }

    }
}

float VectorNorm(const float vector[3])
{
    return std::sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

float DotProduct(const float vector1[3], const float vector2[3])
{
    return (vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2]);
}
