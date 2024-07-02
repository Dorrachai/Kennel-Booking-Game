#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include <vector>
#include <memory>
#include "Booking.h"
using namespace std;

class BookingManager {
private:
    vector<shared_ptr<Booking> > bookings;

public:
    void addBooking(shared_ptr<Booking> booking) {
        bookings.push_back(booking);
    }

    vector<shared_ptr<Booking> > listBookings() const {
        return bookings;
    }

    vector<shared_ptr<Booking> > listCurrentBookings() const {
        vector<shared_ptr<Booking> > currentBookings;
        for (auto& booking : bookings) {
            if (booking->getIsCurrent()) {
                currentBookings.push_back(booking);
            }
        }
        return currentBookings;
    }

    void completeBooking(shared_ptr<Booking> booking) {
        booking->completeBooking();
    }
};

#endif 