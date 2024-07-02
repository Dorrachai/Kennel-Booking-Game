#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {
protected:
    string name;
    string species;
    int age;
    string size; 
    string furColor;

public:
    Animal(string n, string s, int a, string sz, string f)
        : name(n), species(s), age(a), size(sz), furColor(f) {}

    virtual void makeSound() = 0;

    virtual double calculateCost(int days) {
        return days * 10.0; 
    }

    string getName() const {
        return name;
    }

    string getSpecies() const {
        return species;
    }

    int getAge() const {
        return age;
    }

    string getSize() const {
        return size;
    }

    string getFurColor() const {
        return furColor;
    }
};

#endif 