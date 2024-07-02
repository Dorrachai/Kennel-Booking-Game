#ifndef CAT_H
#define CAT_H

#include "Animal.h"
#include <iostream>

class Cat : public Animal {
public:
    Cat(string n, int a, string b, string f)
        : Animal(n, "Cat", a, b, f) {}

    void makeSound() override {
        cout << "Meow!" << endl;
    }
};

#endif