//Package class file


#include "Package.h"

Package::Package() {name = "";}
Package::~Package() {}
void Package::setName(const string& valueName) {name = valueName;}
string Package::getName() {return name;}
