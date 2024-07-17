#ifndef DOG_H
#define DOG_H
#include <iostream>
#include "Animal.h"

class Dog : public Animal {
public:
    Dog(string n, int a, string b, string f)
        : Animal(n, "Dog", a, b, f) {}

    void makeSound() override {
        cout << "Woof!" << endl;
    }
};

#endif