#ifndef BOOKING_H
#define BOOKING_H

#include <ctime>
#include <memory>
#include "Animal.h"
using namespace std;

class Booking {
private:
    shared_ptr<Animal> animal;
    time_t startDate;
    time_t endDate;
    bool isPaid;
    bool isCurrent;

public:
    Booking(shared_ptr<Animal> a, time_t start, time_t end, bool paid = false)
        : animal(a), startDate(start), endDate(end), isPaid(paid), isCurrent(true) {}

    int getDuration() const {
        return difftime(endDate, startDate) / (60 * 60 * 24);
    }

    void completeBooking() {
        isCurrent = false;
    }

    bool getIsCurrent() const {
        return isCurrent;
    }

    shared_ptr<Animal> getAnimal() const {
        return animal;
    }

    time_t getStartDate() const {
        return startDate;
    }

    time_t getEndDate() const {
        return endDate;
    }

    bool getIsPaid() const {
        return isPaid;
    }

    void setPaid(bool paid) {
        isPaid = paid;
    }
};

#endif 