#ifndef _SPHERICAL_
#define _SPHERICAL_

#include <math.h>

class Spherical
{

public:
    Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance), theta(gtheta), fi(gfi){};

    float getX() { return distance * cos(theta) * cos(fi); }

    float getY() { return distance * sin(theta); }

    float getZ() { return distance * cos(theta) * sin(fi); }

    float getDistance() const { return this->distance; }

    float getTheta() const { return this->theta; }

    float getFi() const { return this->fi; }

    void setDistance(float distance) { this->distance = distance; }

    void setTheta(float theta) { this->theta = theta; }

    void setFi(float fi) { this->fi = fi; }

private:
    float distance, theta, fi;
};

#endif