#ifndef KENNEL_H
#define KENNEL_H

#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Animal.h"
#include "BookingManager.h"
using namespace std;

class Kennel {
private:
    vector<shared_ptr<Animal>> animals;
    int capacity;
    BookingManager bookingManager;

public:
    Kennel(int cap) : capacity(cap) {}

    bool checkInAnimal(shared_ptr<Animal> animal) {
        if (animals.size() < capacity) {
            animals.push_back(animal);
            return true;
        }
        return false;
    }

    bool checkOutAnimal(shared_ptr<Animal> animal) {
        auto it = find(animals.begin(), animals.end(), animal);
        if (it != animals.end()) {
            animals.erase(it);
            return true;
        }
        return false;
    }

    vector<shared_ptr<Animal>> listAnimals() const {
        return animals;
    }

    void addBooking(shared_ptr<Booking> booking) {
        bookingManager.addBooking(booking);
    }

    vector<shared_ptr<Booking>> listBookings() const {
        return bookingManager.listBookings();
    }

    vector<shared_ptr<Booking>> listCurrentBookings() const {
        return bookingManager.listCurrentBookings();
    }

    void completeBooking(shared_ptr<Booking> booking) {
        bookingManager.completeBooking(booking);
    }

    void saveBookingsToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Unable to open file for writing: " << filename << endl;
            return;
        }
        for (auto& booking : bookingManager.listBookings()) {
            file << booking->getAnimal()->getName() << ","
                 << booking->getStartDate() << ","
                 << booking->getEndDate() << ","
                 << booking->getIsPaid() << "\n";
        }
        file.close();
    }

    void loadBookingsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Unable to open file for reading: " << filename << endl;
            return;
        }
        string name;
        time_t startDate, endDate;
        bool isPaid;
        while (file >> name >> startDate >> endDate >> isPaid) {
            shared_ptr<Animal> animal = nullptr;
            for (auto& a : animals) {
                if (a->getName() == name) {
                    animal = a;
                    break;
                }
            }
            if (animal == nullptr) {
                cerr << "Animal not found: " << name << endl;
                continue;
            }
            shared_ptr<Booking> booking = make_shared<Booking>(animal, startDate, endDate, isPaid);
            bookingManager.addBooking(booking);
        }
        file.close();
    }
};

#endif // KENNEL_H