// Package header file.

#ifndef ASG3_PACKAGE_H
#define ASG3_PACKAGE_H

#include <string>
using namespace std;

class Package {
public:
    Package();
    ~Package();
    string name;
    void setName(const string& valueName);
    string getName();
};

#endif //ASG3_PACKAGE_H
