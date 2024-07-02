#ifndef STAFF_H
#define STAFF_H

#include <string>
using namespace std;

class Staff {
private:
    string name;
    int employeeID;
    string position;

public:
    Staff(string n, int id, string p) 
        : name(n), employeeID(id), position(p) {}

    string getDetails() const {
        return "Name: " + name + ", ID: " + to_string(employeeID) + ", Position: " + position;
    }
};

#endif 