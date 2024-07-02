#ifndef OWNER_H
#define OWNER_H

#include <string>
#include <vector>
#include <memory>
#include "Animal.h"
using namespace std;

class Owner {
private:
    string name;
    string phoneNumber;
    string address;
    vector<shared_ptr<Animal>> animals;

public:
    Owner(string n, string p, string a) 
        : name(n), phoneNumber(p), address(a) {}

    void addAnimal(shared_ptr<Animal> animal) {
        animals.push_back(animal);
    }

    string getContactInfo() const {
        return "Name: " + name + ", Phone: " + phoneNumber + ", Address: " + address;
    }
};

#endif