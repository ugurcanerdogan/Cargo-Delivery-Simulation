// Truck header file.

#ifndef ASG3_TRUCK_H
#define ASG3_TRUCK_H

#include "Package.h"
using namespace std;

class Truck: public Package {
public:
    Truck();
    ~Truck();
    double power;
    void setPower(const double& valuePower);
    double getPower();
};

#endif //ASG3_TRUCK_H
