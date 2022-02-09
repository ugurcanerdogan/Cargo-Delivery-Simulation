//Truck class file

#include "Truck.h"

Truck::Truck() {power = 0;}
Truck::~Truck() {}
void Truck::setPower(const double& valuePower) {power = valuePower;}
double Truck::getPower() {return power;}
